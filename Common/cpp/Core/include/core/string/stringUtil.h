#pragma once

#include <string>

namespace util {

//! @brief string to wstring
std::wstring ToWstring(const std::string& str);

//! @brief wstring to string
std::string ToString(const std::wstring& str);

} // namespace util