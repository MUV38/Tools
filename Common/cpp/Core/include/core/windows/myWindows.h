#pragma once

#ifndef NOMINMAX
#define NOMINMAX	// min, maxマクロを定義しないようにする
#endif // NOMINMAX

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN	// Windows ヘッダーからほとんど使用されていない部分を除外する
#endif // WIN32_LEAN_AND_MEAN

#include <Windows.h>