#pragma once

#include "common_defs.h"

#define INVALID_DB_DATA_OFFSET ((offset_t) -1)

typedef struct
{
  unsigned char data[65000];
  size_t length;
} db_data_t;

typedef struct
{
  db_data_t teams;
  db_data_t carteams;
} team_db_data_t;

typedef struct
{
  db_data_t key_data;
  db_data_t att_data;
  db_data_t career_data;
  db_data_t season_data;
} player_db_data_t;

void db_data_init(void *data, size_t data_length);

offset_t db_data_append_space(db_data_t *db_data, offset_t offset,
                              size_t length);

offset_t db_data_append_data(db_data_t *db_data, void *data,
                             size_t data_length);
