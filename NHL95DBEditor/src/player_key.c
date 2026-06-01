#include "output.h"
#include "player_key.h"

bool_t key_is_goalie(player_key_t *key)
{
  return key->position == 'G';
}

void show_player_key(player_key_t *key, size_t ofs_key, team_data_t *team, format_t format)
{
  size_t i;

  if (format == FORMAT_CSV)
    INFO("%s,%u,%c,%s,%s", team->abbreviation, key->jersey, key->position, key->first, key->last);
  else if (format == FORMAT_JSON)
    {
      INFO("\"team\": \"%s\"", team->abbreviation);
      INFO(", \"number\": %u", key->jersey);
      INFO(", \"position\": \"%c\"", key->position);
      INFO(", \"firstName\": \"%s\"", key->first);
      INFO(", \"lastName\": \"%s\"", key->last);
    }
  else if (format == FORMAT_PLAIN)
    {
      INFO("T: %3u NO: %2u POS: %c NAME: %-15s %-15s", key->team, key->jersey, key->position,
           key->first, key->last);
      INFO(" OFS_KEY: %4zx OFS_ATT: %4x OFS_CAR: %4x OFS_SEA: %4x", ofs_key, key->ofs_attributes,
           key->ofs_career_stats, key->ofs_season_stats);
      INFO(" UNKNOWN: ");
      for (i = 0; i < sizeof(key->unknown); i++)
        INFO("%3u ", key->unknown[i]);
    }
}

void print_player_key_header(format_t format)
{
  if (format == FORMAT_JSON)
    INFO("      \"info\": { ");
  else if (format == FORMAT_CSV)
    INFO("team,number,position,first name,last name");
}

void print_player_key_footer(format_t format)
{
  if (format == FORMAT_JSON)
    INFO(" },\n");
  else if (format == FORMAT_CSV)
    print_delimiter(format);
}
