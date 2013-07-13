#pragma once

#define CHANGE_LOG_FILE "change-log.txt"

void add_log_entry(const char *cmd, const char *att_name, int att_change);
