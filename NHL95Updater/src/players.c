#pragma once

#include "common_defs.h"
#include "file_utils.h"
#include "player_attributes.h"
#include "player_key.h"

#define FILE_ATTRIBUTES "ATT.DB"
#define FILE_KEYS "KEY.DB"

unsigned char att_data[MAX_DATA_LENGTH];
unsigned char key_data[MAX_DATA_LENGTH];

void read_player_data(void)
{
  size_t key_size;
  size_t att_size;
  size_t i;

  key_size = read_file(key_data, sizeof(key_data), FILE_KEYS);
  att_size = read_file(att_data, sizeof(att_data), FILE_ATTRIBUTES);

  for (i = 0; i < key_size; i += sizeof(key_player))
    {
      key_player *key;

      key = (key_player *) &key_data[i];
      show_key_player(key);
      show_attributes(att_data, key);
    }

  write_file(att_data, att_size, FILE_ATTRIBUTES);
}
