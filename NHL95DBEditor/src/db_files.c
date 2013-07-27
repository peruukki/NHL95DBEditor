#include "db_files.h"

/* The order must be the same as in the db_file_t enumeration. */
static const char *db_files[] =
{
  "ATT.DB", "CAREER.DB", "CARTEAMS.DB", "KEY.DB", "SEASON.DB", "TEAMS.DB"
};

const char **get_db_files(void)
{
  return db_files;
}

const char *get_db_file(db_file_t file)
{
  return db_files[file];
}
