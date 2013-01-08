#pragma once

#include "common_defs.h"
#include "db_data.h"

typedef struct
{
  number_1_t games_played;
  number_1_t wins;
  number_1_t losses;
  number_1_t ties;
  number_2_t goals_for;
  number_2_t goals_against;
  number_2_t pp_goals_for;
  number_2_t pp_advantages;
  number_2_t pp_goals_against;
  number_2_t times_shorthanded;
  number_2_t penalty_minutes;
} team_stats_t;

typedef struct
{
  number_1_t penalty_killing;
  number_1_t power_play;
  number_1_t unknown_1;
  number_1_t unknown_2;
  number_1_t shooting;
  number_1_t skating;
  number_1_t passing;
  number_1_t defense;
  number_1_t checking;
  number_1_t unknown_3;
  number_1_t goaltending;
  number_1_t overall;
} team_scouting_report_t;

typedef struct
{
  index_t left_wing;
  index_t center;
  index_t right_wing;
} team_forward_line_t;

typedef struct
{
  index_t left_wing;
  index_t center;
} team_pk_forward_line_t;

typedef struct
{
  index_t left_defense;
  index_t right_defense;
} team_defense_line_t;

typedef struct
{
  index_t starting_goalie;
  index_t backup_goalie;
} team_goalie_line_t;

typedef struct
{
  index_t first_choice;
  index_t second_choice;
} team_extra_attackers_t;

typedef struct
{
  team_forward_line_t forwards;
  team_defense_line_t defensemen;
} team_pp_line_t;

typedef struct
{
  team_pk_forward_line_t forwards;
  team_defense_line_t defensemen;
} team_pk_line_t;

typedef struct
{
  team_forward_line_t fwd_lines[4];
  team_defense_line_t def_lines[3];
  team_pp_line_t pp_lines[2];
  team_pk_line_t pk_lines[2];
  team_goalie_line_t goalies;
  team_extra_attackers_t extra_attackers;
  index_t scratches[8];
} team_lines_t;

typedef struct
{
  char abbreviation[5];
  char long_name[21];
  char short_name[13];
  number_1_t division;
  team_stats_t regular_season_stats;
  team_stats_t playoff_stats;
  offset_t players[25];
  offset_t goalies[3];
  team_lines_t lines;
  team_lines_t original_lines;
  number_1_t padding[448];
  team_scouting_report_t scouting_report;
} team_data_t;

typedef struct
{
  char abbreviation[5];
  char long_name[21];
  char short_name[13];
  number_1_t division;
  team_stats_t regular_season_stats;
  team_stats_t playoff_stats;
} team_stats_career_t;

#define FILE_TEAMS "TEAMS.DB"
#define FILE_CARTEAMS "CARTEAMS.DB"

bool_t read_team_data(team_db_data_t *db_data);

bool_t add_team(team_db_data_t *team_data,
                player_db_data_t *player_data);
