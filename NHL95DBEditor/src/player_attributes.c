#include <stdio.h>
#include <string.h>
#include "player_attributes.h"

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

player_att_name_t player_att_names[] =
{
  { PLAYER_ATT_ACCURACY, "ACC", "accuracy" },
  { PLAYER_ATT_AGGRESSIVENESS, "AGG", "aggressiveness" },
  { PLAYER_ATT_AGILITY, "AGI", "agility" },
  { PLAYER_ATT_CHECKING, "CHK", "checking" },
  { PLAYER_ATT_DEF_AWARENESS, "DEF", "defensive awareness" },
  { PLAYER_ATT_ENDURANCE, "END", "endurance" },
  { PLAYER_ATT_FACEOFFS, "FAC", "faceoffs" },
  { PLAYER_ATT_GLOVE_LEFT, "GLE", "glove left" },
  { PLAYER_ATT_GLOVE_RIGHT, "GRI", "glove right" },
  { PLAYER_ATT_HANDEDNESS, "HND", "handedness (shoots from / glove hand)" },
  { PLAYER_ATT_OFF_AWARENESS, "OFF", "offensive awareness" },
  { PLAYER_ATT_PASSING, "PAS", "passing" },
  { PLAYER_ATT_PUCK_CONTROL, "PUC", "puck control" },
  { PLAYER_ATT_SHOOT_PASS_BIAS, "S/P", "shoot/pass bias" },
  { PLAYER_ATT_SHOT_POWER, "SHO", "shot power" },
  { PLAYER_ATT_SPEED, "SPD", "speed" },
  { PLAYER_ATT_STICK_HANDLING, "STI", "stick handling" },
  { PLAYER_ATT_STICK_LEFT, "SLE", "stick left" },
  { PLAYER_ATT_STICK_RIGHT, "SRI", "stick right" },
  { PLAYER_ATT_UNKNOWN_1, "UN1", "unknown 1" },
  { PLAYER_ATT_UNKNOWN_2, "UN2", "unknown 2" },
  { PLAYER_ATT_UNKNOWN_3, "UN3", "unknown 3" },
  { PLAYER_ATT_UNKNOWN_4, "UN4", "unknown 4" },
  { PLAYER_ATT_UNKNOWN_5, "UN5", "unknown 5" },
  { PLAYER_ATT_WEIGHT, "WGT", "weight" },
  { PLAYER_ATT_NUM_VALUES, NULL, NULL }
};

player_att_t get_player_att_enum(const char *att_name)
{
  int i;

  for (i = 0; i < PLAYER_ATT_NUM_VALUES; i++)
    {
      if (strcmp(player_att_names[i].name, att_name) == 0)
        return player_att_names[i].value;
    }

  return PLAYER_ATT_NUM_VALUES;
}

const char *get_player_att_name(player_att_t att_enum)
{
  int i;

  for (i = 0; i < PLAYER_ATT_NUM_VALUES; i++)
    {
      if (player_att_names[i].value == att_enum)
        return player_att_names[i].name;
    }

  return NULL;
}

bool_t validate_att_change(player_att_change_t *change)
{
  if (change->att_enum >= PLAYER_ATT_NUM_VALUES)
    {
      printf("Unknown attribute name '%s'\n", change->att_name);
      return FALSE;
    }
  if (change->att_change % ATT_SCALE != 0)
    {
      printf("Attribute change value '%d' is not a multiplier of %d\n",
             change->att_change, ATT_SCALE);
      return FALSE;
    }
  return TRUE;
}

static number_1_t *get_att_player(player_atts_t *atts, player_att_t att_enum)
{
  switch (att_enum)
    {
    case PLAYER_ATT_ACCURACY: return &atts->accuracy;
    case PLAYER_ATT_AGGRESSIVENESS: return &atts->aggressiveness;
    case PLAYER_ATT_AGILITY: return &atts->agility;
    case PLAYER_ATT_CHECKING: return &atts->checking;
    case PLAYER_ATT_DEF_AWARENESS: return &atts->defensive_awareness;
    case PLAYER_ATT_ENDURANCE: return &atts->endurance;
    case PLAYER_ATT_FACEOFFS: return &atts->face_offs;
    case PLAYER_ATT_HANDEDNESS: return &atts->stick_hand;
    case PLAYER_ATT_OFF_AWARENESS: return &atts->offensive_awareness;
    case PLAYER_ATT_PASSING: return &atts->passing;
    case PLAYER_ATT_SHOOT_PASS_BIAS: return &atts->shoot_pass_bias;
    case PLAYER_ATT_SHOT_POWER: return &atts->shot_power;
    case PLAYER_ATT_SPEED: return &atts->speed;
    case PLAYER_ATT_STICK_HANDLING: return &atts->stick_handling;
    case PLAYER_ATT_UNKNOWN_1: return &atts->unknown_1;
    case PLAYER_ATT_UNKNOWN_2: return &atts->unknown_2;
    case PLAYER_ATT_UNKNOWN_3: return &atts->unknown_3;
    case PLAYER_ATT_UNKNOWN_4: return &atts->unknown_4;
    case PLAYER_ATT_UNKNOWN_5: return &atts->unknown_5;
    case PLAYER_ATT_WEIGHT: return &atts->weight;
    default:
      printf("Unknown attribute value %d\n", att_enum);
      return NULL;
    }
}

static number_1_t *get_att_goalie(goalie_atts_t *atts, player_att_t att_enum)
{
  switch (att_enum)
    {
    case PLAYER_ATT_AGILITY: return &atts->agility;
    case PLAYER_ATT_DEF_AWARENESS: return &atts->defensive_awareness;
    case PLAYER_ATT_GLOVE_LEFT: return &atts->glove_left;
    case PLAYER_ATT_GLOVE_RIGHT: return &atts->glove_right;
    case PLAYER_ATT_HANDEDNESS: return &atts->glove_hand;
    case PLAYER_ATT_OFF_AWARENESS: return &atts->offensive_awareness;
    case PLAYER_ATT_PUCK_CONTROL: return &atts->puck_control;
    case PLAYER_ATT_SPEED: return &atts->speed;
    case PLAYER_ATT_STICK_LEFT: return &atts->stick_left;
    case PLAYER_ATT_STICK_RIGHT: return &atts->stick_right;
    case PLAYER_ATT_UNKNOWN_1: return &atts->unknown_1;
    case PLAYER_ATT_UNKNOWN_2: return &atts->unknown_2;
    case PLAYER_ATT_UNKNOWN_3: return &atts->unknown_3;
    case PLAYER_ATT_UNKNOWN_4: return &atts->unknown_4;
    case PLAYER_ATT_UNKNOWN_5: return &atts->unknown_5;
    case PLAYER_ATT_WEIGHT: return &atts->weight;
    default:
      printf("Unknown attribute value %d\n", att_enum);
      return NULL;
    }
}

static void print_att_player(player_atts_t *atts, player_att_t att_enum)
{
  printf(" %s %3d", get_player_att_name(att_enum),
         deserialize(*get_att_player(atts, att_enum)));
}

static void print_att_goalie(goalie_atts_t *atts, player_att_t att_enum)
{
  printf(" %s %3d", get_player_att_name(att_enum),
         deserialize(*get_att_goalie(atts, att_enum)));
}

static void print_att_handedness(number_1_t value)
{
  printf(" %s ", get_player_att_name(PLAYER_ATT_HANDEDNESS));
  if (value == 0)
    printf("R");
  else if (value == 1)
    printf("L");
  else
    printf("%u", value);
}

static void show_att_player(player_atts_t *att)
{
  print_att_handedness(att->stick_hand);
  print_att_player(att, PLAYER_ATT_SPEED);
  print_att_player(att, PLAYER_ATT_AGILITY);
  print_att_player(att, PLAYER_ATT_WEIGHT);
  print_att_player(att, PLAYER_ATT_SHOT_POWER);
  print_att_player(att, PLAYER_ATT_CHECKING);
  print_att_player(att, PLAYER_ATT_STICK_HANDLING);
  print_att_player(att, PLAYER_ATT_ACCURACY);
  print_att_player(att, PLAYER_ATT_PASSING);
  print_att_player(att, PLAYER_ATT_OFF_AWARENESS);
  print_att_player(att, PLAYER_ATT_DEF_AWARENESS);
  print_att_player(att, PLAYER_ATT_AGGRESSIVENESS);
  print_att_player(att, PLAYER_ATT_ENDURANCE);
  print_att_player(att, PLAYER_ATT_SHOOT_PASS_BIAS);
  print_att_player(att, PLAYER_ATT_FACEOFFS);
}

static void show_att_goalie(goalie_atts_t *att)
{
  print_att_handedness(att->glove_hand);
  print_att_goalie(att, PLAYER_ATT_GLOVE_LEFT);
  print_att_goalie(att, PLAYER_ATT_GLOVE_RIGHT);
  print_att_goalie(att, PLAYER_ATT_STICK_LEFT);
  print_att_goalie(att, PLAYER_ATT_STICK_RIGHT);
  print_att_goalie(att, PLAYER_ATT_PUCK_CONTROL);
  print_att_goalie(att, PLAYER_ATT_SPEED);
  print_att_goalie(att, PLAYER_ATT_AGILITY);
  print_att_goalie(att, PLAYER_ATT_WEIGHT);
  print_att_goalie(att, PLAYER_ATT_OFF_AWARENESS);
  print_att_goalie(att, PLAYER_ATT_DEF_AWARENESS);
}

void show_attributes(unsigned char *att_data, player_key_t *key)
{
  unsigned char *att = &att_data[key->ofs_attributes];

  if (key_is_goalie(key))
    {
      show_att_goalie((goalie_atts_t *) att);
    }
  else
    {
      show_att_player((player_atts_t *) att);
    }
}

static void modify_attribute(number_1_t *att, int value_change)
{
  int new_value;

  if (!att)
    return;

  new_value = deserialize(*att) + value_change;

  if (new_value < ATT_MIN)
    new_value = ATT_MIN;
  else if (new_value > ATT_MAX)
    new_value = ATT_MAX;

  *att = serialize(new_value);
}

void modify_player_attribute(player_atts_t *atts, player_att_t att_enum,
                             int value_change)
{
  number_1_t *attribute = get_att_player(atts, att_enum);
  modify_attribute(attribute, value_change);
}

void modify_goalie_attribute(goalie_atts_t *atts, player_att_t att_enum,
                             int value_change)
{
  number_1_t *attribute = get_att_goalie(atts, att_enum);
  modify_attribute(attribute, value_change);
}
