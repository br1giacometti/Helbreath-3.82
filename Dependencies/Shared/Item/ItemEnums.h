// ItemEnums.h: Unified type-safe enums for the Item system
//
// Replaces divergent DEF_ macros from Client/Item.h and Server/Item.h
// Naming decisions:
//   - Slot 5: Leggings (matches item data: PlateLeggings, ChainHose)
//   - Slot 13: FullBody (describes slot purpose, not behavior)
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include <cstdint>

namespace hb {
namespace item {

//------------------------------------------------------------------------
// Equipment Position
//------------------------------------------------------------------------
enum class EquipPos : int8_t
{
    None      = 0,
    Head      = 1,
    Body      = 2,
    Arms      = 3,
    Pants     = 4,
    Leggings  = 5,   // Leg armor (ChainHose, PlateLeggings)
    Neck      = 6,
    LeftHand  = 7,
    RightHand = 8,
    TwoHand   = 9,
    RightFinger = 10,
    LeftFinger  = 11,
    Back      = 12,
    FullBody  = 13,  // Full-body armor (robes) - releases other armor slots when equipped

    Max       = 15
};

constexpr int DEF_MAXITEMEQUIPPOS = 15;

//------------------------------------------------------------------------
// Item Type
//------------------------------------------------------------------------
enum class ItemType : int8_t
{
    NotUsed                = -1,  // Previously used, but currently unused item
    None                   = 0,
    Equip                  = 1,
    Apply                  = 2,
    UseDeplete             = 3,
    Install                = 4,
    Consume                = 5,
    Arrow                  = 6,
    Eat                    = 7,
    UseSkill               = 8,
    UsePerm                = 9,
    UseSkillEnableDialogBox = 10,
    UseDepleteDest         = 11,
    Material               = 12
};

//------------------------------------------------------------------------
// Item Effect Type
//------------------------------------------------------------------------
enum class ItemEffectType : int16_t
{
    None               = 0,
    Attack             = 1,   // Attack value: value1 D value2 + value3
    Defense            = 2,   // Defense capability
    AttackArrow        = 3,   // Arrow attack - adds to base weapon damage
    HP                 = 4,   // HP restoration effect
    MP                 = 5,   // MP restoration effect
    SP                 = 6,   // SP restoration effect
    HPStock            = 7,   // HP recovery over time (no immediate visual)
    Get                = 8,   // Acquire something (tools, containers)
    StudySkill         = 9,   // Skill learning item
    ShowLocation       = 10,  // Shows location on map
    Magic              = 11,  // Item with magic effect when used
    ChangeAttr         = 12,  // Changes player attributes (hair, skin, etc.)
    AttackManaSave     = 13,  // Attack with mana saving effect
    AddEffect          = 14,  // Additional effect
    MagicDamageSave    = 15,  // Magic damage absorption
    OccupyFlag         = 16,  // Capture flag
    Dye                = 17,  // Dye item
    StudyMagic         = 18,  // Magic learning item
    AttackMaxHPDown    = 19,  // Attack that reduces max HP and HP recovery
    AttackDefense      = 20,  // Attack with defense reduction effect
    MaterialAttr       = 21,  // Material attribute for crafting
    FirmStamina        = 22,  // Stamina enhancement
    Lottery            = 23,  // Lottery ticket
    AttackSpecAbility  = 24,  // Attack with special ability
    DefenseSpecAbility = 25,  // Defense with special ability
    AlterItemDrop      = 26,  // Affects item drop of other items
    ConstructionKit    = 27,  // Construction kit
    Warm               = 28,  // Unfreeze potion effect
    // 29 is unused
    Farming            = 30,  // Farming item
    Slates             = 31,  // Ancient Tablets
    ArmorDye           = 32,  // Armor dye
    CritKomm           = 33,  // Crit Candy
    WeaponDye          = 34   // Weapon dye
};

//------------------------------------------------------------------------
// AddEffect Sub-Types (used with ItemEffectType::AddEffect)
// m_sItemEffectValue1 contains the sub-type, m_sItemEffectValue2 contains the value
//------------------------------------------------------------------------
enum class AddEffectType : int16_t
{
    MagicResist     = 1,   // Additional magic resistance
    ManaSave        = 2,   // Mana save percentage
    PoisonResist    = 3,   // Poison resistance
    CriticalHit     = 4,   // Critical hit chance
    Poisoning       = 5,   // Poison attack
    RepairItem      = 6,   // Repair item
    FireAbsorb      = 7,   // Fire damage absorption
    IceAbsorb       = 8,   // Ice damage absorption
    LightAbsorb     = 9,   // Light damage absorption
    ExpBonus        = 10,  // Experience bonus
    GoldBonus       = 11,  // Gold drop bonus
    // 12 unused
    Summon          = 13,  // Summon creature
    CancelBuff      = 14,  // Cancel buffs
    // 15-17 unused
    SpecialAbility  = 18,  // Special ability
    ParalysisImmune = 19   // Paralysis immunity
};

constexpr int16_t ToInt(AddEffectType type) { return static_cast<int16_t>(type); }

//------------------------------------------------------------------------
// Touch Effect Type (item-specific effects on first touch/creation)
//------------------------------------------------------------------------
enum class TouchEffectType : int16_t
{
    None        = 0,
    UniqueOwner = 1,  // Item bound to owner
    ID          = 2,  // Item has unique ID
    Date        = 3   // Item has expiration date
};

//------------------------------------------------------------------------
// Helper Functions
//------------------------------------------------------------------------

// Check if equipment position is a weapon slot
constexpr bool IsWeaponSlot(EquipPos pos)
{
    return pos == EquipPos::LeftHand ||
           pos == EquipPos::RightHand ||
           pos == EquipPos::TwoHand;
}

// Check if equipment position is an armor slot
constexpr bool IsArmorSlot(EquipPos pos)
{
    return pos == EquipPos::Head ||
           pos == EquipPos::Body ||
           pos == EquipPos::Arms ||
           pos == EquipPos::Pants ||
           pos == EquipPos::Leggings ||
           pos == EquipPos::Back ||
           pos == EquipPos::FullBody;
}

// Check if equipment position is an accessory slot
constexpr bool IsAccessorySlot(EquipPos pos)
{
    return pos == EquipPos::Neck ||
           pos == EquipPos::RightFinger ||
           pos == EquipPos::LeftFinger;
}

// Check if item type indicates stackable items
constexpr bool IsStackableType(ItemType type)
{
    return type == ItemType::Arrow ||
           type == ItemType::Consume ||
           type == ItemType::Eat ||
           type == ItemType::UseDeplete ||
           type == ItemType::UseDepleteDest ||
           type == ItemType::Material;
}

// Check if item effect type is an attack type
constexpr bool IsAttackEffectType(ItemEffectType type)
{
    return type == ItemEffectType::Attack ||
           type == ItemEffectType::AttackArrow ||
           type == ItemEffectType::AttackManaSave ||
           type == ItemEffectType::AttackMaxHPDown ||
           type == ItemEffectType::AttackDefense ||
           type == ItemEffectType::AttackSpecAbility;
}

// Check if item effect type is consumable (potion-like)
constexpr bool IsConsumableEffectType(ItemEffectType type)
{
    return type == ItemEffectType::HP ||
           type == ItemEffectType::MP ||
           type == ItemEffectType::SP ||
           type == ItemEffectType::HPStock;
}

//------------------------------------------------------------------------
// Enum conversion helpers (for serialization/deserialization)
//------------------------------------------------------------------------

constexpr int8_t ToInt(EquipPos pos) { return static_cast<int8_t>(pos); }
constexpr int8_t ToInt(ItemType type) { return static_cast<int8_t>(type); }
constexpr int16_t ToInt(ItemEffectType type) { return static_cast<int16_t>(type); }
constexpr int16_t ToInt(TouchEffectType type) { return static_cast<int16_t>(type); }

constexpr EquipPos ToEquipPos(int8_t val) { return static_cast<EquipPos>(val); }
constexpr ItemType ToItemType(int8_t val) { return static_cast<ItemType>(val); }
constexpr ItemEffectType ToItemEffectType(int16_t val) { return static_cast<ItemEffectType>(val); }
constexpr TouchEffectType ToTouchEffectType(int16_t val) { return static_cast<TouchEffectType>(val); }

//------------------------------------------------------------------------
// Common Item IDs
// These are well-known item IDs that are frequently referenced in code
//------------------------------------------------------------------------
namespace ItemId
{
    constexpr short Arrow = 77;
    constexpr short PoisonArrow = 78;
    constexpr short GuildAdmissionTicket = 88;
    constexpr short GuildSecessionTicket = 89;
    constexpr short Gold = 90;
}

} // namespace item
} // namespace hb

//------------------------------------------------------------------------
// Legacy DEF_ macros for backward compatibility during transition
// TODO: Remove these once all code is migrated to use enums directly
//------------------------------------------------------------------------

// Equipment positions
#define DEF_MAXITEMEQUIPPOS     15
#define DEF_EQUIPPOS_NONE       0
#define DEF_EQUIPPOS_HEAD       1
#define DEF_EQUIPPOS_BODY       2
#define DEF_EQUIPPOS_ARMS       3
#define DEF_EQUIPPOS_PANTS      4
#define DEF_EQUIPPOS_LEGGINGS   5
#define DEF_EQUIPPOS_BOOTS      5   // Alias for LEGGINGS (client compatibility)
#define DEF_EQUIPPOS_NECK       6
#define DEF_EQUIPPOS_LHAND      7
#define DEF_EQUIPPOS_RHAND      8
#define DEF_EQUIPPOS_TWOHAND    9
#define DEF_EQUIPPOS_RFINGER    10
#define DEF_EQUIPPOS_LFINGER    11
#define DEF_EQUIPPOS_BACK       12
#define DEF_EQUIPPOS_FULLBODY   13
#define DEF_EQUIPPOS_RELEASEALL 13  // Alias for FULLBODY (server compatibility)

// Item types
#define DEF_ITEMTYPE_NOTUSED                    -1
#define DEF_ITEMTYPE_NONE                        0
#define DEF_ITEMTYPE_EQUIP                       1
#define DEF_ITEMTYPE_APPLY                       2
#define DEF_ITEMTYPE_USE_DEPLETE                 3
#define DEF_ITEMTYPE_INSTALL                     4
#define DEF_ITEMTYPE_CONSUME                     5
#define DEF_ITEMTYPE_ARROW                       6
#define DEF_ITEMTYPE_EAT                         7
#define DEF_ITEMTYPE_USE_SKILL                   8
#define DEF_ITEMTYPE_USE_PERM                    9
#define DEF_ITEMTYPE_USE_SKILL_ENABLEDIALOGBOX  10
#define DEF_ITEMTYPE_USE_DEPLETE_DEST           11
#define DEF_ITEMTYPE_MATERIAL                   12

// Item effect types
#define DEF_ITEMEFFECTTYPE_NONE                 0
#define DEF_ITEMEFFECTTYPE_ATTACK               1
#define DEF_ITEMEFFECTTYPE_DEFENSE              2
#define DEF_ITEMEFFECTTYPE_ATTACK_ARROW         3
#define DEF_ITEMEFFECTTYPE_HP                   4
#define DEF_ITEMEFFECTTYPE_MP                   5
#define DEF_ITEMEFFECTTYPE_SP                   6
#define DEF_ITEMEFFECTTYPE_HPSTOCK              7
#define DEF_ITEMEFFECTTYPE_GET                  8
#define DEF_ITEMEFFECTTYPE_STUDYSKILL           9
#define DEF_ITEMEFFECTTYPE_SHOWLOCATION        10
#define DEF_ITEMEFFECTTYPE_MAGIC               11
#define DEF_ITEMEFFECTTYPE_CHANGEATTR          12
#define DEF_ITEMEFFECTTYPE_ATTACK_MANASAVE     13
#define DEF_ITEMEFFECTTYPE_ADDEFFECT           14
#define DEF_ITEMEFFECTTYPE_MAGICDAMAGESAVE     15
#define DEF_ITEMEFFECTTYPE_OCCUPYFLAG          16
#define DEF_ITEMEFFECTTYPE_DYE                 17
#define DEF_ITEMEFFECTTYPE_STUDYMAGIC          18
#define DEF_ITEMEFFECTTYPE_ATTACK_MAXHPDOWN    19
#define DEF_ITEMEFFECTTYPE_ATTACK_DEFENSE      20
#define DEF_ITEMEFFECTTYPE_MATERIAL_ATTR       21
#define DEF_ITEMEFFECTTYPE_FIRMSTAMINAR        22
#define DEF_ITEMEFFECTTYPE_LOTTERY             23
#define DEF_ITEMEFFECTTYPE_ATTACK_SPECABLTY    24
#define DEF_ITEMEFFECTTYPE_DEFENSE_SPECABLTY   25
#define DEF_ITEMEFFECTTYPE_ALTERITEMDROP       26
#define DEF_ITEMEFFECTTYPE_CONSTRUCTIONKIT     27
#define DEF_ITEMEFFECTTYPE_WARM                28
#define DEF_ITEMEFFECTTYPE_FARMING             30
#define DEF_ITEMEFFECTTYPE_SLATES              31
#define DEF_ITEMEFFECTTYPE_ARMORDYE            32
#define DEF_ITEMEFFECTTYPE_CRITKOMM            33
#define DEF_ITEMEFFECTTYPE_WEAPONDYE           34

// Touch effect types
#define DEF_ITET_UNIQUE_OWNER   1
#define DEF_ITET_ID             2
#define DEF_ITET_DATE           3
