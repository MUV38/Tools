#include "FileSystem.h"

#include <Shlwapi.h>

using namespace std::experimental;

namespace myfilesystem {

// ��΃p�X���瑊�΃p�X���擾
filesystem::path relative(const filesystem::path& path, const filesystem::path& base)
{
	filesystem::path basePath(base);
	if (filesystem::is_directory(basePath))
	{
		basePath = base.string() + "\\";
	}

	wchar_t relativePath[256] = L"\0";
	PathRelativePathTo(
		relativePath,
		basePath.c_str(),
		filesystem::is_directory(path) ? FILE_ATTRIBUTE_DIRECTORY : FILE_ATTRIBUTE_NORMAL,
		path.c_str(),
		filesystem::is_directory(path) ? FILE_ATTRIBUTE_DIRECTORY : FILE_ATTRIBUTE_NORMAL
	);

	return filesystem::path(relativePath);
}

} // namespace myfilesystem