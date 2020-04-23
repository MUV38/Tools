#pragma once

#ifndef _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#endif // _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING

#include <experimental/filesystem>

namespace myfilesystem {

//! @brief ��΃p�X���瑊�΃p�X���擾
std::experimental::filesystem::path relative(
	const std::experimental::filesystem::path& path, 
	const std::experimental::filesystem::path& base = std::experimental::filesystem::current_path()
);

} // namespace myfilesystem