#include <iostream>

#include "core/core.h"
#include "model/modelLoaderRaw.h"

using namespace std::experimental;

// 生データ → 中間データ出力
int ConvertRawToIntermediate(const wchar_t* inputFilePath, const wchar_t* outputFilePath);
// 中間データからバイナリ出力
int ConvertIntermediateToBinary(const wchar_t* inputFilePath, const wchar_t* outputFilePath);

int main(int argc, char* argv[])
{
	const int errorCode = -1;

	if (argc < 2) { return errorCode; }

	// モードごとのコンバート
	const char* mode = argv[1];
	// 生データ → 中間データ
	if (strstr(mode, "raw") != nullptr)
	{
		if (argc < 4) { return errorCode; }

		filesystem::path inputPath = argv[2];
		filesystem::path outputPath = argv[3];
		return ConvertRawToIntermediate(inputPath.c_str(), outputPath.c_str());
	}
	// 中間データ → バイナリ
	else if (strstr(mode, "intermediate") != nullptr)
	{
		if (argc < 4) { return errorCode; }

		filesystem::path inputPath = argv[2];
		filesystem::path outputPath = argv[3];
		return ConvertIntermediateToBinary(inputPath.c_str(), outputPath.c_str());
	}

	return 0;
}

// 生データから中間データ出力
int ConvertRawToIntermediate(const wchar_t* inputFilePath, const wchar_t* outputFilePath)
{
	const int errorCode = -1;

	filesystem::path inputPath = inputFilePath;
	filesystem::path outputPath = outputFilePath;

	ModelLoaderRaw loader;

	std::cout << "---Begin load file [" << inputPath.filename().string().c_str() << "]---" << std::endl;
	if (loader.load(inputPath.c_str()))
	{
		std::cout << "---Succeed load file---" << std::endl;

		std::cout << std::endl;

		std::cout << "---Begin output file [" << outputPath.filename().string().c_str() << "]---" << std::endl;
		if (loader.exportToJson(outputPath.c_str()))
		{
			std::cout << "---Succeed load file---" << std::endl;
		}
		else
		{
			std::cout << "---Failed load file---" << std::endl;
			return errorCode;
		}
	}
	else
	{
		std::cout << "---Failed load file---" << std::endl;
		return errorCode;
	}

	return 0;
}

// 中間データからバイナリ出力
int ConvertIntermediateToBinary(const wchar_t* inputFilePath, const wchar_t* outputFilePath)
{
	return -1;
}
