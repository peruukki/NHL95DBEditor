#pragma once

#include "common_defs.h"
#include "player_key.h"

typedef struct stats_player_t
{
  number_2 games_played;
  number_2 goals;
  number_2 assists;
  number_2 points;
  number_2 pp_goals;
  number_2 sh_goals;
  number_2 penalty_minutes;
  number_2 shots;
  number_s_2 plus_minus;
} stats_player;

typedef struct stats_goalie_t
{
  number_2 games_played;
  number_2 wins;
  number_2 losses;
  number_2 ties;
  number_2 shutouts;
  number_2 empty_nets;
  number_2 minutes;
  number_2 goals_against;
  number_2 gaa;
  number_2 saves;
  number_2 save_pct;
} stats_goalie;

typedef struct stats_career_player_t
{
  stats_player regular_season;
  stats_player playoffs;
  number_1 unknown[4];
} stats_career_player;

typedef struct stats_season_player_t
{
  stats_player regular_season;
  stats_player playoffs;
  number_1 unknown[11];
} stats_season_player;

typedef struct stats_career_goalie_t
{
  stats_goalie regular_season;
  stats_goalie playoffs;
  number_1 unknown[10];
} stats_career_goalie, stats_season_goalie;

void show_stats_career(unsigned char *stats_data, key_player *key);

void show_stats_season(unsigned char *stats_data, key_player *key);
