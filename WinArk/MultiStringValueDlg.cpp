#include "stdafx.h"
#include "resource.h"
#include "MultiStringValueDlg.h"
#include "RegHelpers.h"

CMultiStringValueDlg::CMultiStringValueDlg(RegistryKey& key, PCWSTR name, bool readOnly) :
	m_Key(key), m_Name(name), m_ReadOnly(readOnly) {
}

const CString& CMultiStringValueDlg::GetValue() const {
	return m_Value;
}

bool CMultiStringValueDlg::IsModified() const {
	return m_Modified;
}

LRESULT CMultiStringValueDlg::OnInitDialog(UINT, WPARAM, LPARAM, BOOL&) {
	ULONG chars = 0;
	m_Key.QueryMultiStringValue(m_Name, nullptr, &chars);
	if (chars) {
		chars++;
		auto buffer = std::make_unique<WCHAR[]>(chars);
		ZeroMemory(buffer.get(), chars * sizeof(WCHAR));
		DWORD type;
		auto len = chars * 2;
		if (ERROR_SUCCESS != ::RegQueryValueEx(m_Key.Get(), m_Name, nullptr, &type, (PBYTE)buffer.get(), &len)) {
			EndDialog(IDRETRY);
			return 0;
		}
		std::for_each(buffer.get(), buffer.get() + chars - 1, [](auto& ch) {
			if (ch == 0)
				ch = L'\n';
			});
		m_Value = buffer.get();
		m_Value.Replace(L"\n", L"\r\n");
		SetDlgItemText(IDC_VALUE, m_Value);
	}
	if (m_ReadOnly) {
		((CEdit)GetDlgItem(IDC_VALUE)).SetReadOnly(TRUE);
	}
	SetDlgItemText(IDC_NAME, m_Name.IsEmpty() ? RegHelpers::DefaultValueName : m_Name);

	return TRUE;
}

LRESULT CMultiStringValueDlg::OnCloseCmd(WORD, WORD id, HWND, BOOL&) {
	if (id == IDOK) {
		CString text;
		GetDlgItemText(IDC_VALUE, text);
		m_Modified = text != m_Value;
		if (m_Modified)
			m_Value = text;
	}
	EndDialog(id);
	return 0;
}
