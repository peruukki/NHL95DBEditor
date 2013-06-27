#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "teams.h"
#include "players.h"
#include "player_attributes.h"

extern player_att_name_t player_att_names[];

#define PROGRAM_NAME "NHL95DBEditor"
#define CMD_ARG_INDEX 1

#define EXIT_IF_FAIL(x) if (!(x)) return 1

typedef enum
{
  CMD_ADD_TEAM,
  CMD_DUMP_DATA,
  CMD_GOALIE_ATTRIBUTES,
  CMD_PLAYER_ATTRIBUTES,
  CMD_UNKNOWN /* Must be last */
} command_t;

static const char *commands[] = { "addteam", "dump", "goalieatt", "playeratt" };

static int usage(void)
{
  printf("%s is a tool for editing/displaying NHL Hockey 95 databases.\n", PROGRAM_NAME);
  printf("The database files must be in the current directory.\n\n");
  printf("Available commands:\n");
  printf("%-15s - Adds a team by duplicating the data of the first team.\n", commands[CMD_ADD_TEAM]);
  printf("%-15s - Dumps all database information to stdout.\n", commands[CMD_DUMP_DATA]);
  printf("%-15s - Modifies goalie attributes by given amount.\n", commands[CMD_GOALIE_ATTRIBUTES]);
  printf("%-15s - Modifies player attributes by given amount.\n", commands[CMD_PLAYER_ATTRIBUTES]);
  return 0;
}

static int cmd_attributes_usage(const char *filename, const char *command)
{
  int i;

  printf("\nInvalid command parameters, usage:\n");
  printf("%s %s <ATT 1> <CHANGE 1> <ATT 2> <CHANGE 2> ...\n", filename, command);
  printf("Example: %s %s SPD +25 WGT -50\n", filename, command);

  printf("\nAvailable attributes:\n");
  for (i = 0; i < PLAYER_ATT_NUM_VALUES; i++)
    printf("  %s - %s\n", player_att_names[i].name, player_att_names[i].description);

  return 1;
}

static command_t get_command(int argc, char *argv[])
{
  char *cmd_str;
  int i;

  if (argc <= CMD_ARG_INDEX)
    return CMD_UNKNOWN;

  cmd_str = argv[CMD_ARG_INDEX];
  for (i = 0; i < CMD_UNKNOWN; i++)
    {
      if (strcmp(cmd_str, commands[i]) == 0)
        return (command_t) i;
    }

  return CMD_UNKNOWN;
}

/* The returned array must be freed by the caller. */
static player_att_change_t *get_att_changes(int argc, char *argv[], int *change_count)
{
  player_att_change_t *att_changes = NULL;
  int param_count = argc - 1 - CMD_ARG_INDEX;
  int i, j;

  if ((param_count == 0) || (param_count % 2 != 0))
    goto error;

  *change_count = param_count / 2;
  att_changes = calloc(*change_count, sizeof(*att_changes));
  for (i = 0, j = CMD_ARG_INDEX + 1; i < *change_count; i++)
    {
      att_changes[i].att_name = argv[j++];
      att_changes[i].att_enum = get_player_att_enum(att_changes[i].att_name);
      att_changes[i].att_change = atoi(argv[j++]);

      if (!validate_att_change(&att_changes[i]))
        goto error;
    }
  return att_changes;

error:
  free(att_changes);
  return NULL;
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

    case CMD_GOALIE_ATTRIBUTES:
    case CMD_PLAYER_ATTRIBUTES:
      {
        player_att_change_t *changes;
        int change_count = 0;
        bool_t success = FALSE;

        if ((changes = get_att_changes(argc, argv, &change_count)) == NULL)
          return cmd_attributes_usage(argv[0], argv[CMD_ARG_INDEX]);

        if (command == CMD_GOALIE_ATTRIBUTES)
          success = modify_goalie_data(&player_data, changes, change_count);
        else
          success = modify_player_data(&player_data, changes, change_count);
        free(changes);
        EXIT_IF_FAIL(success);

        EXIT_IF_FAIL(write_player_data(&player_data));
      }
      break;

    default:
      break;
    }

  return 0;
}
