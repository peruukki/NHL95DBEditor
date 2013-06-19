#include <stdio.h>
#include <string.h>
#include "common_defs.h"
#include "file_utils.h"
#include "teams.h"
#include "players.h"

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
      if (offsets[i] == INVALID_DB_DATA_OFFSET)
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
  show_offsets(team->players, ELEM_COUNT(team->players), "P");
}

static void show_team_goalies(team_data_t *team)
{
  show_offsets(team->goalies, ELEM_COUNT(team->goalies), "G");
}

static void show_team_lines(team_lines_t *lines)
{
  int i;
  int count;

  /* Forward lines */
  count = ELEM_COUNT(lines->fwd_lines);
  for (i = 0; i < count; i++)
    {
      team_forward_line_t *line = &lines->fwd_lines[i];

      printf(" F%u: %2u %2u %2u", i + 1,
             line->left_wing, line->center, line->right_wing);
    }

  /* Defense lines */
  count = ELEM_COUNT(lines->def_lines);
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
  if (!read_db_file(&db_data->teams, FILE_TEAMS))
    return FALSE;
  if (!read_db_file(&db_data->carteams, FILE_CARTEAMS))
    return FALSE;
  return TRUE;
}

bool_t dump_team_data(team_db_data_t *db_data)
{
  size_t i;

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

static number_1_t get_new_team_index(db_data_t *team_db_data)
{
  size_t i;
  number_1_t team_index = 0;

  for (i = 0; i < team_db_data->length; i += sizeof(team_data_t))
    {
      team_data_t *team = (team_data_t *) &team_db_data->data[i];

      /* Return the index of the first the all-star team */
      if (team->division == 0xFF)
        break;

      team_index++;
    }

  return team_index;
}

bool_t add_team(team_db_data_t *team_data,
                player_db_data_t *player_data)
{
  team_data_t *new_team;
  team_stats_career_t *new_team_career;
  size_t new_team_ofs;
  size_t new_team_career_ofs;
  number_1_t new_team_index;

  /* Append new data */
  new_team_index = get_new_team_index(&team_data->teams);
  new_team_ofs = db_data_append_space(&team_data->teams,
                                      new_team_index * sizeof(*new_team),
                                      sizeof(*new_team));
  new_team_career_ofs = db_data_append_space(&team_data->carteams,
                                             new_team_index * sizeof(*new_team_career),
                                             sizeof(*new_team_career));

  if ((new_team_ofs == INVALID_DB_DATA_OFFSET) ||
      (new_team_career_ofs == INVALID_DB_DATA_OFFSET))
    return FALSE;

  new_team = (team_data_t *) &team_data->teams.data[new_team_ofs];
  new_team_career = (team_stats_career_t *)
    &team_data->carteams.data[new_team_career_ofs];

  /* Duplicate existing team */
  memcpy(new_team, &team_data->teams, sizeof(*new_team));
  memcpy(new_team_career, &team_data->carteams, sizeof(*new_team_career));

  /* Overwrite team data */
  sprintf(new_team->short_name, "New Team");
  sprintf(new_team->long_name, "New Team Katit");
  new_team->division = 1;
  if (!add_duplicate_player_data((team_data_t *) &team_data->teams.data,
                                 new_team, new_team_index, player_data))
    return FALSE;
  write_db_file(&team_data->teams, FILE_TEAMS);

  /* Overwrite team career data */
  sprintf(new_team_career->short_name, "New Team");
  sprintf(new_team_career->long_name, "New Team Katit");
  new_team_career->division = 1;
  write_db_file(&team_data->carteams, FILE_CARTEAMS);

  return TRUE;
}
