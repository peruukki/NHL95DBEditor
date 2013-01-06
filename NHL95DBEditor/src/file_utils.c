#include <stdio.h>
#include "file_utils.h"

size_t read_db_file(db_data_t *data, const char *file_name)
{
  FILE *fp;

  if ((fp = fopen(file_name, "rb")) == NULL)
    {
      printf("Failed to read file '%s'", file_name);
      return INVALID_DB_DATA_OFFSET;
    }

  data->length = fread(data->data, 1, sizeof(data->data), fp);
  fclose(fp);
  printf("Read %lu bytes from file %s\n", data->length, file_name);

  return data->length;
}

size_t write_db_file(db_data_t *data, const char *file_name)
{
  size_t bytes_written;
  FILE *fp;

  fp = fopen(file_name, "wb");
  bytes_written = fwrite(data->data, 1, data->length, fp);
  fclose(fp);
  printf("Wrote %u bytes to file %s\n", bytes_written, file_name);

  return bytes_written;
}
