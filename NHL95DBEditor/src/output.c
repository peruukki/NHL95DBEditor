#include "common_defs.h"
#include "output.h"

const char *get_format_str_number(format_t format)
{
  switch (format)
    {
    case FORMAT_CSV:
      return "%d";
    case FORMAT_JSON:
      return "\"%s\": %d";
    case FORMAT_PLAIN:
      return "%s %3d";
    default:
      INFO("Unknown format value %d\n", format);
      return "";
    }
}

void print_delimiter(format_t format)
{
  switch (format)
    {
    case FORMAT_CSV:
      INFO(",");
      break;
    case FORMAT_JSON:
      INFO(", ");
      break;
    case FORMAT_PLAIN:
      INFO(" ");
      break;
    default:
      INFO("<Unknown format value %d>", format);
      break;
    }
}

void print_field_name(const char *field, format_t format)
{
  switch (format)
    {
    case FORMAT_CSV:
      break;
    case FORMAT_JSON:
      {
        print_field_value_string(field, format);
        INFO(": ");
        break;
      }
    case FORMAT_PLAIN:
      {
        print_field_value_string(field, format);
        INFO(" ");
        break;
      }
    default:
      {
        INFO("Unknown format value %d\n", format);
        break;
      }
    }
}

void print_field_value_number(int value, format_t format)
{
  switch (format)
    {
    case FORMAT_CSV:
    case FORMAT_JSON:
      {
        INFO("%d", value);
        break;
      }
    case FORMAT_PLAIN:
      {
        INFO("%3d", value);
        break;
      }
    default:
      {
        INFO("Unknown format value %d\n", format);
        break;
      }
    }
}

void print_field_value_string(const char *value, format_t format)
{
  switch (format)
    {
    case FORMAT_CSV:
    case FORMAT_PLAIN:
      {
        INFO("%s", value);
        break;
      }
    case FORMAT_JSON:
      {
        INFO("\"%s\"", value);
        break;
      }
    default:
      {
        INFO("Unknown format value %d\n", format);
        break;
      }
    }
}
