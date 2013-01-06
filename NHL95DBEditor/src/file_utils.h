#pragma once

#include "common_defs.h"
#include "db_data.h"

bool_t read_db_file(db_data_t *data, const char *file_name);

bool_t write_db_file(db_data_t *data, const char *file_name);
