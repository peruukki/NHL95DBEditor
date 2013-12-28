#pragma once

#include <stdio.h>

#define INFO(fmt, ...) printf(fmt, ##__VA_ARGS__)
