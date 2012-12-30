#include "constants.h"

#define TEAM_DATA_SIZE 704

typedef struct team_stats_t
{
  NUMBER1 games_played;
  NUMBER1 wins;
  NUMBER1 losses;
  NUMBER1 ties;
  NUMBER2 goals_for;
  NUMBER2 goals_against;
  NUMBER2 pp_goals_for;
  NUMBER2 pp_advantages;
  NUMBER2 pp_goals_against;
  NUMBER2 times_shorthanded;
  NUMBER2 penalty_minutes;
} team_stats;

typedef struct team_data_t
{
  char abbr[5];
  char long_name[21];
  char short_name[13];
  NUMBER1 division;
  team_stats regular_season_stats;
  team_stats playoff_stats;
  NUMBER1 rest[TEAM_DATA_SIZE - 2 * sizeof(team_stats)];
} team_data;

void show_team_data(team_data *team);

void read_team_data(void);
