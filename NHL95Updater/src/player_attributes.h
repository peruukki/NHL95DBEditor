#pragma once

#include "common_defs.h"

typedef struct key_player_t
{
  char team;
  char jersey;
  char position;
  char first[16];
  char last[17];
  offset ofs_attributes;
  offset ofs_career_stats;
  offset ofs_season_stats;
  number_1 unknown[4];
} key_player;

typedef struct att_player_t
{
  number_1 stick_hand; /* 0 = right, 1 = left */
  number_1 speed;
  number_1 agility;
  number_1 weight;
  number_1 shot_power;
  number_1 checking;
  number_1 stick_handling;
  number_1 accuracy;
  number_1 unknown_1;
  number_1 passing;
  number_1 offensive_awareness;
  number_1 defensive_awareness;
  number_1 aggressiveness;
  number_1 endurance;
  number_1 shoot_pass_bias;
  number_1 unknown_2;
  number_1 unknown_3;
  number_1 unknown_4;
  number_1 unknown_5;
  number_1 face_offs;
} att_player;

typedef struct att_goalie_t
{
  number_1 glove_hand; /* 0 = right, 1 = left */
  number_1 glove_left;
  number_1 glove_right;
  number_1 stick_left;
  number_1 stick_right;
  number_1 puck_control;
  number_1 speed;
  number_1 agility;
  number_1 weight;
  number_1 unknown_1;
  number_1 offensive_awareness;
  number_1 defensive_awareness;
  number_1 unknown_2;
  number_1 unknown_3;
  number_1 unknown_4;
  number_1 unknown_5;
} att_goalie;

void show_key_player(key_player *key);

void show_att_player(att_player *att);

void show_att_goalie(att_goalie *att);

void read_player_data(void);
