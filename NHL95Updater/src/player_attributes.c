#include <stdio.h>
#include "player_attributes.h"

#define ATT_MIN 25
#define ATT_SCALE 5

static int convert(int x)
{
  /* Conversion:
     25 - 0
     30 - 1
     35 - 2
     40 - 3
     45 - 4
     50 - 5
     55 - 6
     60 - 7
     65 - 8
     70 - 9
     75 - 10
     80 - 11
     85 - 12
     90 - 13
     95 - 14
     100 - 15 (0x0f) */
  return ATT_MIN + (ATT_SCALE * x);
}

static void show_att_player(att_player *att)
{
  if (att->stick_hand == 0)
    {
      printf("S: R");
    }
  else if (att->stick_hand == 1)
    {
      printf("S: L");
    }
  else
    {
      printf("S: %u", att->stick_hand);
    }

  printf(" SPD %3d", convert(att->speed));
  printf(" AGI %3d", convert(att->agility));
  printf(" WGT %3d", convert(att->weight));
  printf(" SHO %3d", convert(att->shot_power));
  printf(" CHK %3d", convert(att->checking));
  printf(" STI %3d", convert(att->stick_handling));
  printf(" ACC %3d", convert(att->accuracy));
  printf(" PAS %3d", convert(att->passing));
  printf(" OFF %3d", convert(att->offensive_awareness));
  printf(" DEF %3d", convert(att->defensive_awareness));
  printf(" AGG %3d", convert(att->aggressiveness));
  printf(" END %3d", convert(att->endurance));
  printf(" S/P %3d", convert(att->shoot_pass_bias));
  printf(" FAC %3d", convert(att->face_offs));
  printf("\n");
}

static void show_att_goalie(att_goalie *att)
{
  if (att->glove_hand == 0)
    {
      printf("S: R");
    }
  else if (att->glove_hand == 1)
    {
      printf("S: L");
    }
  else
    {
      printf("S: %u", att->glove_hand);
    }

  printf(" GLE %3d", convert(att->glove_left));
  printf(" GRI %3d", convert(att->glove_right));
  printf(" SLE %3d", convert(att->stick_left));
  printf(" SRI %3d", convert(att->stick_right));
  printf(" PCK %3d", convert(att->puck_control));
  printf(" SPD %3d", convert(att->speed));
  printf(" AGI %3d", convert(att->agility));
  printf(" WGT %3d", convert(att->weight));
  printf(" OFF %3d", convert(att->offensive_awareness));
  printf(" DEF %3d", convert(att->defensive_awareness));
  printf("\n");
}

void show_attributes(unsigned char *att_data, key_player *key)
{
  unsigned char *att = &att_data[key->ofs_attributes];

  if (key_is_goalie(key))
    {
      show_att_goalie((att_goalie *) att);
    }
  else
    {
      show_att_player((att_player *) att);
    }
}
