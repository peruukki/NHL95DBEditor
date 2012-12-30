#include <stdio.h>
#include "constants.h"
#include "file_utils.h"
#include "player_attributes.h"

#define FILE_ATTRIBUTES "ATT.DB"
#define FILE_KEYS "KEY.DB"

#define ATT_MIN 25
#define ATT_SCALE 5

unsigned char attfile[MAX_DATA_LENGTH];
unsigned char keyfile[MAX_DATA_LENGTH];

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

static void show_in_binary(unsigned char value)
{
  unsigned char mask;

  for (mask = 1 << 7; mask; mask = mask >> 1)
    {
      printf("%c", (value & mask) ? '1' : '0');
    }
  printf("=%3u ", value);
}

void show_key_player(key_player *key)
{
  size_t i;

  printf("T: %2u NO: %2u POS: %c NAME: %-15s %-15s UNKNOWN: ",
         key->team, key->jersey, key->position, key->first, key->last);

  show_in_binary(key->unknown[0]);

  for (i = 1; i < sizeof(key->unknown); i++)
    {
      printf("%3u ", key->unknown[i]);
    }
}

void show_att_player(att_player *att)
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

void show_att_goalie(att_goalie *att)
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

void read_player_data(void)
{
  size_t keysize;
  size_t attsize;
  size_t i;

  keysize = read_file(keyfile, sizeof(keyfile), FILE_KEYS);
  attsize = read_file(attfile, sizeof(attfile), FILE_ATTRIBUTES);

  for (i = 0; i < keysize; i += sizeof(key_player))
    {
      key_player *key;

      key = (key_player *) &keyfile[i];
      show_key_player(key);
      if (key->position == 'G')
        {
          att_goalie *att = (att_goalie *) &attfile[key->addr_1];
          show_att_goalie(att);
        }
      else
        {
          att_player *att = (att_player *) &attfile[key->addr_1];
          show_att_player(att);
        }
    }

  write_file(attfile, attsize, FILE_ATTRIBUTES);
}
