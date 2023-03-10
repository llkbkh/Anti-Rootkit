#pragma once
#include "ProcessInfoEx.h"
#include "Token.h"
#include "EventData.h"

struct FormatHelper {
	static CString ToBinary(ULONGLONG value);
	static CString TimeSpanToString(int64_t ts);
	static CString FormatWithCommas(long long size);
	static CString TimeToString(int64_t time, bool includeMS = true);
	static CString PrivilegeAttributesToString(DWORD pattributes);
	static PCWSTR VirtualizationStateToString(WinSys::VirtualizationState state);
	static PCWSTR IntegrityToString(WinSys::IntegrityLevel level);
	static PCWSTR SidNameUseToString(SID_NAME_USE use);
	static CString SidAttributesToString(WinSys::SidGroupAttributes attributes);
	static PCWSTR PriorityClassToString(WinSys::ProcessPriorityClass pc);
	static CString JobCpuRateControlFlagsToString(DWORD flags);
	static PCWSTR IoPriorityToString(WinSys::IoPriority io);
	static CString ComFlagsToString(WinSys::ComFlags flags);
	static PCWSTR ComApartmentToString(WinSys::ComFlags flags);
	static CString ProcessAttributesToString(ProcessAttributes attributes);
	static CString FormatHWndOrNone(HWND hWnd);
	static PCWSTR ObjectTypeToString(int type);
	static CString MajorFunctionToString(UCHAR mf);
	static CString VirtualAllocFlagsToString(DWORD flags, bool withNumeric = false);
	static CString FormatTime(LONGLONG ts);
	static std::wstring FormatProperty(const EventData* data, const EventProperty& prop);
};