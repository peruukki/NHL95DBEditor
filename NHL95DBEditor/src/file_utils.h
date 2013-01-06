#pragma once

#include "db_data.h"

size_t read_db_file(db_data_t *data, const char *file_name);

size_t write_db_file(db_data_t *data, const char *file_name);
