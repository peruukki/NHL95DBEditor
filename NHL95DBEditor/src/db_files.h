#pragma once

typedef enum
{
  DB_FILE_ATTRIBUTES,
  DB_FILE_CAREER,
  DB_FILE_CARTEAMS,
  DB_FILE_KEYS,
  DB_FILE_SEASON,
  DB_FILE_TEAMS,
  DB_FILE_NUM_FILES
} db_file_t;

const char **get_db_files(void);

const char *get_db_file(db_file_t file);
