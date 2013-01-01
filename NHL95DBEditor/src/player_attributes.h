#pragma once

#include "common_defs.h"
#include "player_key.h"

typedef struct
{
  number_1_t stick_hand; /* 0 = right, 1 = left */
  number_1_t speed;
  number_1_t agility;
  number_1_t weight;
  number_1_t shot_power;
  number_1_t checking;
  number_1_t stick_handling;
  number_1_t accuracy;
  number_1_t unknown_1;
  number_1_t passing;
  number_1_t offensive_awareness;
  number_1_t defensive_awareness;
  number_1_t aggressiveness;
  number_1_t endurance;
  number_1_t shoot_pass_bias;
  number_1_t unknown_2;
  number_1_t unknown_3;
  number_1_t unknown_4;
  number_1_t unknown_5;
  number_1_t face_offs;
} player_att_t;

typedef struct
{
  number_1_t glove_hand; /* 0 = right, 1 = left */
  number_1_t glove_left;
  number_1_t glove_right;
  number_1_t stick_left;
  number_1_t stick_right;
  number_1_t puck_control;
  number_1_t speed;
  number_1_t agility;
  number_1_t weight;
  number_1_t unknown_1;
  number_1_t offensive_awareness;
  number_1_t defensive_awareness;
  number_1_t unknown_2;
  number_1_t unknown_3;
  number_1_t unknown_4;
  number_1_t unknown_5;
} goalie_att_t;

void show_attributes(unsigned char *att_data, player_key_t *key);
