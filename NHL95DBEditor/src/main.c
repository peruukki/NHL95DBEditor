#include "teams.h"
#include "players.h"

int main(int argc, char *argv[])
{
  team_db_data_t team_data;

  read_team_data(&team_data);
  read_player_data();
  return 0;
}
