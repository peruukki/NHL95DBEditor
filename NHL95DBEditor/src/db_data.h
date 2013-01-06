#pragma once

typedef struct
{
  unsigned char data[65000];
  size_t length;
} db_data_t;

void db_data_init(db_data_t *db_data);

unsigned char *db_data_append_space(db_data_t *db_data, size_t length);
