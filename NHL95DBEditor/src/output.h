#pragma once

#include <stdio.h>

typedef enum
{
  FORMAT_CSV,
  FORMAT_JSON,
  FORMAT_PLAIN,
  FORMAT_UNKNOWN /* Must be last */
} format_t;

#define INFO(fmt, ...) printf(fmt, ##__VA_ARGS__)

#ifdef _DEBUG
#define DEBUG(fmt, ...) printf(fmt, ##__VA_ARGS__)
#else
#define DEBUG(fmt, ...)
#endif /* NDEBUG */

void print_delimiter(format_t format);

void print_field_name(const char *field, format_t format);

void print_field_value_number(int value, format_t format);

void print_field_value_string(const char *value, format_t format);
