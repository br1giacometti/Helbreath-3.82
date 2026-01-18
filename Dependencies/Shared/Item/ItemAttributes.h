// ItemAttributes.h: Item attribute parsing and formatting helpers
//
// Provides shared logic for both client and server to interpret item
// attribute flags encoded in m_dwAttribute.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include <cstdint>

namespace hb {
namespace item {

//------------------------------------------------------------------------
// Attribute Bit Layout
//
// m_dwAttribute: aaaa bbbb cccc dddd eeee ffff xxxx xxx1
//
// Bit 0:       Custom-Made Item flag
// Bits 8-11:   Secondary effect value (f nibble)
// Bits 12-15:  Secondary effect type (e nibble)
// Bits 16-19:  Primary effect value (d nibble)
// Bits 20-23:  Primary effect type (c nibble)
// Bits 24-27:  Attribute value (b nibble)
// Bits 28-31:  Attribute type / enchant bonus (a nibble)
//------------------------------------------------------------------------

//------------------------------------------------------------------------
// Primary Attribute Types (bits 20-23)
// These determine the name prefix added to items
//------------------------------------------------------------------------
enum class AttributePrefixType : uint8_t
{
    None           = 0,
    Critical       = 1,   // "Critical " - Critical hit damage bonus
    Poisoning      = 2,   // "Poisoning " - Poison damage bonus
    Righteous      = 3,   // "Righteous " - Holy damage
    Reserved4      = 4,   // Unused
    Agile          = 5,   // "Agile " - Attack speed bonus
    Light          = 6,   // "Light " - Weight reduction
    Sharp          = 7,   // "Sharp " - Extra damage
    Strong         = 8,   // "Strong " - Endurance bonus
    Ancient        = 9,   // "Ancient " - Extra damage
    Special        = 10,  // "Special " - Magic casting bonus
    ManaConverting = 11,  // "Mana Converting " - Damage to mana conversion
    CritChance     = 12   // "Critical " - Critical hit chance bonus
};

//------------------------------------------------------------------------
// Secondary Effect Types (bits 12-15)
// These determine additional bonuses displayed on item
//------------------------------------------------------------------------
enum class SecondaryEffectType : uint8_t
{
    None              = 0,
    PoisonResistance  = 1,   // Poison Resistance +X%
    HittingProb       = 2,   // Hitting Probability +X
    DefenseRatio      = 3,   // Defense Ratio +X
    HPRecovery        = 4,   // HP recovery X%
    SPRecovery        = 5,   // SP recovery X%
    MPRecovery        = 6,   // MP recovery X%
    MagicResistance   = 7,   // Magic Resistance +X%
    PhysicalAbsorb    = 8,   // Physical Absorption +X%
    MagicAbsorb       = 9,   // Magic Absorption +X%
    ConsecutiveAttack = 10,  // Consecutive Attack Damage +X
    ExperienceBonus   = 11,  // Experience +X%
    GoldBonus         = 12   // Gold +X%
};

//------------------------------------------------------------------------
// Attribute Value Multipliers
//------------------------------------------------------------------------

// Primary effect value multipliers (indexed by AttributePrefixType)
constexpr int GetPrimaryEffectMultiplier(AttributePrefixType type)
{
    switch (type)
    {
        case AttributePrefixType::Critical:       return 1;   // +N critical damage
        case AttributePrefixType::Poisoning:      return 5;   // +N*5 poison damage
        case AttributePrefixType::Agile:          return 1;   // -1 attack speed (fixed)
        case AttributePrefixType::Light:          return 4;   // N*4% lighter
        case AttributePrefixType::Sharp:          return 1;   // Damage added (fixed)
        case AttributePrefixType::Strong:         return 7;   // N*7% endurance
        case AttributePrefixType::Ancient:        return 1;   // Extra damage added (fixed)
        case AttributePrefixType::Special:        return 3;   // N*3% magic casting
        case AttributePrefixType::ManaConverting: return 1;   // N% damage to mana
        case AttributePrefixType::CritChance:     return 1;   // N% crit chance
        default:                                  return 1;
    }
}

// Secondary effect value multipliers (indexed by SecondaryEffectType)
constexpr int GetSecondaryEffectMultiplier(SecondaryEffectType type)
{
    switch (type)
    {
        case SecondaryEffectType::PoisonResistance:  return 7;   // N*7%
        case SecondaryEffectType::HittingProb:       return 7;   // N*7
        case SecondaryEffectType::DefenseRatio:      return 7;   // N*7
        case SecondaryEffectType::HPRecovery:        return 7;   // N*7%
        case SecondaryEffectType::SPRecovery:        return 7;   // N*7%
        case SecondaryEffectType::MPRecovery:        return 7;   // N*7%
        case SecondaryEffectType::MagicResistance:   return 7;   // N*7%
        case SecondaryEffectType::PhysicalAbsorb:    return 3;   // N*3%
        case SecondaryEffectType::MagicAbsorb:       return 3;   // N*3%
        case SecondaryEffectType::ConsecutiveAttack: return 1;   // N
        case SecondaryEffectType::ExperienceBonus:   return 10;  // N*10%
        case SecondaryEffectType::GoldBonus:         return 10;  // N*10%
        default:                                     return 1;
    }
}

//------------------------------------------------------------------------
// Parsed Attribute Structure
//------------------------------------------------------------------------
struct ParsedAttribute
{
    bool isCustomMade;                    // Bit 0
    AttributePrefixType prefixType;       // Bits 20-23
    uint8_t prefixValue;                  // Bits 16-19
    SecondaryEffectType secondaryType;    // Bits 12-15
    uint8_t secondaryValue;               // Bits 8-11
    uint8_t enchantBonus;                 // Bits 28-31

    // Calculated values
    int primaryEffectAmount;              // prefixValue * multiplier
    int secondaryEffectAmount;            // secondaryValue * multiplier

    // Check if item has any special attributes
    bool HasSpecialAttributes() const
    {
        return prefixType != AttributePrefixType::None ||
               secondaryType != SecondaryEffectType::None ||
               enchantBonus > 0 ||
               isCustomMade;
    }
};

//------------------------------------------------------------------------
// Attribute Parsing Functions
//------------------------------------------------------------------------

// Parse m_dwAttribute into a structured format
inline ParsedAttribute ParseAttribute(uint32_t dwAttribute)
{
    ParsedAttribute result;

    result.isCustomMade    = (dwAttribute & 0x00000001) != 0;
    result.prefixType      = static_cast<AttributePrefixType>((dwAttribute >> 20) & 0x0F);
    result.prefixValue     = static_cast<uint8_t>((dwAttribute >> 16) & 0x0F);
    result.secondaryType   = static_cast<SecondaryEffectType>((dwAttribute >> 12) & 0x0F);
    result.secondaryValue  = static_cast<uint8_t>((dwAttribute >> 8) & 0x0F);
    result.enchantBonus    = static_cast<uint8_t>((dwAttribute >> 28) & 0x0F);

    result.primaryEffectAmount = result.prefixValue * GetPrimaryEffectMultiplier(result.prefixType);
    result.secondaryEffectAmount = result.secondaryValue * GetSecondaryEffectMultiplier(result.secondaryType);

    return result;
}

// Check if attribute flags indicate any special effects
inline bool HasSpecialEffects(uint32_t dwAttribute)
{
    return (dwAttribute & 0x00F0F000) != 0;
}

// Get enchant bonus from attribute (the +X at end of name)
inline uint8_t GetEnchantBonus(uint32_t dwAttribute)
{
    return static_cast<uint8_t>((dwAttribute >> 28) & 0x0F);
}

// Check if item is custom made
inline bool IsCustomMade(uint32_t dwAttribute)
{
    return (dwAttribute & 0x00000001) != 0;
}

//------------------------------------------------------------------------
// Attribute Construction Helpers
//------------------------------------------------------------------------

// Build attribute flags from components
inline uint32_t BuildAttribute(
    bool customMade,
    AttributePrefixType prefixType,
    uint8_t prefixValue,
    SecondaryEffectType secondaryType,
    uint8_t secondaryValue,
    uint8_t enchantBonus)
{
    uint32_t attr = 0;

    if (customMade)
        attr |= 0x00000001;

    attr |= (static_cast<uint32_t>(prefixType) & 0x0F) << 20;
    attr |= (static_cast<uint32_t>(prefixValue) & 0x0F) << 16;
    attr |= (static_cast<uint32_t>(secondaryType) & 0x0F) << 12;
    attr |= (static_cast<uint32_t>(secondaryValue) & 0x0F) << 8;
    attr |= (static_cast<uint32_t>(enchantBonus) & 0x0F) << 28;

    return attr;
}

// Set just the enchant bonus, preserving other flags
inline uint32_t SetEnchantBonus(uint32_t dwAttribute, uint8_t bonus)
{
    return (dwAttribute & 0x0FFFFFFF) | ((static_cast<uint32_t>(bonus) & 0x0F) << 28);
}

// Set custom made flag, preserving other flags
inline uint32_t SetCustomMade(uint32_t dwAttribute, bool customMade)
{
    if (customMade)
        return dwAttribute | 0x00000001;
    else
        return dwAttribute & ~0x00000001;
}

} // namespace item
} // namespace hb
