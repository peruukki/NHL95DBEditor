#include <stdio.h>
#include <string.h>
#include "teams.h"
#include "players.h"

#define PROGRAM_NAME "NHL95DBEditor"

#define EXIT_IF_FAIL(x) if (!(x)) return 1

typedef enum
{
  CMD_ADD_TEAM,
  CMD_DUMP_DATA,
  CMD_PLAYER_ATTRIBUTES,
  CMD_UNKNOWN /* Must be last */
} command_t;

static const char *commands[] = { "addteam", "dump", "playeratt" };

static int usage(void)
{
  printf("%s is a tool for editing/displaying NHL Hockey 95 databases.\n", PROGRAM_NAME);
  printf("The database files must be in the current directory.\n\n");
  printf("Available commands:\n");
  printf("%-15s - Adds a team by duplicating the data of the first team.\n", commands[CMD_ADD_TEAM]);
  printf("%-15s - Dumps all database information to stdout.\n", commands[CMD_DUMP_DATA]);
  printf("%-15s - Modifies player attributes.\n", commands[CMD_PLAYER_ATTRIBUTES]);
  return 0;
}

static command_t get_command(int argc, char *argv[])
{
  char *cmd_str;
  int i;

  if (argc < 2)
    return CMD_UNKNOWN;

  cmd_str = argv[1];
  for (i = 0; i < CMD_UNKNOWN; i++)
    {
      if (strcmp(cmd_str, commands[i]) == 0)
        return (command_t) i;
    }

  return CMD_UNKNOWN;
}

int main(int argc, char *argv[])
{
  team_db_data_t team_data;
  player_db_data_t player_data;
  command_t command;

  if ((command = get_command(argc, argv)) == CMD_UNKNOWN)
    return usage();

  db_data_init(&team_data, sizeof(team_data));
  db_data_init(&player_data, sizeof(player_data));

  EXIT_IF_FAIL(read_team_data(&team_data));
  EXIT_IF_FAIL(read_player_data(&player_data));

  switch (command)
    {
    case CMD_ADD_TEAM:
      EXIT_IF_FAIL(add_team(&team_data, &player_data));
      break;

    case CMD_DUMP_DATA:
      EXIT_IF_FAIL(dump_team_data(&team_data));
      EXIT_IF_FAIL(dump_player_data(&player_data));
      break;

    case CMD_PLAYER_ATTRIBUTES:
      EXIT_IF_FAIL(modify_player_data(&player_data));
      EXIT_IF_FAIL(write_player_data(&player_data));
      break;

    default:
      break;
    }

  return 0;
}
