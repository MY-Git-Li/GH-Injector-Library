#pragma once

#include "Injection.h"

#define RELOC_FLAG86(RelInfo) ((RelInfo >> 0x0C) == IMAGE_REL_BASED_HIGHLOW)
#define RELOC_FLAG64(RelInfo) ((RelInfo >> 0x0C) == IMAGE_REL_BASED_DIR64)

#ifdef _WIN64
#define RELOC_FLAG RELOC_FLAG64
#else
#define RELOC_FLAG RELOC_FLAG86
#endif

using f_DLL_ENTRY_POINT	= BOOL(WINAPI*)(HINSTANCE hDll, DWORD dwReason, void * pReserved);

namespace MMAP_NATIVE
{
	using namespace NATIVE;

	ALIGN struct MODULE_DEPENDENCY_LIST_ENTRY
	{
		ALIGN MODULE_DEPENDENCY_LIST_ENTRY * Next;
		ALIGN HINSTANCE hModule;
		ALIGN DWORD SizeOfImage;
	};

	ALIGN struct MANUAL_MAPPING_FUNCTION_TABLE
	{
		ALIGN NT_FUNC_LOCAL(NtOpenFile);
		ALIGN NT_FUNC_LOCAL(NtReadFile);
		ALIGN NT_FUNC_LOCAL(NtSetInformationFile);
		ALIGN NT_FUNC_LOCAL(NtQueryInformationFile);

		ALIGN NT_FUNC_LOCAL(NtCreateSection);
		ALIGN NT_FUNC_LOCAL(NtMapViewOfSection);
		ALIGN NT_FUNC_LOCAL(NtUnmapViewOfSection);

		ALIGN NT_FUNC_LOCAL(NtAllocateVirtualMemory);
		ALIGN NT_FUNC_LOCAL(NtProtectVirtualMemory);
		ALIGN NT_FUNC_LOCAL(NtFreeVirtualMemory);

		ALIGN NT_FUNC_LOCAL(RtlMoveMemory);
		ALIGN NT_FUNC_LOCAL(RtlAllocateHeap);
		ALIGN NT_FUNC_LOCAL(RtlFreeHeap);

		ALIGN NT_FUNC_LOCAL(LdrGetDllHandleEx);
		ALIGN NT_FUNC_LOCAL(LdrpLoadDll);
		ALIGN NT_FUNC_LOCAL(LdrUnloadDll);
		ALIGN NT_FUNC_LOCAL(LdrGetProcedureAddress);

		ALIGN NT_FUNC_LOCAL(LdrLockLoaderLock);
		ALIGN NT_FUNC_LOCAL(LdrUnlockLoaderLock);

		ALIGN NT_FUNC_LOCAL(RtlAnsiStringToUnicodeString);
		ALIGN NT_FUNC_LOCAL(RtlUnicodeStringToAnsiString);
		ALIGN NT_FUNC_LOCAL(RtlInitUnicodeString);
		ALIGN NT_FUNC_LOCAL(RtlHashUnicodeString);

		ALIGN NT_FUNC_LOCAL(RtlRbInsertNodeEx);
		ALIGN NT_FUNC_LOCAL(RtlRbRemoveNode);

		ALIGN NT_FUNC_LOCAL(RtlGetSystemTimePrecise);

		ALIGN NT_FUNC_LOCAL(NtClose);

		ALIGN NT_FUNC_LOCAL(LdrpPreprocessDllName);
		ALIGN NT_FUNC_LOCAL(RtlInsertInvertedFunctionTable);
		ALIGN NT_FUNC_LOCAL(LdrpHandleTlsData);

		ALIGN NT_FUNC_LOCAL(LdrpModuleBaseAddressIndex);
		ALIGN NT_FUNC_LOCAL(LdrpMappingInfoIndex);
		ALIGN NT_FUNC_LOCAL(LdrpHashTable);
		ALIGN NT_FUNC_LOCAL(LdrpHeap);

		void * pLdrpHeap;

		MANUAL_MAPPING_FUNCTION_TABLE();
	};
	
	ALIGN struct MANUAL_MAPPING_DATA
	{
		ALIGN HINSTANCE	hRet{ 0 };
		ALIGN DWORD		Flags{ 0 };
		ALIGN NTSTATUS	ntRet{ 0 };

		ALIGN UNICODE_STRING DllPath{ 0 };
		ALIGN wchar_t szPathBuffer[MAX_PATH]{ 0 };

		ALIGN UNICODE_STRING DllName{ 0 };
		ALIGN wchar_t szNameBuffer[MAX_PATH]{ 0 };

		ALIGN wchar_t NtPathPrefix[8] = L"\\??\\\0\0\0";
		ALIGN wchar_t Kernel32Name[16] = L"kernel32.dll";

		ALIGN LDR_DATA_TABLE_ENTRY * pEntryOut{ 0 };

		ALIGN MODULE_DEPENDENCY_LIST_ENTRY * First{ 0 };

		ALIGN UINT ModuleCount{ 0 };

		ALIGN MANUAL_MAPPING_FUNCTION_TABLE f;
	};

	DWORD ManualMap(const wchar_t * szDllFile, HANDLE hTargetProc, LAUNCH_METHOD Method, DWORD Flags, HINSTANCE & hOut, ERROR_DATA & error_data);
}

#ifdef _WIN64

namespace MMAP_WOW64
{
	using namespace WOW64;

	ALIGN_86 struct MANUAL_MAPPING_FUNCTION_TABLE_WOW64
	{
		ALIGN_86 WOW64_FUNCTION_POINTER_LOCAL(NtOpenFile);
		ALIGN_86 WOW64_FUNCTION_POINTER_LOCAL(NtReadFile);
		ALIGN_86 WOW64_FUNCTION_POINTER_LOCAL(NtSetInformationFile);
		ALIGN_86 WOW64_FUNCTION_POINTER_LOCAL(NtQueryInformationFile);

		ALIGN_86 WOW64_FUNCTION_POINTER_LOCAL(NtCreateSection);
		ALIGN_86 WOW64_FUNCTION_POINTER_LOCAL(NtMapViewOfSection);
		ALIGN_86 WOW64_FUNCTION_POINTER_LOCAL(NtUnmapViewOfSection);

		ALIGN_86 WOW64_FUNCTION_POINTER_LOCAL(NtAllocateVirtualMemory);
		ALIGN_86 WOW64_FUNCTION_POINTER_LOCAL(NtProtectVirtualMemory);
		ALIGN_86 WOW64_FUNCTION_POINTER_LOCAL(NtFreeVirtualMemory);

		ALIGN_86 WOW64_FUNCTION_POINTER_LOCAL(RtlMoveMemory);
		ALIGN_86 WOW64_FUNCTION_POINTER_LOCAL(RtlAllocateHeap);
		ALIGN_86 WOW64_FUNCTION_POINTER_LOCAL(RtlFreeHeap);

		ALIGN_86 WOW64_FUNCTION_POINTER_LOCAL(LdrGetDllHandleEx);
		ALIGN_86 WOW64_FUNCTION_POINTER_LOCAL(LdrpLoadDll);
		ALIGN_86 WOW64_FUNCTION_POINTER_LOCAL(LdrUnloadDll);
		ALIGN_86 WOW64_FUNCTION_POINTER_LOCAL(LdrGetProcedureAddress);

		ALIGN_86 WOW64_FUNCTION_POINTER_LOCAL(LdrLockLoaderLock);
		ALIGN_86 WOW64_FUNCTION_POINTER_LOCAL(LdrUnlockLoaderLock);

		ALIGN_86 WOW64_FUNCTION_POINTER_LOCAL(RtlAnsiStringToUnicodeString);
		ALIGN_86 WOW64_FUNCTION_POINTER_LOCAL(RtlUnicodeStringToAnsiString);
		ALIGN_86 WOW64_FUNCTION_POINTER_LOCAL(RtlInitUnicodeString);
		ALIGN_86 WOW64_FUNCTION_POINTER_LOCAL(RtlHashUnicodeString);

		ALIGN_86 WOW64_FUNCTION_POINTER_LOCAL(RtlRbInsertNodeEx);
		ALIGN_86 WOW64_FUNCTION_POINTER_LOCAL(RtlRbRemoveNode);

		ALIGN_86 WOW64_FUNCTION_POINTER_LOCAL(RtlGetSystemTimePrecise);

		ALIGN_86 WOW64_FUNCTION_POINTER_LOCAL(NtClose);

		ALIGN_86 WOW64_FUNCTION_POINTER_LOCAL(LdrpPreprocessDllName);
		ALIGN_86 WOW64_FUNCTION_POINTER_LOCAL(RtlInsertInvertedFunctionTable);
		ALIGN_86 WOW64_FUNCTION_POINTER_LOCAL(LdrpHandleTlsData);

		ALIGN_86 WOW64_FUNCTION_POINTER_LOCAL(LdrpModuleBaseAddressIndex);
		ALIGN_86 WOW64_FUNCTION_POINTER_LOCAL(LdrpMappingInfoIndex);
		ALIGN_86 WOW64_FUNCTION_POINTER_LOCAL(LdrpHashTable);
		ALIGN_86 WOW64_FUNCTION_POINTER_LOCAL(LdrpHeap);

		MANUAL_MAPPING_FUNCTION_TABLE_WOW64();
	};

	ALIGN_86 struct MANUAL_MAPPING_DATA_WOW64
	{
		ALIGN_86 DWORD	hRet{ 0 };
		ALIGN_86 DWORD	Flags{ 0 };
		ALIGN_86 DWORD	ntRet{ 0 };

		ALIGN_86 UNICODE_STRING32 DllPath{ 0 };
		ALIGN_86 wchar_t szPathBuffer[MAX_PATH]{ 0 };

		ALIGN_86 UNICODE_STRING32 DllName{ 0 };
		ALIGN_86 wchar_t szNameBuffer[MAX_PATH]{ 0 };

		ALIGN_86 wchar_t NtPathPrefix[8] = L"\\??\\\0\0\0";
		ALIGN_86 wchar_t Kernel32Name[16] = L"kernel32.dll";

		ALIGN_86 DWORD pEntryOut{ 0 };

		ALIGN_86 DWORD First{ 0 };

		ALIGN_86 DWORD ModuleCount{ 0 };

		ALIGN_86 MANUAL_MAPPING_FUNCTION_TABLE_WOW64 f;
	};

	DWORD ManualMap_WOW64(const wchar_t * szDllFile, HANDLE hTargetProc, LAUNCH_METHOD Method, DWORD Flags, HINSTANCE & hOut, ERROR_DATA & error_data);
}

#endif