#pragma once

#include "common_defs.h"
#include "db_data.h"

typedef struct
{
  db_data_t key_data;
  db_data_t att_data;
  db_data_t career_data;
  db_data_t season_data;
} player_db_data_t;

bool_t read_player_data(player_db_data_t *db_data);
