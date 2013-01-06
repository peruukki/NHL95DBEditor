#include "teams.h"
#include "players.h"

int main(int argc, char *argv[])
{
  team_db_data_t team_data;

  db_data_init(&team_data.teams);
  db_data_init(&team_data.carteams);

  if (!read_team_data(&team_data))
    goto error;
  if (!read_player_data())
    goto error;

  return 0;

error:
  return 1;
}
