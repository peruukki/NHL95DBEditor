#include <stdio.h>
#include <string.h>
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
  if (!read_db_file(&db_data->key_data, FILE_KEYS))
    return FALSE;
  if (!read_db_file(&db_data->att_data, FILE_ATTRIBUTES))
    return FALSE;
  if (!read_db_file(&db_data->career_data, FILE_CAREER))
    return FALSE;
  if (!read_db_file(&db_data->season_data, FILE_SEASON))
    return FALSE;
  return TRUE;
}

bool_t dump_player_data(player_db_data_t *db_data)
{
  size_t i;

  for (i = 0; i < db_data->key_data.length; i += sizeof(player_key_t))
    {
      player_key_t *key;

      key = (player_key_t *) &db_data->key_data.data[i];
      show_key_player(key, i);
      show_attributes(db_data->att_data.data, key);
      show_stats_career(db_data->career_data.data, key);
      show_stats_season(db_data->season_data.data, key);
      printf("\n");
    }

  return TRUE;
}

static void update_team_indexes(int new_team_index, db_data_t *key_db_data)
{
  size_t i;

  for (i = 0; i < key_db_data->length; i += sizeof(player_key_t))
    {
      player_key_t *key = (player_key_t *) &key_db_data->data[i];

      if (key->team >= new_team_index)
        key->team++;
      if (key->team == 28)
        key->team--;
    }
}

static offset_t add_player_data(player_db_data_t *db_data,
                                player_key_t *key,
                                void *att_data, size_t att_data_length,
                                void *season_data, size_t season_data_length,
                                void *career_data, size_t career_data_length)
{
  offset_t ofs_key, ofs_att, ofs_season, ofs_career;

  ofs_att = db_data_append_data(&db_data->att_data, att_data, att_data_length);
  ofs_season = db_data_append_data(&db_data->season_data, season_data,
                                   season_data_length);
  ofs_career = db_data_append_data(&db_data->career_data, career_data,
                                   career_data_length);
  if ((ofs_att == INVALID_DB_DATA_OFFSET) ||
      (ofs_season == INVALID_DB_DATA_OFFSET) ||
      (ofs_career == INVALID_DB_DATA_OFFSET))
    return INVALID_DB_DATA_OFFSET;

  key->ofs_attributes = ofs_att;
  key->ofs_season_stats = ofs_season;
  key->ofs_career_stats = ofs_career;

  ofs_key = db_data_append_data(&db_data->key_data, key, sizeof(*key));
  return ofs_key;
}

static bool_t add_duplicate_players(team_data_t *src_team,
                                    team_data_t *dst_team,
                                    number_1_t new_team_index,
                                    player_db_data_t *db_data,
                                    offset_t *players,
                                    int player_count,
                                    size_t att_length,
                                    size_t season_length,
                                    size_t career_length)
{
  int i;

  for (i = 0; i < player_count; i++)
    {
      offset_t src_key_ofs, dst_key_ofs;
      player_key_t *src_key, dst_key;

      src_key_ofs = players[i];
      if (src_key_ofs == INVALID_DB_DATA_OFFSET)
        break;

      src_key = (player_key_t *) &db_data->key_data.data[src_key_ofs];

      /* Update new key */
      memcpy(&dst_key, src_key, sizeof(dst_key));
      dst_key.team = new_team_index;
      memset(dst_key.unknown, 0, sizeof(dst_key.unknown));
      dst_key_ofs = add_player_data(db_data, &dst_key,
                                    &db_data->att_data.data[src_key->ofs_attributes],
                                    sizeof(player_att_t),
                                    &db_data->season_data.data[src_key->ofs_season_stats],
                                    sizeof(player_stats_season_t),
                                    &db_data->career_data.data[src_key->ofs_career_stats],
                                    sizeof(player_stats_career_t));
      if (dst_key_ofs == INVALID_DB_DATA_OFFSET)
        return FALSE;

      /* Update key offset in team data */
      players[i] = dst_key_ofs;
    }

  return TRUE;
}

bool_t add_duplicate_player_data(team_data_t *src_team,
                                 team_data_t *dst_team,
                                 number_1_t new_team_index,
                                 player_db_data_t *db_data)
{
  /* Update players of teams whose team index has increased */
  update_team_indexes(new_team_index, &db_data->key_data);

  /* Players */
  if (!add_duplicate_players(src_team, dst_team, new_team_index, db_data,
                             dst_team->players, ELEM_COUNT(dst_team->players),
                             sizeof(player_att_t), sizeof(player_stats_season_t),
                             sizeof(player_stats_career_t)))
    return FALSE;

  /* Goalies */
  if (!add_duplicate_players(src_team, dst_team, new_team_index, db_data,
                             dst_team->goalies, ELEM_COUNT(dst_team->goalies),
                             sizeof(goalie_att_t), sizeof(goalie_stats_season_t),
                             sizeof(goalie_stats_career_t)))
    return FALSE;

  return write_player_data(db_data);
}

bool_t modify_player_data(player_db_data_t *db_data)
{
  size_t i;

  for (i = 0; i < db_data->key_data.length; i += sizeof(player_key_t))
    {
      player_key_t *key;

      key = (player_key_t *) &db_data->key_data.data[i];
      if (!key_is_goalie(key))
        {
          player_att_t *att = (player_att_t *)
            &db_data->att_data.data[key->ofs_attributes];
          modify_player_attribute(att, ATT_NAME_PASSING, 25);
          modify_player_attribute(att, ATT_NAME_SPEED, 25);
          modify_player_attribute(att, ATT_NAME_SHOT_POWER, 25);
          modify_player_attribute(att, ATT_NAME_ACCURACY, 25);
          modify_player_attribute(att, ATT_NAME_STICK_HANDLING, 25);
          modify_player_attribute(att, ATT_NAME_SHOOT_PASS_BIAS, -50);
        }
    }

  return TRUE;
}

bool_t write_player_data(player_db_data_t *db_data)
{
  write_db_file(&db_data->key_data, FILE_KEYS);
  write_db_file(&db_data->att_data, FILE_ATTRIBUTES);
  write_db_file(&db_data->career_data, FILE_CAREER);
  write_db_file(&db_data->season_data, FILE_SEASON);
  return TRUE;
}
