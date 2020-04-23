#pragma once

#ifndef _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#endif // _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING

#include <experimental/filesystem>

namespace myfilesystem {

//! @brief 絶対パスから相対パスを取得
std::experimental::filesystem::path relative(
	const std::experimental::filesystem::path& path, 
	const std::experimental::filesystem::path& base = std::experimental::filesystem::current_path()
);

} // namespace myfilesystem