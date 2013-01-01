#include <stdio.h>
#include "player_stats.h"

static void show_unknown_data(number_1 *data, size_t length)
{
  size_t i;

  printf(" UNKNOWN:");
  for (i = 0; i < length; i++)
    {
      printf(" %3u", data[i]);
    }
}

static void show_stats_goalie(stats_goalie *stats)
{
  printf(" GP: %2u W: %2u L: %2u T: %2u SH: %2u EN: %2u MIN: %4u"
         " GA: %3u GAA: %u.%02u SA: %4u SV%%: .%03u",
         stats->games_played, stats->wins, stats->losses, stats->ties,
         stats->shutouts, stats->empty_nets, stats->minutes,
         stats->goals_against, stats->gaa / 100, stats->gaa % 100,
         stats->saves, stats->save_pct);
}

static void show_stats_player(stats_player *stats)
{
  printf(" GP: %2u G: %2u A: %2u P: %3u PPG: %2u SHG: %2u"
         " PIM: %3u SH: %3u +/-: %+3d",
         stats->games_played, stats->goals, stats->assists, stats->points,
         stats->pp_goals, stats->sh_goals, stats->penalty_minutes,
         stats->shots, stats->plus_minus);
}

static void show_stats_career_goalie(stats_career_goalie *stats)
{
  show_stats_goalie(&stats->regular_season);
  show_stats_goalie(&stats->playoffs);
  show_unknown_data(stats->unknown, sizeof(stats->unknown));
}

static void show_stats_career_player(stats_career_player *stats)
{
  show_stats_player(&stats->regular_season);
  show_stats_player(&stats->playoffs);
  show_unknown_data(stats->unknown, sizeof(stats->unknown));
}

void show_stats_career(unsigned char *stats_data, key_player *key)
{
  unsigned char *stats = &stats_data[key->ofs_career_stats];

  if (key_is_goalie(key))
    {
      show_stats_career_goalie((stats_career_goalie *) stats);
    }
  else
    {
      show_stats_career_player((stats_career_player *) stats);
    }
}
