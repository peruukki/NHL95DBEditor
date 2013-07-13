#pragma once

#define CHANGE_LOG_FILE "change-log.txt"

void add_change_log_entry(const char *cmd, const char *att_name, int att_change);

void dump_change_log_entries(void);
