#include "backup.h"
#include "change_log.h"
#include "common_defs.h"
#include "db_files.h"
#include "file_utils.h"
#include "output.h"

static const char *backup_suffix = ".BAK";

bool_t backup_database_files(void)
{
  const char **db_files = get_db_files();
  char backup_file[255];
  int i;

  for (i = 0; i < DB_FILE_NUM_FILES; i++)
    {
      sprintf(backup_file, "%s%s", db_files[i], backup_suffix);
      if (!file_exists(backup_file))
        {
          INFO("Backing up file %s... ", db_files[i]);
          if (!copy_file(db_files[i], backup_file))
            return FALSE;
        }
    }

  return TRUE;
}

bool_t restore_database_backup_files(void)
{
  const char **db_files = get_db_files();
  char backup_file[255];
  int i;

  for (i = 0; i < DB_FILE_NUM_FILES; i++)
    {
      sprintf(backup_file, "%s%s", db_files[i], backup_suffix);
      if (file_exists(backup_file))
        {
          INFO("Restoring backup file %s... ", backup_file);
          if (!copy_file(backup_file, db_files[i]))
            return FALSE;
          (void) delete_file(backup_file);
        }
    }

  if (file_exists(CHANGE_LOG_FILE) && !delete_file(CHANGE_LOG_FILE))
    return FALSE;

  return TRUE;
}
