#pragma once

#include "common_defs.h"
#include "player_key.h"

typedef struct
{
  number_2_t games_played;
  number_2_t goals;
  number_2_t assists;
  number_2_t points;
  number_2_t pp_goals;
  number_2_t sh_goals;
  number_2_t penalty_minutes;
  number_2_t shots;
  number_s_2_t plus_minus;
} player_stats_t;

typedef struct
{
  number_2_t games_played;
  number_2_t wins;
  number_2_t losses;
  number_2_t ties;
  number_2_t shutouts;
  number_2_t empty_nets;
  number_2_t minutes;
  number_2_t goals_against;
  number_2_t gaa;
  number_2_t saves;
  number_2_t save_pct;
} goalie_stats_t;

typedef struct
{
  player_stats_t regular_season;
  player_stats_t playoffs;
  number_1_t unknown[4];
} player_stats_career_t;

typedef struct
{
  player_stats_t regular_season;
  player_stats_t playoffs;
  number_1_t unknown[11];
} player_stats_season_t;

typedef struct
{
  goalie_stats_t regular_season;
  goalie_stats_t playoffs;
  number_1_t unknown[10];
} goalie_stats_career_t, goalie_stats_season_t;

void show_stats_career(unsigned char *stats_data, player_key_t *key);

void show_stats_season(unsigned char *stats_data, player_key_t *key);
