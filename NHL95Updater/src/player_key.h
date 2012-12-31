#pragma once

#include "common_defs.h"

typedef struct key_player_t
{
  char team;
  char jersey;
  char position;
  char first[16];
  char last[17];
  offset ofs_attributes;
  offset ofs_career_stats;
  offset ofs_season_stats;
  number_1 unknown[4];
} key_player;

void show_key_player(key_player *key);
