#include <stdio.h>
#include "common_defs.h"
#include "file_utils.h"
#include "player_attributes.h"
#include "player_key.h"
#include "player_stats.h"
#include "players.h"

#define FILE_ATTRIBUTES "ATT.DB"
#define FILE_CAREER "CAREER.DB"
#define FILE_KEYS "KEY.DB"
#define FILE_SEASON "SEASON.DB"

bool_t read_player_data(player_db_data_t *db_data)
{
  size_t i;

  if (!read_db_file(&db_data->key_data, FILE_KEYS))
    return FALSE;
  if (!read_db_file(&db_data->att_data, FILE_ATTRIBUTES))
    return FALSE;
  if (!read_db_file(&db_data->career_data, FILE_CAREER))
    return FALSE;
  if (!read_db_file(&db_data->season_data, FILE_SEASON))
    return FALSE;

  for (i = 0; i < db_data->key_data.length; i += sizeof(player_key_t))
    {
      player_key_t *key;

      key = (player_key_t *) &db_data->key_data.data[i];
      show_key_player(key);
      show_attributes(db_data->att_data.data, key);
      show_stats_career(db_data->career_data.data, key);
      show_stats_season(db_data->season_data.data, key);
      printf("\n");
    }

  return TRUE;
}
