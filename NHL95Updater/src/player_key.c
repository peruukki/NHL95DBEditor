#include <stdio.h>
#include "player_key.h"

void show_key_player(key_player *key)
{
  size_t i;

  printf("T: %2u NO: %2u POS: %c NAME: %-15s %-15s",
         key->team, key->jersey, key->position, key->first, key->last);

  printf(" OFS_ATT: %4x OFS_CAR: %4x OFS_SEA: %4x",
         key->ofs_attributes, key->ofs_career_stats, key->ofs_season_stats);

  printf(" UNKNOWN: ");
  for (i = 0; i < sizeof(key->unknown); i++)
    {
      printf("%3u ", key->unknown[i]);
    }
}
