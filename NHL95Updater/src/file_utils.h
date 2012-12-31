#pragma once

size_t read_file(unsigned char *buf, size_t buf_len,
                 const char *file_name);

size_t write_file(unsigned char *buf, size_t buf_len,
                  const char *file_name);
