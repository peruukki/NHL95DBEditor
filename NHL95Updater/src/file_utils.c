#include <stdio.h>

size_t read_file(unsigned char *buf, size_t buf_len,
                 const char *file_name)
{
  size_t bytes_read;
  FILE *fp;

  fp = fopen(file_name, "rb");
  bytes_read = fread(buf, 1, buf_len, fp);
  fclose(fp);
  printf("Read %u bytes from file %s\n", bytes_read, file_name);

  return bytes_read;
}

size_t write_file(unsigned char *buf, size_t buf_len,
	                const char *file_name)
{
  size_t bytes_written;
  FILE *fp;

  fp = fopen(file_name, "wb");
  bytes_written = fwrite(buf, 1, buf_len, fp);
  fclose(fp);
  printf("Wrote %u bytes to file %s\n", bytes_written, file_name);

  return bytes_written;
}
