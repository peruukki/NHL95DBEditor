#include "output.h"
#include "player_key.h"

bool_t key_is_goalie(player_key_t *key)
{
  return key->position == 'G';
}

void show_key_player(player_key_t *key, size_t ofs_key)
{
  size_t i;

  INFO("T: %3u NO: %2u POS: %c NAME: %-15s %-15s",
       key->team, key->jersey, key->position, key->first, key->last);

  INFO(" OFS_KEY: %4x OFS_ATT: %4x OFS_CAR: %4x OFS_SEA: %4x",
       ofs_key, key->ofs_attributes, key->ofs_career_stats, key->ofs_season_stats);

  INFO(" UNKNOWN: ");
  for (i = 0; i < sizeof(key->unknown); i++)
    {
      INFO("%3u ", key->unknown[i]);
    }
}
