#include <stdio.h>
#include "common_defs.h"
#include "file_utils.h"
#include "player_attributes.h"
#include "player_key.h"
#include "player_stats.h"

#define FILE_ATTRIBUTES "ATT.DB"
#define FILE_CAREER "CAREER.DB"
#define FILE_KEYS "KEY.DB"
#define FILE_SEASON "SEASON.DB"

unsigned char att_data[MAX_DATA_LENGTH];
unsigned char career_data[MAX_DATA_LENGTH];
unsigned char key_data[MAX_DATA_LENGTH];
unsigned char season_data[MAX_DATA_LENGTH];

bool_t read_player_data(void)
{
  db_data_t key_data;
  db_data_t att_data;
  db_data_t career_data;
  db_data_t season_data;
  size_t i;

  db_data_init(&key_data);
  db_data_init(&att_data);
  db_data_init(&career_data);
  db_data_init(&season_data);

  if (read_db_file(&key_data, FILE_KEYS) == INVALID_DB_DATA_OFFSET)
    return FALSE;
  if (read_db_file(&att_data, FILE_ATTRIBUTES) == INVALID_DB_DATA_OFFSET)
    return FALSE;
  if (read_db_file(&career_data, FILE_CAREER) == INVALID_DB_DATA_OFFSET)
    return FALSE;
  if (read_db_file(&season_data, FILE_SEASON) == INVALID_DB_DATA_OFFSET)
    return FALSE;

  for (i = 0; i < key_data.length; i += sizeof(player_key_t))
    {
      player_key_t *key;

      key = (player_key_t *) &key_data.data[i];
      show_key_player(key);
      show_attributes(att_data.data, key);
      show_stats_career(career_data.data, key);
      show_stats_season(season_data.data, key);
      printf("\n");
    }

  write_db_file(&att_data, FILE_ATTRIBUTES);
  return TRUE;
}
