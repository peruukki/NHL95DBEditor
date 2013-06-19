#pragma once

#include "common_defs.h"
#include "db_data.h"
#include "teams.h"

bool_t read_player_data(player_db_data_t *db_data);

bool_t dump_player_data(player_db_data_t *db_data);

bool_t add_duplicate_player_data(team_data_t *src_team,
                                 team_data_t *dst_team,
                                 number_1_t new_team_index,
                                 player_db_data_t *player_data);

bool_t modify_player_data(player_db_data_t *db_data);

bool_t modify_goalie_data(player_db_data_t *db_data);

bool_t write_player_data(player_db_data_t *db_data);
