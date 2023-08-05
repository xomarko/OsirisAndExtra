#pragma once

#include <type_traits>

#include "Constants/ClassId.h"
#include "Constants/Platform.h"

class Entity;
struct RecvTable;

struct ClientClass {
    std::add_pointer_t<Entity* __cdecl(int, int)> createFunction;
    void* createEventFunction;
    char* networkName;
    RecvTable* recvTable;
    ClientClass* next;
    ClassId classId;
};
