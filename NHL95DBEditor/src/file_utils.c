#include <errno.h>
#include "file_utils.h"
#include "output.h"

static size_t read_db_data(db_data_t *data, const char *file_name)
{
  FILE *fp;

  if ((fp = fopen(file_name, "rb")) == NULL)
    {
      INFO("Failed to open file '%s' for reading", file_name);
      return 0;
    }

  data->length = fread(data->data, 1, sizeof(data->data), fp);
  fclose(fp);

  return data->length;
}

bool_t read_db_file(db_data_t *data, const char *file_name)
{
  size_t bytes_read = read_db_data(data, file_name);

  if (bytes_read)
    DEBUG("Read %lu bytes from file %s\n", bytes_read, file_name);

  return bytes_read != 0;
}

static size_t write_db_data(db_data_t *data, const char *file_name)
{
  size_t bytes_written;
  FILE *fp;

  if ((fp = fopen(file_name, "wb")) == NULL)
    {
      INFO("Failed to open file '%s' for writing", file_name);
      return 0;
    }

  bytes_written = fwrite(data->data, 1, data->length, fp);
  fclose(fp);

  return bytes_written;
}

bool_t write_db_file(db_data_t *data, const char *file_name)
{
  size_t bytes_written = read_db_data(data, file_name);

  if (bytes_written)
    DEBUG("Wrote %u bytes to file %s\n", bytes_written, file_name);

  return bytes_written != 0;
}

bool_t file_exists(const char *file_name)
{
  FILE *fp;

  if ((fp = fopen(file_name, "rb")) == NULL)
    return (errno != ENOENT);

  fclose(fp);
  return TRUE;
}

bool_t copy_file(const char *src_name, const char *dst_name)
{
  db_data_t data;

  if (read_db_data(&data, src_name) == 0)
    goto error;

  if (write_db_data(&data, dst_name) == 0)
    goto error;

  INFO("copied file %s to %s\n", src_name, dst_name);
  return TRUE;

error:
  INFO("failed to copy file %s to %s\n", src_name, dst_name);
  return FALSE;
}

bool_t delete_file(const char *file_name)
{
  INFO("Deleting file %s\n", file_name);
  if (remove(file_name) != 0)
    {
      INFO("Failed to delete file %s: error %d\n", file_name, errno);
      return FALSE;
    }

  return TRUE;
}
