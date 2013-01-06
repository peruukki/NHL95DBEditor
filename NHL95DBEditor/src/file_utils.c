#include <stdio.h>
#include "file_utils.h"

bool_t read_db_file(db_data_t *data, const char *file_name)
{
  FILE *fp;

  if ((fp = fopen(file_name, "rb")) == NULL)
    {
      printf("Failed to open file '%s' for reading", file_name);
      return FALSE;
    }

  data->length = fread(data->data, 1, sizeof(data->data), fp);
  fclose(fp);
  printf("Read %lu bytes from file %s\n", data->length, file_name);

  return TRUE;
}

bool_t write_db_file(db_data_t *data, const char *file_name)
{
  size_t bytes_written;
  FILE *fp;

  if ((fp = fopen(file_name, "wb")) == NULL)
    {
      printf("Failed to open file '%s' for writing", file_name);
      return FALSE;
    }

  bytes_written = fwrite(data->data, 1, data->length, fp);
  fclose(fp);
  printf("Wrote %u bytes to file %s\n", bytes_written, file_name);

  return TRUE;
}
