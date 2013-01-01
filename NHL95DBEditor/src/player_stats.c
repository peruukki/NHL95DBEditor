#include <stdio.h>
#include "player_stats.h"

static void show_unknown_data(number_1_t *data, size_t length)
{
  size_t i;

  printf(" UNKNOWN:");
  for (i = 0; i < length; i++)
    {
      printf(" %3u", data[i]);
    }
}

static void show_stats_goalie(goalie_stats_t *stats)
{
  printf(" GP: %2u W: %2u L: %2u T: %2u SH: %2u EN: %2u MIN: %4u"
         " GA: %3u GAA: %u.%02u SA: %4u SV%%: .%03u",
         stats->games_played, stats->wins, stats->losses, stats->ties,
         stats->shutouts, stats->empty_nets, stats->minutes,
         stats->goals_against, stats->gaa / 100, stats->gaa % 100,
         stats->saves, stats->save_pct);
}

static void show_stats_player(player_stats_t *stats)
{
  printf(" GP: %2u G: %2u A: %2u P: %3u PPG: %2u SHG: %2u"
         " PIM: %3u SH: %3u +/-: %+3d",
         stats->games_played, stats->goals, stats->assists, stats->points,
         stats->pp_goals, stats->sh_goals, stats->penalty_minutes,
         stats->shots, stats->plus_minus);
}

static void show_stats_data_goalie(goalie_stats_t *regular_season,
                                   goalie_stats_t *playoffs,
                                   number_1_t *unknown,
                                   size_t unknown_length)
{
  show_stats_goalie(regular_season);
  show_stats_goalie(playoffs);
  show_unknown_data(unknown, unknown_length);
}

static void show_stats_data_player(player_stats_t *regular_season,
                                   player_stats_t *playoffs,
                                   number_1_t *unknown,
                                   size_t unknown_length)
{
  show_stats_player(regular_season);
  show_stats_player(playoffs);
  show_unknown_data(unknown, unknown_length);
}

void show_stats_career(unsigned char *stats_data, player_key_t *key)
{
  if (key_is_goalie(key))
    {
      goalie_stats_career_t *stats =
        (goalie_stats_career_t *) &stats_data[key->ofs_career_stats];
      show_stats_data_goalie(&stats->regular_season, &stats->playoffs,
                             stats->unknown, sizeof(stats->unknown));
    }
  else
    {
      player_stats_career_t *stats =
        (player_stats_career_t *) &stats_data[key->ofs_career_stats];
      show_stats_data_player(&stats->regular_season, &stats->playoffs,
                             stats->unknown, sizeof(stats->unknown));
    }
}

void show_stats_season(unsigned char *stats_data, player_key_t *key)
{
  if (key_is_goalie(key))
    {
      goalie_stats_season_t *stats =
        (goalie_stats_season_t *) &stats_data[key->ofs_season_stats];
      show_stats_data_goalie(&stats->regular_season, &stats->playoffs,
                             stats->unknown, sizeof(stats->unknown));
    }
  else
    {
      player_stats_season_t *stats =
        (player_stats_season_t *) &stats_data[key->ofs_season_stats];
      show_stats_data_player(&stats->regular_season, &stats->playoffs,
                             stats->unknown, sizeof(stats->unknown));
    }
}
