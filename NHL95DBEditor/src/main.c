#include "teams.h"
#include "players.h"

int main(int argc, char *argv[])
{
  team_db_data_t team_data;
  player_db_data_t player_data;

  db_data_init(&team_data, sizeof(team_data));
  db_data_init(&player_data, sizeof(player_data));

  if (!read_team_data(&team_data))
    goto error;
  if (!read_player_data(&player_data))
    goto error;

  if (!modify_player_data(&player_data))
    goto error;
  if (!write_player_data(&player_data))
    goto error;

  /* Show the updated data */
  if (!read_team_data(&team_data))
    goto error;
  if (!read_player_data(&player_data))
    goto error;

  return 0;

error:
  return 1;
}
