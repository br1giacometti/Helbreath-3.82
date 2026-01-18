// Item.h: Unified CItem class for Helbreath Client and Server
//
// This class combines the item definitions from both Client/Item.h and Server/Item.h
// with the addition of m_cDisplayName for localized display names.
//
// Note: Display names are now stored directly in the database (name column).
// The server sends display names directly, so no client-side lookup is needed.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "ItemEnums.h"
#include <cstring>
#include <cstdint>

class CItem
{
public:
    inline CItem()
    {
        std::memset(m_cName, 0, sizeof(m_cName));
        std::memset(m_cDisplayName, 0, sizeof(m_cDisplayName));

        m_sIDnum = 0;
        m_cItemType = 0;
        m_cEquipPos = 0;
        m_sItemEffectType = 0;

        m_sItemEffectValue1 = 0;
        m_sItemEffectValue2 = 0;
        m_sItemEffectValue3 = 0;
        m_sItemEffectValue4 = 0;
        m_sItemEffectValue5 = 0;
        m_sItemEffectValue6 = 0;

        m_wMaxLifeSpan = 0;
        m_sSpecialEffect = 0;
        m_sSpecialEffectValue1 = 0;
        m_sSpecialEffectValue2 = 0;

        m_sX = 0;
        m_sY = 0;

        m_sSprite = 0;
        m_sSpriteFrame = 0;

        m_cApprValue = 0;
        m_cSpeed = 0;

        m_wPrice = 0;
        m_wWeight = 0;
        m_sLevelLimit = 0;
        m_cGenderLimit = 0;

        m_sRelatedSkill = 0;

        m_cCategory = 0;
        m_bIsForSale = false;

        m_dwCount = 1;
        m_sTouchEffectType = 0;
        m_sTouchEffectValue1 = 0;
        m_sTouchEffectValue2 = 0;
        m_sTouchEffectValue3 = 0;

        m_cItemColor = 0;
        m_sItemSpecEffectValue1 = 0;
        m_sItemSpecEffectValue2 = 0;
        m_sItemSpecEffectValue3 = 0;

        m_wCurLifeSpan = 0;
        m_dwAttribute = 0;
    }

    inline virtual ~CItem()
    {
    }

    //------------------------------------------------------------------------
    // Core Item Data
    //------------------------------------------------------------------------

    char  m_cName[21];              // Internal item name (from database)
    char  m_cDisplayName[34];       // Localized display name (from ItemName.cfg mapping)

    short m_sIDnum;                 // Item ID number (unique identifier)
    char  m_cItemType;              // Item type (see ItemType enum)
    char  m_cEquipPos;              // Equipment position (see EquipPos enum)

    //------------------------------------------------------------------------
    // Item Effects
    //------------------------------------------------------------------------

    short m_sItemEffectType;        // Primary effect type (see ItemEffectType enum)
    short m_sItemEffectValue1;      // Effect value 1
    short m_sItemEffectValue2;      // Effect value 2
    short m_sItemEffectValue3;      // Effect value 3
    short m_sItemEffectValue4;      // Effect value 4 (for armor: stat bonus type)
    short m_sItemEffectValue5;      // Effect value 5 (for armor: stat bonus amount)
    short m_sItemEffectValue6;      // Effect value 6

    //------------------------------------------------------------------------
    // Special Effects
    //------------------------------------------------------------------------

    short m_sSpecialEffect;         // Special effect type
    short m_sSpecialEffectValue1;   // Special effect value 1
    short m_sSpecialEffectValue2;   // Special effect value 2

    //------------------------------------------------------------------------
    // Item-Specific Effects (attributes applied to item instance)
    //------------------------------------------------------------------------

    short m_sItemSpecEffectValue1;  // Item spec effect value 1
    short m_sItemSpecEffectValue2;  // Item spec effect value 2
    short m_sItemSpecEffectValue3;  // Item spec effect value 3

    //------------------------------------------------------------------------
    // Touch Effects (triggered on first touch/acquisition)
    //------------------------------------------------------------------------

    short m_sTouchEffectType;       // Touch effect type (see TouchEffectType enum)
    short m_sTouchEffectValue1;     // Touch effect value 1
    short m_sTouchEffectValue2;     // Touch effect value 2
    short m_sTouchEffectValue3;     // Touch effect value 3

    //------------------------------------------------------------------------
    // Visual Properties
    //------------------------------------------------------------------------

    short m_sSprite;                // Sprite sheet index
    short m_sSpriteFrame;           // Frame within sprite sheet
    char  m_cApprValue;             // Appearance value (for equipped items)
    char  m_cItemColor;             // Item color variant

    //------------------------------------------------------------------------
    // Position (client-side for inventory/ground display)
    //------------------------------------------------------------------------

    short m_sX;                     // X position
    short m_sY;                     // Y position

    //------------------------------------------------------------------------
    // Stats and Limits
    //------------------------------------------------------------------------

    char  m_cSpeed;                 // Weapon attack speed
    uint32_t m_wPrice;              // Base price in gold
    uint16_t m_wWeight;             // Weight (affects encumbrance)
    short m_sLevelLimit;            // Minimum level to use
    char  m_cGenderLimit;           // Gender restriction (0=none, 1=male, 2=female)
    short m_sRelatedSkill;          // Related skill for proficiency

    //------------------------------------------------------------------------
    // Durability
    //------------------------------------------------------------------------

    uint16_t m_wMaxLifeSpan;        // Maximum durability
    uint16_t m_wCurLifeSpan;        // Current durability

    //------------------------------------------------------------------------
    // Miscellaneous
    //------------------------------------------------------------------------

    char  m_cCategory;              // Item category (for shop filtering)
    bool  m_bIsForSale;             // Can be sold to NPC shops
    uint32_t m_dwCount;             // Stack count (for stackable items)

    //------------------------------------------------------------------------
    // Attribute Flags
    //
    // Bit layout: aaaa bbbb cccc dddd eeee ffff xxxx xxx1
    //   1: Custom-Made Item flag
    //   a: Item attribute type
    //   b: Item attribute value
    //   c: Special item flag
    //   d: Special item flag value
    //   e: Additional special flag
    //   f: Additional special flag value
    //------------------------------------------------------------------------

    uint32_t m_dwAttribute;

    //------------------------------------------------------------------------
    // Display Name Helpers
    //------------------------------------------------------------------------

    // Returns display name if set, otherwise falls back to m_cName
    // Note: Since DB migration, m_cName now contains display names directly
    const char* GetDisplayName() const
    {
        return (m_cDisplayName[0] != '\0') ? m_cDisplayName : m_cName;
    }

    // Legacy method - copies m_cName to m_cDisplayName for compatibility
    // Note: Since DB migration, m_cName already contains display names
    void PopulateDisplayName()
    {
        if (m_cName[0] != '\0')
        {
            std::strncpy(m_cDisplayName, m_cName, sizeof(m_cDisplayName) - 1);
            m_cDisplayName[sizeof(m_cDisplayName) - 1] = '\0';
        }
    }

    // Set display name directly
    void SetDisplayName(const char* name)
    {
        if (name != nullptr)
        {
            std::strncpy(m_cDisplayName, name, sizeof(m_cDisplayName) - 1);
            m_cDisplayName[sizeof(m_cDisplayName) - 1] = '\0';
        }
    }

    //------------------------------------------------------------------------
    // Type-Safe Enum Accessors
    //------------------------------------------------------------------------

    hb::item::EquipPos GetEquipPos() const
    {
        return hb::item::ToEquipPos(m_cEquipPos);
    }

    void SetEquipPos(hb::item::EquipPos pos)
    {
        m_cEquipPos = hb::item::ToInt(pos);
    }

    hb::item::ItemType GetItemType() const
    {
        return hb::item::ToItemType(m_cItemType);
    }

    void SetItemType(hb::item::ItemType type)
    {
        m_cItemType = hb::item::ToInt(type);
    }

    hb::item::ItemEffectType GetItemEffectType() const
    {
        return hb::item::ToItemEffectType(m_sItemEffectType);
    }

    void SetItemEffectType(hb::item::ItemEffectType type)
    {
        m_sItemEffectType = hb::item::ToInt(type);
    }

    hb::item::TouchEffectType GetTouchEffectType() const
    {
        return hb::item::ToTouchEffectType(m_sTouchEffectType);
    }

    void SetTouchEffectType(hb::item::TouchEffectType type)
    {
        m_sTouchEffectType = hb::item::ToInt(type);
    }

    //------------------------------------------------------------------------
    // Attribute Helpers
    //------------------------------------------------------------------------

    bool IsCustomMade() const
    {
        return (m_dwAttribute & 0x00000001) != 0;
    }

    void SetCustomMade(bool custom)
    {
        if (custom)
            m_dwAttribute |= 0x00000001;
        else
            m_dwAttribute &= ~0x00000001;
    }

    // Get attribute type (bits 28-31, 'a' nibble)
    uint8_t GetAttributeType() const
    {
        return static_cast<uint8_t>((m_dwAttribute >> 28) & 0x0F);
    }

    // Get attribute value (bits 24-27, 'b' nibble)
    uint8_t GetAttributeValue() const
    {
        return static_cast<uint8_t>((m_dwAttribute >> 24) & 0x0F);
    }

    // Check if item is stackable based on its type
    bool IsStackable() const
    {
        return hb::item::IsStackableType(GetItemType());
    }

    // Check if item is a weapon
    bool IsWeapon() const
    {
        return hb::item::IsWeaponSlot(GetEquipPos());
    }

    // Check if item is armor
    bool IsArmor() const
    {
        return hb::item::IsArmorSlot(GetEquipPos());
    }

    // Check if item is an accessory
    bool IsAccessory() const
    {
        return hb::item::IsAccessorySlot(GetEquipPos());
    }
};
