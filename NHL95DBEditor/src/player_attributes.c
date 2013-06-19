#include <stdio.h>
#include <string.h>
#include "player_attributes.h"

#define ATT_MIN 25
#define ATT_MAX 200
#define ATT_SCALE 5

#define CASE(str, ret) if (!strcmp(att_name, str)) return ret
#define DEFAULT(ret) return ret

static int deserialize(number_1_t value)
{
  /* Conversion:
      0 -> 25
      1 -> 30
      2 -> 35
      3 -> 40
      4 -> 45
      5 -> 50
      6 -> 55
      7 -> 60
      8 -> 65
      9 -> 70
     10 -> 75
     11 -> 80
     12 -> 85
     13 -> 90
     14 -> 95
     15 -> 100 (0x0f) */
  return ATT_MIN + (ATT_SCALE * value);
}

static number_1_t serialize(int value)
{
  /* Conversion:
      25 -> 0
      30 -> 1
      35 -> 2
      40 -> 3
      45 -> 4
      50 -> 5
      55 -> 6
      60 -> 7
      65 -> 8
      70 -> 9
      75 -> 10
      80 -> 11
      85 -> 12
      90 -> 13
      95 -> 14
     100 -> 15 (0x0f) */
  return (value - ATT_MIN) / ATT_SCALE;
}

static number_1_t *get_att_player(player_att_t *att, const char *att_name)
{
  CASE(ATT_NAME_ACCURACY, &att->accuracy);
  CASE(ATT_NAME_AGGRESSIVENESS, &att->aggressiveness);
  CASE(ATT_NAME_AGILITY, &att->agility);
  CASE(ATT_NAME_CHECKING, &att->checking);
  CASE(ATT_NAME_DEF_AWARENESS, &att->defensive_awareness);
  CASE(ATT_NAME_ENDURANCE, &att->endurance);
  CASE(ATT_NAME_FACEOFFS, &att->face_offs);
  CASE(ATT_NAME_HANDEDNESS, &att->stick_hand);
  CASE(ATT_NAME_OFF_AWARENESS, &att->offensive_awareness);
  CASE(ATT_NAME_PASSING, &att->passing);
  CASE(ATT_NAME_SHOOT_PASS_BIAS, &att->shoot_pass_bias);
  CASE(ATT_NAME_SHOT_POWER, &att->shot_power);
  CASE(ATT_NAME_SPEED, &att->speed);
  CASE(ATT_NAME_STICK_HANDLING, &att->stick_handling);
  CASE(ATT_NAME_UNKNOWN_1, &att->unknown_1);
  CASE(ATT_NAME_UNKNOWN_2, &att->unknown_2);
  CASE(ATT_NAME_UNKNOWN_3, &att->unknown_3);
  CASE(ATT_NAME_UNKNOWN_4, &att->unknown_4);
  CASE(ATT_NAME_UNKNOWN_5, &att->unknown_5);
  CASE(ATT_NAME_WEIGHT, &att->weight);
  DEFAULT(NULL);
}

static number_1_t *get_att_goalie(goalie_att_t *att, const char *att_name)
{
  CASE(ATT_NAME_AGILITY, &att->agility);
  CASE(ATT_NAME_DEF_AWARENESS, &att->defensive_awareness);
  CASE(ATT_NAME_GLOVE_LEFT, &att->glove_left);
  CASE(ATT_NAME_GLOVE_RIGHT, &att->glove_right);
  CASE(ATT_NAME_HANDEDNESS, &att->glove_hand);
  CASE(ATT_NAME_OFF_AWARENESS, &att->offensive_awareness);
  CASE(ATT_NAME_PUCK_CONTROL, &att->puck_control);
  CASE(ATT_NAME_SPEED, &att->speed);
  CASE(ATT_NAME_STICK_LEFT, &att->stick_left);
  CASE(ATT_NAME_STICK_RIGHT, &att->stick_right);
  CASE(ATT_NAME_UNKNOWN_1, &att->unknown_1);
  CASE(ATT_NAME_UNKNOWN_2, &att->unknown_2);
  CASE(ATT_NAME_UNKNOWN_3, &att->unknown_3);
  CASE(ATT_NAME_UNKNOWN_4, &att->unknown_4);
  CASE(ATT_NAME_UNKNOWN_5, &att->unknown_5);
  CASE(ATT_NAME_WEIGHT, &att->weight);
  DEFAULT(NULL);
}

static void print_att_player(player_att_t *att, const char *att_name)
{
  printf(" %s %3d", att_name, deserialize(*get_att_player(att, att_name)));
}

static void print_att_goalie(goalie_att_t *att, const char *att_name)
{
  printf(" %s %3d", att_name, deserialize(*get_att_goalie(att, att_name)));
}

static void print_att_handedness(number_1_t value)
{
  printf(" %s ", ATT_NAME_HANDEDNESS);
  if (value == 0)
    printf("R");
  else if (value == 1)
    printf("L");
  else
    printf("%u", value);
}

static void show_att_player(player_att_t *att)
{
  print_att_handedness(att->stick_hand);
  print_att_player(att, ATT_NAME_SPEED);
  print_att_player(att, ATT_NAME_AGILITY);
  print_att_player(att, ATT_NAME_WEIGHT);
  print_att_player(att, ATT_NAME_SHOT_POWER);
  print_att_player(att, ATT_NAME_CHECKING);
  print_att_player(att, ATT_NAME_STICK_HANDLING);
  print_att_player(att, ATT_NAME_ACCURACY);
  print_att_player(att, ATT_NAME_PASSING);
  print_att_player(att, ATT_NAME_OFF_AWARENESS);
  print_att_player(att, ATT_NAME_DEF_AWARENESS);
  print_att_player(att, ATT_NAME_AGGRESSIVENESS);
  print_att_player(att, ATT_NAME_ENDURANCE);
  print_att_player(att, ATT_NAME_SHOOT_PASS_BIAS);
  print_att_player(att, ATT_NAME_FACEOFFS);
}

static void show_att_goalie(goalie_att_t *att)
{
  print_att_handedness(att->glove_hand);
  print_att_goalie(att, ATT_NAME_GLOVE_LEFT);
  print_att_goalie(att, ATT_NAME_GLOVE_RIGHT);
  print_att_goalie(att, ATT_NAME_STICK_LEFT);
  print_att_goalie(att, ATT_NAME_STICK_RIGHT);
  print_att_goalie(att, ATT_NAME_PUCK_CONTROL);
  print_att_goalie(att, ATT_NAME_SPEED);
  print_att_goalie(att, ATT_NAME_AGILITY);
  print_att_goalie(att, ATT_NAME_WEIGHT);
  print_att_goalie(att, ATT_NAME_OFF_AWARENESS);
  print_att_goalie(att, ATT_NAME_DEF_AWARENESS);
}

void show_attributes(unsigned char *att_data, player_key_t *key)
{
  unsigned char *att = &att_data[key->ofs_attributes];

  if (key_is_goalie(key))
    {
      show_att_goalie((goalie_att_t *) att);
    }
  else
    {
      show_att_player((player_att_t *) att);
    }
}

static void modify_attribute(number_1_t *att, int value_change)
{
  int new_value = deserialize(*att) + value_change;

  if (new_value < ATT_MIN)
    new_value = ATT_MIN;
  else if (new_value > ATT_MAX)
    new_value = ATT_MAX;

  *att = serialize(new_value);
}

void modify_player_attribute(player_att_t *att, const char *att_name,
                             int value_change)
{
  number_1_t *attribute = get_att_player(att, att_name);
  modify_attribute(attribute, value_change);
}

void modify_goalie_attribute(goalie_att_t *att, const char *att_name,
                             int value_change)
{
  number_1_t *attribute = get_att_goalie(att, att_name);
  modify_attribute(attribute, value_change);
}
