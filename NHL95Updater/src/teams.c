#include <stdio.h>
#include "common_defs.h"
#include "file_utils.h"
#include "teams.h"

#define FILE_TEAMS "TEAMS.DB"

unsigned char teamfile[MAX_DATA_LENGTH];

static void show_team_stats(team_stats *stats)
{
  printf(" GP: %2u W: %2u L: %2u T: %2u GF: %3u GA: %3u PIM: %3u "
         "PPGF: %3u PPGA: %3u ADV: %3u TSH: %3u",
         stats->games_played, stats->wins, stats->losses, stats->ties,
         stats->goals_for, stats->goals_against, stats->penalty_minutes,
         stats->pp_goals_for, stats->pp_goals_against,
         stats->pp_advantages, stats->times_shorthanded);
}

static void show_offsets(offset offsets[], int count, char *title)
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

static void show_team_players(team_data *team)
{
  int count;

  count = sizeof(team->players) / sizeof(team->players[0]);
  show_offsets(team->players, count, "P");
}

static void show_team_goalies(team_data *team)
{
  int count;

  count = sizeof(team->goalies) / sizeof(team->goalies[0]);
  show_offsets(team->goalies, count, "G");
}

static void show_team_lines(team_lines *lines)
{
  int i;
  int count;

  /* Forward lines */
  count = sizeof(lines->fwd_lines) / sizeof(lines->fwd_lines[0]);
  for (i = 0; i < count; i++)
    {
      team_forward_line *line = &lines->fwd_lines[i];

      printf(" F%u: %2u %2u %2u", i + 1,
             line->left_wing, line->center, line->right_wing);
    }

  /* Defense lines */
  count = sizeof(lines->def_lines) / sizeof(lines->def_lines[0]);
  for (i = 0; i < count; i++)
    {
      team_defense_line *line = &lines->def_lines[i];

      printf(" D%u: %2u %2u", i + 1,
             line->left_defense, line->right_defense);
    }

  /* Goalies */
  printf(" G1: %u G2: %u",
         lines->goalies.starting_goalie, lines->goalies.backup_goalie);

  /* Don't show everything, there's too much... */
  printf(" ...");
}

static void show_team_scouting_report(team_scouting_report *report)
{
  printf(" PK: %2u PP: %2u SH: %2u SK: %2u PS: %2u DE: %2u "
         "CH: %2u GT: %2u OA: %2u",
         report->penalty_killing, report->power_play, report->shooting,
         report->skating, report->passing, report->defense,
         report->checking, report->goaltending, report->overall);
}

static void show_unknown_data(number_1 *data, size_t length, char *title)
{
  size_t i;

  printf(" %s:", title);
  for (i = 0; i < length; i++)
    {
      printf(" %3u", data[i]);
    }
}

void show_team_data(team_data *team)
{
  printf("TEAM: %-3s DIV: %3u", team->abbr, team->division);

  show_team_stats(&team->regular_season_stats);
  show_team_stats(&team->playoff_stats);

  show_team_players(team);
  show_team_goalies(team);

  show_team_lines(&team->lines);
  show_team_lines(&team->original_lines);

  show_unknown_data(team->unknown_1, sizeof(team->unknown_1), "DATA1");

  show_team_scouting_report(&team->scouting_report);

  printf("\n");
}

void read_team_data(void)
{
  size_t teamsize;
  size_t i;

  teamsize = read_file(teamfile, sizeof(teamfile), FILE_TEAMS);

  for (i = 0; i < teamsize; i += sizeof(team_data))
    {
      team_data *team;

      team = (team_data *) &teamfile[i];
      show_team_data(team);
    }
}
