#include "stdafx.h"
#include "KeyObjectType.h"
#include "NtDll.h"

KeyObjectType::KeyObjectType(int index, PCWSTR name) : ObjectType(index, name) {
}

CString KeyObjectType::GetDetails(HANDLE hKey) {
	CString details;
	BYTE buffer[1 << 12];
	ULONG len;
	if (NT_SUCCESS(::NtQueryKey(hKey, KeyBasicInformation, buffer, sizeof(buffer), &len))) {
		auto info = (KEY_BASIC_INFORMATION*)buffer;
		details.Format(L"Last Write: %s",
			(PCWSTR)CTime(*(FILETIME*)&info->LastWriteTime.QuadPart).Format(L"%D %X"));
	}
	return details;
}
