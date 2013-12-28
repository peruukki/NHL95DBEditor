#include <string.h>
#include "change_log.h"
#include "file_utils.h"
#include "output.h"

void add_change_log_entry(const char *cmd, const char *att_name, int att_change)
{
  FILE *fp;

  if ((fp = fopen(CHANGE_LOG_FILE, "a")) == NULL)
    {
      INFO("Failed to open change log file '%s' for appending", CHANGE_LOG_FILE);
      return;
    }

  fprintf(fp, "%s: %s %+d\n", cmd, att_name, att_change);
  fclose(fp);
}

void dump_change_log_entries(void)
{
  unsigned char content[1024];
  size_t content_bytes = sizeof(content) - 1;
  size_t byte_count = 0;
  FILE *fp;

  if ((fp = fopen(CHANGE_LOG_FILE, "r")) == NULL)
    {
      INFO("No attribute changes.\n");
      return;
    }

  do
    {
      memset(content, 0, sizeof(content));
      byte_count = fread(content, sizeof(*content), content_bytes, fp);
      INFO("%s", content);
    }
  while (byte_count == content_bytes);
  fclose(fp);
}
