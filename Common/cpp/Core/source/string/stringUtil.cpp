#include "pch.h"
#include "core/string/stringUtil.h"

#include "core/windows/MyWindows.h"

// string to wstring
std::wstring util::ToWstring(const std::string& str)
{
	if (str.length() > 0)
	{
		const size_t strLength = str.length();
		wchar_t* wlocal = new wchar_t[strLength + 1];
		wlocal[0] = L'\0';

		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, str.c_str(), static_cast<int>(strLength), wlocal, static_cast<int>(strLength + 1));

		std::wstring out(wlocal);
		delete[] wlocal;

		return out;
	}
	else
	{
		return L"";
	}
}

// wstring to string
std::string util::ToString(const std::wstring& str)
{
	const size_t strLength = str.length();
	char* local = new char[strLength + 1];
	local[0] = '\0';

	WideCharToMultiByte(CP_ACP, 0, str.c_str(), -1, local, static_cast<int>(strLength + 1), NULL, NULL);
	
	std::string out(local);
	delete[] local;

	return out;
}
