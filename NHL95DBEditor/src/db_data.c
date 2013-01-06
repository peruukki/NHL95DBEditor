#include <stdio.h>
#include <string.h>
#include "db_data.h"

void db_data_init(db_data_t *db_data)
{
  memset(db_data, 0, sizeof(*db_data));
}

unsigned char *db_data_append_space(db_data_t *db_data, size_t length)
{
  size_t space_left = sizeof(db_data->data) - db_data->length;
  size_t start_offset;

  if (space_left < length)
    {
      printf("Can't append %lu bytes: only %ld bytes space left",
             length, space_left);
      return NULL;
    }

  start_offset = db_data->length;
  db_data->length += length;
  return db_data->data + start_offset;
}
