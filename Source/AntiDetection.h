#pragma once

#include <Windows.h>
#include <winternl.h>
#include <cstddef>
#include <memory>

class AntiDetection
{
public:
    explicit AntiDetection(const HMODULE hModule) : hModule(hModule) 
    {
        removeModule();
        removeHeader();
    }

    AntiDetection(const AntiDetection&) = delete;
    AntiDetection& operator=(const AntiDetection&) = delete;

    AntiDetection(AntiDetection&&) = delete;
    AntiDetection& operator=(AntiDetection&&) = delete;

    ~AntiDetection() 
    {
        restoreHeader();
        restoreModule();
    }
private:
    typedef struct _PEB_LDR_DATA_FULL 
    {
        ULONG Length;
        UCHAR Initialized;
        PVOID SsHandle;
        LIST_ENTRY InLoadOrderModuleList;
        LIST_ENTRY InMemoryOrderModuleList;
        LIST_ENTRY InInitializationOrderModuleList;
        PVOID EntryInProgress;
    } PEB_LDR_DATA_FULL, * PPEB_LDR_DATA_FULL;

    typedef struct _LDR_DATA_TABLE_ENTRY_FULL 
    {
        LIST_ENTRY InLoadOrderLinks;
        LIST_ENTRY InMemoryOrderLinks;
        LIST_ENTRY InInitializationOrderLinks;
        PVOID DllBase;
        PVOID EntryPoint;
        ULONG SizeOfImage;
        UNICODE_STRING FullDllName;
        UNICODE_STRING BaseDllName;
        ULONG Flags;
        WORD LoadCount;
        WORD TlsIndex;
        union
        {
            LIST_ENTRY HashLinks;
            struct
            {
                PVOID SectionPointer;
                ULONG CheckSum;
            } DUMMYSTRUCTNAME;
        } DUMMYUNIONNAME;
        union
        {
            ULONG TimeDateStamp;
            PVOID LoadedImports;
        } DUMMYUNIONNAME2;
        _ACTIVATION_CONTEXT* EntryPointActivationContext;
        PVOID PatchInformation;
        LIST_ENTRY ForwarderLinks;
        LIST_ENTRY ServiceTagLinks;
        LIST_ENTRY StaticLinks;
    } LDR_DATA_TABLE_ENTRY_FULL, * PLDR_DATA_TABLE_ENTRY_FULL;

    typedef struct _UNLINKED_MODULE 
    {
        HMODULE hModule;
        PLIST_ENTRY RealInLoadOrderLinks;
        PLIST_ENTRY RealInMemoryOrderLinks;
        PLIST_ENTRY RealInInitializationOrderLinks;
        PLDR_DATA_TABLE_ENTRY_FULL LdrDataTableEntry;
    } UNLINKED_MODULE, * PUNLINKED_MODULE;

    bool removeHeader() noexcept;
    bool restoreHeader() noexcept;
    bool removeModule() noexcept;
    bool restoreModule() noexcept;

    static HMODULE GetSelfModuleHandle() 
    {
        MEMORY_BASIC_INFORMATION mbi;

        return VirtualQuery(&GetSelfModuleHandle, &mbi, sizeof mbi) != 0
            ? static_cast<HMODULE>(mbi.AllocationBase) : nullptr;
    }

    static constexpr auto UnlinkLink(LIST_ENTRY* const source) noexcept
    {
        source->Flink->Blink = source->Blink;
        source->Blink->Flink = source->Flink;
    }

    static constexpr auto RelinkLink(LIST_ENTRY* const source, LIST_ENTRY* const destenation) noexcept
    {
        destenation->Flink->Blink = source;
        destenation->Blink->Flink = source;
        source->Blink = destenation->Blink;
        source->Flink = destenation->Flink;
    }
    
    HMODULE hModule = nullptr;
    std::unique_ptr<UNLINKED_MODULE> UnlinkedModule;
    struct PE_HEADER 
    {
        std::unique_ptr<std::byte[]> data;
        DWORD size = NULL;
    } peHeader;
};