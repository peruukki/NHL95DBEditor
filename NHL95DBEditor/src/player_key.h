#pragma once

#include "common_defs.h"
#include "output.h"
#include "teams.h"

typedef struct
{
  number_1_t team;
  number_1_t jersey;
  char position;
  char first[16];
  char last[17];
  offset_t ofs_attributes;
  offset_t ofs_career_stats;
  offset_t ofs_season_stats;
  number_1_t unknown[4];
} player_key_t;

bool_t key_is_goalie(player_key_t *key);

void show_player_key(player_key_t *key, size_t ofs_key, team_data_t *team, format_t format);

void print_player_key_footer(format_t format);

void print_player_key_header(format_t format);
