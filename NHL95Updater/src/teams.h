#include "constants.h"

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

typedef struct team_data_t
{
  char abbr[5];
  char long_name[21];
  char short_name[13];
  number_1 division;
  team_stats regular_season_stats;
  team_stats playoff_stats;
  number_1 rest[TEAM_DATA_SIZE - 2 * sizeof(team_stats)];
} team_data;

void show_team_data(team_data *team);

void read_team_data(void);
