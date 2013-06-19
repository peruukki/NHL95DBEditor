#pragma once

#include "common_defs.h"
#include "player_key.h"

#define ATT_NAME_ACCURACY "ACC"
#define ATT_NAME_AGGRESSIVENESS "AGG"
#define ATT_NAME_AGILITY "AGI"
#define ATT_NAME_CHECKING "CHK"
#define ATT_NAME_DEF_AWARENESS "DEF"
#define ATT_NAME_ENDURANCE "END"
#define ATT_NAME_FACEOFFS "FAC"
#define ATT_NAME_GLOVE_LEFT "GLE"
#define ATT_NAME_GLOVE_RIGHT "GRI"
#define ATT_NAME_HANDEDNESS "HND"
#define ATT_NAME_OFF_AWARENESS "OFF"
#define ATT_NAME_PASSING "PAS"
#define ATT_NAME_PUCK_CONTROL "PUC"
#define ATT_NAME_SHOOT_PASS_BIAS "S/P"
#define ATT_NAME_SHOT_POWER "SHO"
#define ATT_NAME_SPEED "SPD"
#define ATT_NAME_STICK_HANDLING "STI"
#define ATT_NAME_STICK_LEFT "SLE"
#define ATT_NAME_STICK_RIGHT "SRI"
#define ATT_NAME_UNKNOWN_1 "UN1"
#define ATT_NAME_UNKNOWN_2 "UN2"
#define ATT_NAME_UNKNOWN_3 "UN3"
#define ATT_NAME_UNKNOWN_4 "UN4"
#define ATT_NAME_UNKNOWN_5 "UN5"
#define ATT_NAME_WEIGHT "WGT"

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
