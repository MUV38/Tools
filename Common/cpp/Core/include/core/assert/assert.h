#pragma once

#include <cassert>

#if _DEBUG
#define ASSERT(CONDITION) assert(CONDITION)
#define ASSERT_MSG(CONDITION, MESSAGE) assert(CONDITION, MESSAGE)
#else // _DEBUG
#define ASSERT(CONDITION)
#define ASSERT_MSG(CONDITION, MESSAGE)
#endif // _DEBUG