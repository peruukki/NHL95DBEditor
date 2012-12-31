#pragma once

#include "common_defs.h"
#include "file_utils.h"
#include "player_attributes.h"
#include "player_key.h"

#define FILE_ATTRIBUTES "ATT.DB"
#define FILE_KEYS "KEY.DB"

unsigned char attfile[MAX_DATA_LENGTH];
unsigned char keyfile[MAX_DATA_LENGTH];

void read_player_data(void)
{
  size_t keysize;
  size_t attsize;
  size_t i;

  keysize = read_file(keyfile, sizeof(keyfile), FILE_KEYS);
  attsize = read_file(attfile, sizeof(attfile), FILE_ATTRIBUTES);

  for (i = 0; i < keysize; i += sizeof(key_player))
    {
      key_player *key;

      key = (key_player *) &keyfile[i];
      show_key_player(key);
      show_attributes(attfile, key);
    }

  write_file(attfile, attsize, FILE_ATTRIBUTES);
}
