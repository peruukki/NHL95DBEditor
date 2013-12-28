#pragma once

#include <stdio.h>

#define INFO(fmt, ...) printf(fmt, ##__VA_ARGS__)

#ifdef _DEBUG
#define DEBUG(fmt, ...) printf(fmt, ##__VA_ARGS__)
#else
#define DEBUG(fmt, ...)
#endif /* NDEBUG */
