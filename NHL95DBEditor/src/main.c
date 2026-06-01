#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "backup.h"
#include "change_log.h"
#include "output.h"
#include "player_attributes.h"
#include "players.h"
#include "teams.h"
#include "version.h"

extern player_att_name_t player_att_names[];

#define PROGRAM_NAME "NHL95DBEditor"
#define CMD_ARG_INDEX 1

#define EXIT_IF_FAIL(x)                                                                            \
  if (!(x))                                                                                        \
  return 1

typedef enum
{
  CMD_ADD_TEAM,
  CMD_DUMP_DATA,
  CMD_DUMP_CHANGES,
  CMD_EXPORT,
  CMD_GOALIE_ATTRIBUTES,
  CMD_PLAYER_ATTRIBUTES,
  CMD_RESET,
  CMD_SKATER_ATTRIBUTES,
  CMD_VERSION,
  CMD_UNKNOWN /* Must be last */
} command_t;

/* Keep in sync with command_t values */
static const char *commands[] = { "addteam",   "data",  "changes",   "export", "goalieatt",
                                  "playeratt", "reset", "skateratt", "version" };

/* Keep in sync with format_t values */
static const char *formats[] = { "csv", "json", "plain" };

typedef enum
{
  DATA_TYPE_GOALIE_ATTRIBUTES,
  DATA_TYPE_SKATER_ATTRIBUTES,
  DATA_TYPE_UNKNOWN /* Must be last */
} data_type_t;

/* Keep in sync with data_type_t values */
static const char *data_types[] = { "goalieatt", "skateratt" };

static int usage(const char *filename)
{
  INFO("\n%s is a tool for editing/displaying NHL Hockey 95 databases.\n", PROGRAM_NAME);
  INFO("The database files must be in the current directory.\n\n");
  INFO("Available commands:\n");
  INFO("%-10s - Dumps all database information on the screen.\n", commands[CMD_DUMP_DATA]);
  INFO("%-10s   Dump to a file: %s %s > FILENAME.\n", "", filename, commands[CMD_DUMP_DATA]);
  INFO("%-10s - Exports given database information on the screen in given format.\n",
       commands[CMD_EXPORT]);
  INFO("%-10s   Export to a file: %s %s csv|json skateratt|goalieatt > FILENAME.\n", "", filename,
       commands[CMD_EXPORT]);
  INFO("%-10s - Changes skater attributes. Changes are logged to %s.\n",
       commands[CMD_SKATER_ATTRIBUTES], CHANGE_LOG_FILE);
  INFO("%-10s - Changes goalie attributes. Changes are logged to %s.\n",
       commands[CMD_GOALIE_ATTRIBUTES], CHANGE_LOG_FILE);
  INFO("%-10s - Dumps attribute changes (%s) on the screen.\n", commands[CMD_DUMP_CHANGES],
       CHANGE_LOG_FILE);
  INFO("%-10s - Resets database files to the original ones.\n", commands[CMD_RESET]);
  INFO("%-10s - Shows the application version.\n", commands[CMD_VERSION]);
  INFO("\nExperimental commands:\n");
  INFO("%-10s - Adds a team by duplicating the data of the first team.\n", commands[CMD_ADD_TEAM]);
  INFO("%-10s   NOTE: The added team will not work in the game without some\n", "");
  INFO("%-10s         serious hacking.\n", "");
  return 0;
}

static int cmd_attributes_usage(const char *filename, const char *command, bool_t for_goalie)
{
  int i;

  INFO("\n");
  INFO("Invalid command parameters, usage:\n");
  INFO("%s %s <ATT 1> <CHANGE 1> <ATT 2> <CHANGE 2> ...\n", filename, command);
  INFO("\n");
  INFO("Example: %s %s SPD +25 WGT -50\n", filename, command);
  INFO("\n");
  INFO("Change values must be multipliers of %d, e.g. +%d, +%d, or -%d.\n", ATT_SCALE, ATT_SCALE,
       2 * ATT_SCALE, 5 * ATT_SCALE);
  INFO("\n");
  INFO("The minimum resulting attribute value is %d and the maximum %d.\n", ATT_MIN, ATT_MAX);
  INFO("For example, if a player would get an attribute value of %d after\n"
       "applying the change, the value is set to %d.\n",
       ATT_MIN - ATT_SCALE, ATT_MIN);
  INFO("\n");
  INFO("Available attributes:\n");
  for (i = 0; i < PLAYER_ATT_NUM_VALUES; i++)
    if ((for_goalie && player_att_names[i].for_goalie) ||
        (!for_goalie && player_att_names[i].for_player))
      INFO("  %s - %s\n", player_att_names[i].name, player_att_names[i].description);

  return 1;
}

static int cmd_export_usage(const char *filename, const char *command)
{
  INFO("\n");
  INFO("Invalid command parameters, usage:\n");
  INFO("%s %s csv|json skateratt|goalieatt\n", filename, command);
  INFO("\n");
  INFO("Example: %s %s json goalieatt\n", filename, command);

  return 1;
}

static int get_enum_value(int argc, char *argv[], int arg_index, const char *values[],
                          int unknown_value)
{
  char *arg_str;
  int i;

  if (argc <= arg_index)
    return unknown_value;

  arg_str = argv[arg_index];
  for (i = 0; i < unknown_value; i++)
    {
      if (strcmp(arg_str, values[i]) == 0)
        return i;
    }

  return unknown_value;
}

/* The returned array must be freed by the caller. */
static player_att_change_t *get_att_changes(int argc, char *argv[], int *change_count,
                                            bool_t for_goalie)
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
      att_changes[i].att_enum = get_player_att_enum(att_changes[i].att_name, for_goalie);
      att_changes[i].att_change = atoi(argv[j++]);

      if (!validate_att_change(&att_changes[i]))
        goto error;
    }
  return att_changes;

error:
  free(att_changes);
  return NULL;
}

static void write_changes_to_log(const char *cmd, player_att_change_t *changes, int change_count)
{
  int i;

  for (i = 0; i < change_count; i++)
    add_change_log_entry(cmd, changes[i].att_name, changes[i].att_change);
}

static bool_t read_data(team_db_data_t *team_data, player_db_data_t *player_data)
{
  if (!read_team_data(team_data))
    return FALSE;
  return read_player_data(player_data);
}

int main(int argc, char *argv[])
{
  team_db_data_t team_data;
  player_db_data_t player_data;
  command_t command = (command_t) get_enum_value(argc, argv, CMD_ARG_INDEX, commands, CMD_UNKNOWN);

  if (command == CMD_UNKNOWN)
    return usage(argv[0]);

  db_data_init(&team_data, sizeof(team_data));
  db_data_init(&player_data, sizeof(player_data));

  switch (command)
    {
    case CMD_ADD_TEAM:
      EXIT_IF_FAIL(backup_database_files());
      EXIT_IF_FAIL(read_data(&team_data, &player_data));
      EXIT_IF_FAIL(add_team(&team_data, &player_data));
      break;

    case CMD_DUMP_DATA:
      EXIT_IF_FAIL(read_data(&team_data, &player_data));
      EXIT_IF_FAIL(dump_team_data(&team_data));
      EXIT_IF_FAIL(dump_player_data(&player_data));
      break;

    case CMD_DUMP_CHANGES:
      dump_change_log_entries();
      break;

    case CMD_EXPORT:
      {
        format_t format = get_enum_value(argc, argv, CMD_ARG_INDEX + 1, formats, FORMAT_UNKNOWN);
        data_type_t data_type =
            get_enum_value(argc, argv, CMD_ARG_INDEX + 2, data_types, DATA_TYPE_UNKNOWN);

        if (format == FORMAT_PLAIN || format == FORMAT_UNKNOWN || data_type == DATA_TYPE_UNKNOWN)
          return cmd_export_usage(argv[0], argv[CMD_ARG_INDEX]);

        EXIT_IF_FAIL(read_data(&team_data, &player_data));
        EXIT_IF_FAIL(export_player_data(&player_data, data_type == DATA_TYPE_GOALIE_ATTRIBUTES,
                                        &team_data, format));
        break;
      }

    case CMD_GOALIE_ATTRIBUTES:
    case CMD_PLAYER_ATTRIBUTES:
    case CMD_SKATER_ATTRIBUTES:
      {
        player_att_change_t *changes;
        int change_count = 0;
        bool_t success = FALSE;
        bool_t for_goalie = (command == CMD_GOALIE_ATTRIBUTES);

        EXIT_IF_FAIL(backup_database_files());
        EXIT_IF_FAIL(read_data(&team_data, &player_data));

        if ((changes = get_att_changes(argc, argv, &change_count, for_goalie)) == NULL)
          return cmd_attributes_usage(argv[0], argv[CMD_ARG_INDEX], for_goalie);

        if (for_goalie)
          success = modify_goalie_data(&player_data, changes, change_count);
        else
          success = modify_player_data(&player_data, changes, change_count);
        EXIT_IF_FAIL(success);

        EXIT_IF_FAIL(write_player_data(&player_data));

        write_changes_to_log(for_goalie ? "goalies" : "skaters", changes, change_count);
        free(changes);

        INFO("Attributes changed successfully. All changes:\n");
        dump_change_log_entries();
      }
      break;

    case CMD_RESET:
      if (!restore_database_backup_files())
        {
          INFO("Failed to restore backup files\n");
          EXIT_IF_FAIL(FALSE);
        }
      break;

    case CMD_VERSION:
      INFO(VERSION "\n");
      break;

    default:
      break;
    }

  return 0;
}
