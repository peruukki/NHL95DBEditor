#include <string.h>
#include "output.h"
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

player_att_name_t player_att_names[] = {
  /* Value, name, description, for player, for goalie */
  { PLAYER_ATT_ACCURACY, "ACC", "accuracy", TRUE, FALSE },
  { PLAYER_ATT_AGGRESSIVENESS, "AGG", "aggressiveness", TRUE, FALSE },
  { PLAYER_ATT_AGILITY, "AGI", "agility", TRUE, TRUE },
  { PLAYER_ATT_CHECKING, "CHK", "checking", TRUE, FALSE },
  { PLAYER_ATT_DEF_AWARENESS, "DEF", "defensive awareness", TRUE, TRUE },
  { PLAYER_ATT_ENDURANCE, "END", "endurance", TRUE, FALSE },
  { PLAYER_ATT_FACEOFFS, "FAC", "faceoffs", TRUE, FALSE },
  { PLAYER_ATT_GLOVE_LEFT, "GLE", "glove left", FALSE, TRUE },
  { PLAYER_ATT_GLOVE_RIGHT, "GRI", "glove right", FALSE, TRUE },
  { PLAYER_ATT_HANDEDNESS, "HND", "handedness", TRUE, TRUE },
  { PLAYER_ATT_OFF_AWARENESS, "OFF", "offensive awareness", TRUE, TRUE },
  { PLAYER_ATT_PASSING, "PAS", "passing", TRUE, FALSE },
  { PLAYER_ATT_PUCK_CONTROL, "PUC", "puck control", FALSE, TRUE },
  { PLAYER_ATT_SHOOT_PASS_BIAS, "S/P", "shoot/pass bias", TRUE, FALSE },
  { PLAYER_ATT_SHOT_POWER, "SHO", "shot power", TRUE, FALSE },
  { PLAYER_ATT_SPEED, "SPD", "speed", TRUE, TRUE },
  { PLAYER_ATT_STICK_HANDLING, "STI", "stick handling", TRUE, FALSE },
  { PLAYER_ATT_STICK_LEFT, "SLE", "stick left", FALSE, TRUE },
  { PLAYER_ATT_STICK_RIGHT, "SRI", "stick right", FALSE, TRUE },
  { PLAYER_ATT_UNKNOWN_1, "UN1", "unknown 1", TRUE, TRUE },
  { PLAYER_ATT_UNKNOWN_2, "UN2", "unknown 2", TRUE, TRUE },
  { PLAYER_ATT_UNKNOWN_3, "UN3", "unknown 3", TRUE, TRUE },
  { PLAYER_ATT_UNKNOWN_4, "UN4", "unknown 4", TRUE, TRUE },
  { PLAYER_ATT_UNKNOWN_5, "UN5", "unknown 5", TRUE, TRUE },
  { PLAYER_ATT_WEIGHT, "WGT", "weight", TRUE, TRUE },
  { PLAYER_ATT_NUM_VALUES, NULL, NULL, FALSE, FALSE }
};

player_att_t skater_atts[] = {
  PLAYER_ATT_HANDEDNESS,     PLAYER_ATT_SPEED,           PLAYER_ATT_AGILITY,
  PLAYER_ATT_WEIGHT,         PLAYER_ATT_SHOT_POWER,      PLAYER_ATT_CHECKING,
  PLAYER_ATT_STICK_HANDLING, PLAYER_ATT_ACCURACY,        PLAYER_ATT_PASSING,
  PLAYER_ATT_OFF_AWARENESS,  PLAYER_ATT_DEF_AWARENESS,   PLAYER_ATT_AGGRESSIVENESS,
  PLAYER_ATT_ENDURANCE,      PLAYER_ATT_SHOOT_PASS_BIAS, PLAYER_ATT_FACEOFFS
};

player_att_t goalie_atts[] = {
  PLAYER_ATT_HANDEDNESS,  PLAYER_ATT_GLOVE_LEFT,    PLAYER_ATT_GLOVE_RIGHT,  PLAYER_ATT_STICK_LEFT,
  PLAYER_ATT_STICK_RIGHT, PLAYER_ATT_PUCK_CONTROL,  PLAYER_ATT_SPEED,        PLAYER_ATT_AGILITY,
  PLAYER_ATT_WEIGHT,      PLAYER_ATT_OFF_AWARENESS, PLAYER_ATT_DEF_AWARENESS
};

player_att_t get_player_att_enum(const char *att_name, bool_t for_goalie)
{
  int i;

  for (i = 0; i < PLAYER_ATT_NUM_VALUES; i++)
    {
      if ((strcmp(player_att_names[i].name, att_name) == 0) &&
          ((for_goalie && player_att_names[i].for_goalie) ||
           (!for_goalie && player_att_names[i].for_player)))
        return player_att_names[i].value;
    }

  return PLAYER_ATT_NUM_VALUES;
}

static const char *get_player_att_description(player_att_t att_enum)
{
  int i;

  for (i = 0; i < PLAYER_ATT_NUM_VALUES; i++)
    {
      if (player_att_names[i].value == att_enum)
        return player_att_names[i].description;
    }

  return NULL;
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
      INFO("Unknown attribute name '%s'\n", change->att_name);
      return FALSE;
    }
  if (change->att_change % ATT_SCALE != 0)
    {
      INFO("Attribute change value '%d' is not a multiplier of %d\n", change->att_change,
           ATT_SCALE);
      return FALSE;
    }
  return TRUE;
}

static number_1_t *get_att_skater(skater_atts_t *atts, player_att_t att_enum)
{
  switch (att_enum)
    {
    case PLAYER_ATT_ACCURACY:
      return &atts->accuracy;
    case PLAYER_ATT_AGGRESSIVENESS:
      return &atts->aggressiveness;
    case PLAYER_ATT_AGILITY:
      return &atts->agility;
    case PLAYER_ATT_CHECKING:
      return &atts->checking;
    case PLAYER_ATT_DEF_AWARENESS:
      return &atts->defensive_awareness;
    case PLAYER_ATT_ENDURANCE:
      return &atts->endurance;
    case PLAYER_ATT_FACEOFFS:
      return &atts->face_offs;
    case PLAYER_ATT_HANDEDNESS:
      return &atts->stick_hand;
    case PLAYER_ATT_OFF_AWARENESS:
      return &atts->offensive_awareness;
    case PLAYER_ATT_PASSING:
      return &atts->passing;
    case PLAYER_ATT_SHOOT_PASS_BIAS:
      return &atts->shoot_pass_bias;
    case PLAYER_ATT_SHOT_POWER:
      return &atts->shot_power;
    case PLAYER_ATT_SPEED:
      return &atts->speed;
    case PLAYER_ATT_STICK_HANDLING:
      return &atts->stick_handling;
    case PLAYER_ATT_UNKNOWN_1:
      return &atts->unknown_1;
    case PLAYER_ATT_UNKNOWN_2:
      return &atts->unknown_2;
    case PLAYER_ATT_UNKNOWN_3:
      return &atts->unknown_3;
    case PLAYER_ATT_UNKNOWN_4:
      return &atts->unknown_4;
    case PLAYER_ATT_UNKNOWN_5:
      return &atts->unknown_5;
    case PLAYER_ATT_WEIGHT:
      return &atts->weight;
    default:
      INFO("Unknown skater attribute value %d\n", att_enum);
      return NULL;
    }
}

static number_1_t *get_att_goalie(goalie_atts_t *atts, player_att_t att_enum)
{
  switch (att_enum)
    {
    case PLAYER_ATT_AGILITY:
      return &atts->agility;
    case PLAYER_ATT_DEF_AWARENESS:
      return &atts->defensive_awareness;
    case PLAYER_ATT_GLOVE_LEFT:
      return &atts->glove_left;
    case PLAYER_ATT_GLOVE_RIGHT:
      return &atts->glove_right;
    case PLAYER_ATT_HANDEDNESS:
      return &atts->glove_hand;
    case PLAYER_ATT_OFF_AWARENESS:
      return &atts->offensive_awareness;
    case PLAYER_ATT_PUCK_CONTROL:
      return &atts->puck_control;
    case PLAYER_ATT_SPEED:
      return &atts->speed;
    case PLAYER_ATT_STICK_LEFT:
      return &atts->stick_left;
    case PLAYER_ATT_STICK_RIGHT:
      return &atts->stick_right;
    case PLAYER_ATT_UNKNOWN_1:
      return &atts->unknown_1;
    case PLAYER_ATT_UNKNOWN_2:
      return &atts->unknown_2;
    case PLAYER_ATT_UNKNOWN_3:
      return &atts->unknown_3;
    case PLAYER_ATT_UNKNOWN_4:
      return &atts->unknown_4;
    case PLAYER_ATT_UNKNOWN_5:
      return &atts->unknown_5;
    case PLAYER_ATT_WEIGHT:
      return &atts->weight;
    default:
      INFO("Unknown goalie attribute value %d\n", att_enum);
      return NULL;
    }
}

void print_attributes_footer(bool_t is_last_item, format_t format)
{
  if (format == FORMAT_JSON)
    {
      INFO(" }\n    }");
      INFO(is_last_item ? "" : ",");
    }
}

void print_attributes_header(bool_t is_goalie, format_t format)
{
  player_att_t *atts;
  int att_count, i;

  if (format == FORMAT_JSON)
    INFO("      \"attributes\": { ");
  else if (format == FORMAT_CSV)
    {
      atts = is_goalie ? goalie_atts : skater_atts;
      att_count = is_goalie ? ELEM_COUNT(goalie_atts) : ELEM_COUNT(skater_atts);

      for (i = 0; i < att_count; i++)
        {
          INFO("%s", get_player_att_description(atts[i]));

          if (i < att_count - 1)
            print_delimiter(FORMAT_CSV);
        }
    }
}

static void print_att_skater(skater_atts_t *atts, player_att_t att_enum, format_t format)
{
  print_field_name(get_player_att_name(att_enum), format);
  print_field_value_number(deserialize(*get_att_skater(atts, att_enum)), format);
}

static void print_att_goalie(goalie_atts_t *atts, player_att_t att_enum, format_t format)
{
  print_field_name(get_player_att_name(att_enum), format);
  print_field_value_number(deserialize(*get_att_goalie(atts, att_enum)), format);
}

static const char *get_handedness_str(number_1_t value)
{
  if (value == 0)
    return "R";
  else if (value == 1)
    return "L";
  else
    return "<Unknown handedness>";
}

static void print_att_handedness(number_1_t value, format_t format)
{
  print_field_name(get_player_att_name(PLAYER_ATT_HANDEDNESS), format);
  print_field_value_string(get_handedness_str(value), format);
}

static void show_att_skater(skater_atts_t *att, format_t format)
{
  int i;

  for (i = 0; i < ELEM_COUNT(skater_atts); i++)
    {
      if (i > 0)
        print_delimiter(format);

      if (skater_atts[i] == PLAYER_ATT_HANDEDNESS)
        print_att_handedness(att->stick_hand, format);
      else
        print_att_skater(att, skater_atts[i], format);
    }
}

static void show_att_goalie(goalie_atts_t *att, format_t format)
{
  int i;

  for (i = 0; i < ELEM_COUNT(goalie_atts); i++)
    {
      if (i > 0)
        print_delimiter(format);

      if (goalie_atts[i] == PLAYER_ATT_HANDEDNESS)
        print_att_handedness(att->glove_hand, format);
      else
        print_att_goalie(att, goalie_atts[i], format);
    }
}

void show_attributes(unsigned char *att_data, player_key_t *key, format_t format)
{
  unsigned char *att = &att_data[key->ofs_attributes];

  if (key_is_goalie(key))
    show_att_goalie((goalie_atts_t *) att, format);
  else
    show_att_skater((skater_atts_t *) att, format);
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

void modify_skater_attribute(skater_atts_t *atts, player_att_t att_enum, int value_change)
{
  number_1_t *attribute = get_att_skater(atts, att_enum);
  modify_attribute(attribute, value_change);
}

void modify_goalie_attribute(goalie_atts_t *atts, player_att_t att_enum, int value_change)
{
  number_1_t *attribute = get_att_goalie(atts, att_enum);
  modify_attribute(attribute, value_change);
}
