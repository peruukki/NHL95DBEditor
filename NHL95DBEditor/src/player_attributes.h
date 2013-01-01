#pragma once

#include "common_defs.h"
#include "player_key.h"

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

void show_attributes(unsigned char *att_data, key_player *key);
