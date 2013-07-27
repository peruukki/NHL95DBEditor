#include <stdio.h>
#include "backup.h"
#include "common_defs.h"
#include "db_files.h"
#include "file_utils.h"

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
          printf("Backing up file %s... ", db_files[i]);
          if (!copy_file(db_files[i], backup_file))
            return FALSE;
        }
    }

  return TRUE;
}
