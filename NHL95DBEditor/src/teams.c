#include <stdio.h>
#include <string.h>
#include "common_defs.h"
#include "file_utils.h"
#include "teams.h"

static void show_team_stats(team_stats_t *stats)
{
  printf(" GP: %2u W: %2u L: %2u T: %2u GF: %3u GA: %3u PIM: %4u "
         "PPGF: %3u PPGA: %3u ADV: %3u TSH: %3u",
         stats->games_played, stats->wins, stats->losses, stats->ties,
         stats->goals_for, stats->goals_against, stats->penalty_minutes,
         stats->pp_goals_for, stats->pp_goals_against,
         stats->pp_advantages, stats->times_shorthanded);
}

static void show_offsets(offset_t offsets[], int count, char *title)
{
  int i;

  for (i = 0; i < count; i++)
    {
      if (offsets[i] == 0xFFFFFFFF)
        {
          printf(" %s%2u:     ", title, i);
        }
      else
        {
          printf(" %s%2u: %4x", title, i, offsets[i]);
        }
    }
}

static void show_team_players(team_data_t *team)
{
  int count;

  count = sizeof(team->players) / sizeof(team->players[0]);
  show_offsets(team->players, count, "P");
}

static void show_team_goalies(team_data_t *team)
{
  int count;

  count = sizeof(team->goalies) / sizeof(team->goalies[0]);
  show_offsets(team->goalies, count, "G");
}

static void show_team_lines(team_lines_t *lines)
{
  int i;
  int count;

  /* Forward lines */
  count = sizeof(lines->fwd_lines) / sizeof(lines->fwd_lines[0]);
  for (i = 0; i < count; i++)
    {
      team_forward_line_t *line = &lines->fwd_lines[i];

      printf(" F%u: %2u %2u %2u", i + 1,
             line->left_wing, line->center, line->right_wing);
    }

  /* Defense lines */
  count = sizeof(lines->def_lines) / sizeof(lines->def_lines[0]);
  for (i = 0; i < count; i++)
    {
      team_defense_line_t *line = &lines->def_lines[i];

      printf(" D%u: %2u %2u", i + 1,
             line->left_defense, line->right_defense);
    }

  /* Goalies */
  printf(" G1: %u G2: %u",
         lines->goalies.starting_goalie, lines->goalies.backup_goalie);

  /* Don't show everything, there's too much... */
  printf(" ...");
}

static void show_team_scouting_report(team_scouting_report_t *report)
{
  printf(" PK: %2u PP: %2u SH: %2u SK: %2u PS: %2u DE: %2u "
         "CH: %2u GT: %2u OA: %2u",
         report->penalty_killing, report->power_play, report->shooting,
         report->skating, report->passing, report->defense,
         report->checking, report->goaltending, report->overall);
}

static void show_raw_data(number_1_t *data, size_t length, char *title)
{
  size_t i;

  printf(" %s:", title);
  for (i = 0; i < length; i++)
    {
      if (data[i] != 0xFF)
        {
          printf(" %u: %3u", i, data[i]);
        }
    }
}

static void show_team_data(team_data_t *team)
{
  printf("TEAM: %-3s DIV: %3u", team->abbreviation, team->division);

  show_team_stats(&team->regular_season_stats);
  show_team_stats(&team->playoff_stats);

  show_team_players(team);
  show_team_goalies(team);

  show_team_lines(&team->lines);
  show_team_lines(&team->original_lines);

  show_team_scouting_report(&team->scouting_report);

  show_raw_data(team->padding, sizeof(team->padding), "PADDING");

  printf("\n");
}

static void show_team_career_stats(team_stats_career_t *stats)
{
  printf("TEAM: %-3s DIV: %3u", stats->abbreviation, stats->division);

  show_team_stats(&stats->regular_season_stats);
  show_team_stats(&stats->playoff_stats);

  printf("\n");
}

bool_t read_team_data(team_db_data_t *db_data)
{
  size_t i;

  if (read_db_file(&db_data->teams, FILE_TEAMS) == INVALID_DB_DATA_OFFSET)
    return FALSE;
  if (read_db_file(&db_data->carteams, FILE_CARTEAMS) == INVALID_DB_DATA_OFFSET)
    return FALSE;

  for (i = 0; i < db_data->teams.length; i += sizeof(team_data_t))
    {
      team_data_t *team;

      team = (team_data_t *) &db_data->teams.data[i];
      show_team_data(team);
    }

  for (i = 0; i < db_data->carteams.length; i += sizeof(team_stats_career_t))
    {
      team_stats_career_t *stats;

      stats = (team_stats_career_t *) &db_data->carteams.data[i];
      show_team_career_stats(stats);
    }

  return TRUE;
}
