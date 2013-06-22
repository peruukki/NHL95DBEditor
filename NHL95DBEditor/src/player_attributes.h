#pragma once

#include "common_defs.h"
#include "player_key.h"

typedef enum
{
  PLAYER_ATT_ACCURACY,
  PLAYER_ATT_AGGRESSIVENESS,
  PLAYER_ATT_AGILITY,
  PLAYER_ATT_CHECKING,
  PLAYER_ATT_DEF_AWARENESS,
  PLAYER_ATT_ENDURANCE,
  PLAYER_ATT_FACEOFFS,
  PLAYER_ATT_GLOVE_LEFT,
  PLAYER_ATT_GLOVE_RIGHT,
  PLAYER_ATT_HANDEDNESS,
  PLAYER_ATT_OFF_AWARENESS,
  PLAYER_ATT_PASSING,
  PLAYER_ATT_PUCK_CONTROL,
  PLAYER_ATT_SHOOT_PASS_BIAS,
  PLAYER_ATT_SHOT_POWER,
  PLAYER_ATT_SPEED,
  PLAYER_ATT_STICK_HANDLING,
  PLAYER_ATT_STICK_LEFT,
  PLAYER_ATT_STICK_RIGHT,
  PLAYER_ATT_UNKNOWN_1,
  PLAYER_ATT_UNKNOWN_2,
  PLAYER_ATT_UNKNOWN_3,
  PLAYER_ATT_UNKNOWN_4,
  PLAYER_ATT_UNKNOWN_5,
  PLAYER_ATT_WEIGHT,
  PLAYER_ATT_NUM_VALUES /* Must be last */
} player_att_t;

typedef struct
{
  player_att_t att_enum;
  const char *att_name;
  int att_change;
} player_att_change_t;

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
} player_atts_t;

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
} goalie_atts_t;

player_att_t get_player_att_enum(const char *att_name);

const char *get_player_att_name(player_att_t att_enum);

bool_t validate_att_change(player_att_change_t *change);

void show_attributes(unsigned char *att_data, player_key_t *key);

void modify_player_attribute(player_atts_t *atts, player_att_t att_enum,
                             int value_change);

void modify_goalie_attribute(goalie_atts_t *atts, player_att_t att_enum,
                             int value_change);
