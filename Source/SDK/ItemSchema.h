#pragma once

#include <cstddef>

#include "Pad.h"
#include "UtlMap.h"
#include "UtlMemory.h"
#include "UtlVector.h"
#include "VirtualMethod.h"

enum class WeaponId : short;

struct UtlString {
    UtlMemory<char> buffer;
    int length;

    const char* data() const noexcept { return buffer.memory; }
};

struct PaintKit {
    int id;
    UtlString name;
    UtlString description;
    UtlString itemName;
    UtlString sameNameFamilyAggregate;
    UtlString pattern;
    UtlString normal;
    UtlString logoMaterial;
    bool baseDiffuseOverride;
    int rarity;
};

struct StickerKit {
    int id;
    int rarity;
    UtlString name;
    UtlString description;
    UtlString itemName;
    PAD(2 * sizeof(UtlString))
    UtlString inventoryImage;
};

class EconItemDefinition {
public:
    VIRTUAL_METHOD(WeaponId, getWeaponId, 0, (), (this))
    VIRTUAL_METHOD(const char*, getItemBaseName, 2, (), (this))
    VIRTUAL_METHOD(const char*, getItemTypeName, 3, (), (this))
    VIRTUAL_METHOD(const char*, getPlayerDisplayModel, 6, (), (this))
    VIRTUAL_METHOD(const char*, getWorldDisplayModel, 7, (), (this))
    VIRTUAL_METHOD(std::uint8_t, getRarity, 12, (), (this))

    int getCapabilities() noexcept
    {
        return *reinterpret_cast<int*>(this + 0x148);
    }

    bool isPaintable() noexcept
    {
        return getCapabilities() & 1; // ITEM_CAP_PAINTABLE
    }

    const char* getDefinitionName() noexcept
    {
        return *reinterpret_cast<const char**>(this + 0x1DC);
    }
};

struct ItemListEntry {
    int itemDef;
    int paintKit;
    PAD(20)

    auto weaponId() const noexcept
    {
        return static_cast<WeaponId>(itemDef);
    }
};

class EconLootListDefinition {
public:
    VIRTUAL_METHOD(const char*, getName, 0, (), (this))
    VIRTUAL_METHOD(const UtlVector<ItemListEntry>&, getLootListContents, 1, (), (this))
};

class EconItemSetDefinition {
public:
    VIRTUAL_METHOD(const char*, getLocKey, 1, (), (this))
    VIRTUAL_METHOD(int, getItemCount, 4, (), (this))
    VIRTUAL_METHOD(WeaponId, getItemDef, 5, (int index), (this, index))
    VIRTUAL_METHOD(int, getItemPaintKit, 6, (int index), (this, index))
};

struct EconItemQualityDefinition {
    int value;
    const char* name;
    unsigned weight;
    bool explicitMatchesOnly;
    bool canSupportSet;
    const char* hexColor;
};

struct AlternateIconData {
    UtlString simpleName;
    UtlString largeSimpleName;
    UtlString iconURLSmall;
    UtlString iconURLLarge;
    PAD(28)
};

struct EconMusicDefinition
{
    int id;
    const char* name;
    const char* nameLocalized;
    PAD(8)
    const char* inventoryImage;
};

class ItemSchema {
public:
    PAD(0x88)
    UtlMap<int, EconItemQualityDefinition> qualities;
    PAD(0x48)
    UtlMap<int, EconItemDefinition*> itemsSorted;
    PAD(0x60)
    UtlMap<int, const char*> revolvingLootLists;
    PAD(0x80)
    UtlMap<std::uint64_t, AlternateIconData> alternateIcons;
    PAD(0x48)
    UtlMap<int, PaintKit*> paintKits;
    UtlMap<int, StickerKit*> stickerKits;
    PAD(0x11C)
    UtlMap<int, EconMusicDefinition*> musicKits;

    VIRTUAL_METHOD(EconItemDefinition*, getItemDefinitionInterface, 4, (WeaponId id), (this, id))
    VIRTUAL_METHOD(const char*, getRarityName, 19, (uint8_t rarity), (this, rarity))
    VIRTUAL_METHOD(int, getItemSetCount, 28, (), (this))
    VIRTUAL_METHOD(EconItemSetDefinition*, getItemSet, 29, (int index), (this, index))
    VIRTUAL_METHOD(EconLootListDefinition*, getLootList, 32, (int index), (this, index))
    VIRTUAL_METHOD(int, getLootListCount, 34, (), (this))
    VIRTUAL_METHOD(EconItemDefinition*, getItemDefinitionByName, 42, (const char* name), (this, name))
};

class ItemSystem {
public:
    VIRTUAL_METHOD(ItemSchema*, getItemSchema, 0, (), (this))
};
