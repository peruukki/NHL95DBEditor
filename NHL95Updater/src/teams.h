#include "common_defs.h"

#define TEAM_DATA_SIZE 704

typedef struct team_stats_t
{
  number_1 games_played;
  number_1 wins;
  number_1 losses;
  number_1 ties;
  number_2 goals_for;
  number_2 goals_against;
  number_2 pp_goals_for;
  number_2 pp_advantages;
  number_2 pp_goals_against;
  number_2 times_shorthanded;
  number_2 penalty_minutes;
} team_stats;

typedef struct team_scouting_report_t
{
  number_1 penalty_killing;
  number_1 power_play;
  number_1 unknown_1;
  number_1 unknown_2;
  number_1 shooting;
  number_1 skating;
  number_1 passing;
  number_1 defense;
  number_1 checking;
  number_1 unknown_3;
  number_1 goaltending;
  number_1 overall;
} team_scouting_report;

typedef struct team_forward_line_t
{
  index left_wing;
  index center;
  index right_wing;
} team_forward_line;

typedef struct team_pk_forward_line_t
{
  index left_wing;
  index center;
} team_pk_forward_line;

typedef struct team_defense_line_t
{
  index left_defense;
  index right_defense;
} team_defense_line;

typedef struct team_goalie_line_t
{
  index starting_goalie;
  index backup_goalie;
} team_goalie_line;

typedef struct team_extra_attackers_t
{
  index first_choice;
  index second_choice;
} team_extra_attackers;

typedef struct team_pp_line_t
{
  team_forward_line forwards;
  team_defense_line defensemen;
} team_pp_line;

typedef struct team_pk_line_t
{
  team_pk_forward_line forwards;
  team_defense_line defensemen;
} team_pk_line;

typedef struct team_lines_t
{
  team_forward_line fwd_lines[4];
  team_defense_line def_lines[3];
  team_pp_line pp_lines[2];
  team_pk_line pk_lines[2];
  team_goalie_line goalies;
  team_extra_attackers extra_attackers;
  index scratches[8];
} team_lines;

typedef struct team_data_t
{
  char abbr[5];
  char long_name[21];
  char short_name[13];
  number_1 division;
  team_stats regular_season_stats;
  team_stats playoff_stats;
  offset players[25];
  offset goalies[3];
  team_lines lines;
  team_lines original_lines;
  number_1 padding[448];
  team_scouting_report scouting_report;
} team_data;

void show_team_data(team_data *team);

void read_team_data(void);
