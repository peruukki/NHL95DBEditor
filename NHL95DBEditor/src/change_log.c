#include <stdio.h>
#include "change_log.h"
#include "file_utils.h"

void add_log_entry(const char *cmd, const char *att_name, int att_change)
{
  FILE *fp;

  if ((fp = fopen(CHANGE_LOG_FILE, "a")) == NULL)
    printf("Failed to open change log file '%s' for appending", CHANGE_LOG_FILE);

  fprintf(fp, "%s: %s %+d\n", cmd, att_name, att_change);
  fclose(fp);
}
