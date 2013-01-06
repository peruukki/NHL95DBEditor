#pragma once

#define INVALID_DB_DATA_OFFSET ((offset_t) -1)

typedef struct
{
  unsigned char data[65000];
  size_t length;
} db_data_t;

void db_data_init(void *data, size_t data_length);

offset_t db_data_append_space(db_data_t *db_data, size_t length);
