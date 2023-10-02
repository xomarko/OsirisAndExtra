#pragma once

#include "Item.h"
#include "ItemIDMap.h"
#include "Loadout.h"
#include "StorageUnitManager.h"
#include "XRayScanner.h"

#include "Response/ResponseQueue.h"

namespace inventory_changer::backend
{

    struct Items {
        ItemList inventory;
        Loadout loadout;
        ResponseQueue<> responseQueue;
        ItemIDMap itemIDMap;
        XRayScanner xRayScanner;
        StorageUnitManager storageUnitManager;
    };

}