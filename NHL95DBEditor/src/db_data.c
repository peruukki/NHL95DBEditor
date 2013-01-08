#include <stdio.h>
#include <string.h>
#include "db_data.h"

void db_data_init(void *data, size_t data_length)
{
  memset(data, 0, data_length);
}

offset_t db_data_append_space(db_data_t *db_data, offset_t offset,
                              size_t length)
{
  size_t space_left = sizeof(db_data->data) - db_data->length;
  size_t start_offset;

  if (space_left < length)
    {
      printf("Can't append %lu bytes: only %ld bytes space left",
             length, space_left);
      return INVALID_DB_DATA_OFFSET;
    }

  start_offset = (offset == INVALID_DB_DATA_OFFSET) ? db_data->length : offset;
  if (start_offset < db_data->length)
    {
      memmove(db_data->data + (start_offset + length),
              db_data->data + start_offset, db_data->length - start_offset);
    }

  db_data->length += length;
  return (offset_t) start_offset;
}

offset_t db_data_append_data(db_data_t *db_data, void *data,
                             size_t data_length)
{
  offset_t offset;

  offset = db_data_append_space(db_data, INVALID_DB_DATA_OFFSET, data_length);
  if (offset != INVALID_DB_DATA_OFFSET)
    {
      memcpy(db_data->data + offset, data, data_length);
    }

  return offset;
}
