#include <stdio.h>

#define FILE_ATTRIBUTES "ATT.DB"
#define FILE_KEYS "KEY.DB"

#define DATA_LENGTH 65000
#define ATT_MIN 25
#define ATT_SCALE 5

struct key_player
{
  char team;
  char jersey;
  char position;
  char first[16];
  char last[16];
  unsigned char unknown_1;
  int addr_1;
  int addr_2;
  unsigned char unknown_2[8];
};

struct att_player
{
  unsigned char stick_hand; /* 0 = right, 1 = left */
  unsigned char speed;
  unsigned char agility;
  unsigned char weight;
  unsigned char shot_power;
  unsigned char checking;
  unsigned char stick_handling;
  unsigned char accuracy;
  unsigned char unknown_1;
  unsigned char passing;
  unsigned char offensive_awareness;
  unsigned char defensive_awareness;
  unsigned char aggressiveness;
  unsigned char endurance;
  unsigned char shoot_pass_bias;
  unsigned char unknown_2;
  unsigned char unknown_3;
  unsigned char unknown_4;
  unsigned char unknown_5;
  unsigned char face_offs;
};

struct att_goalie
{
  unsigned char glove_hand; /* 0 = right, 1 = left */
  unsigned char glove_left;
  unsigned char glove_right;
  unsigned char stick_left;
  unsigned char stick_right;
  unsigned char puck_control;
  unsigned char speed;
  unsigned char agility;
  unsigned char weight;
  unsigned char unknown_1;
  unsigned char offensive_awareness;
  unsigned char defensive_awareness;
  unsigned char unknown_2;
  unsigned char unknown_3;
  unsigned char unknown_4;
  unsigned char unknown_5;
};

unsigned char attfile[DATA_LENGTH];
unsigned char keyfile[DATA_LENGTH];

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

static void show_key_player(struct key_player *key)
{
  printf("T: %2d NO: %2d POS: %c NAME: %-10s %-10s ",
         key->team, key->jersey, key->position, key->first, key->last);
}

static void show_att_player(struct att_player *att)
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

static void show_att_goalie(struct att_goalie *att)
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

static size_t read_file(unsigned char *buf, size_t buf_len,
					              const char *file_name)
{
  size_t bytes_read;
  FILE *fp;

  fp = fopen(file_name, "rb");
  bytes_read = fread(buf, 1, buf_len, fp);
  fclose(fp);
  printf("Read %u bytes from file %s\n", bytes_read, file_name);

  return bytes_read;
}

static size_t write_file(unsigned char *buf, size_t buf_len,
					               const char *file_name)
{
  size_t bytes_written;
  FILE *fp;

  fp = fopen(file_name, "wb");
  bytes_written = fwrite(buf, 1, buf_len, fp);
  fclose(fp);
  printf("Wrote %u bytes to file %s\n", bytes_written, file_name);

  return bytes_written;
}

int main(int argc, char *argv[])
{
  size_t keysize;
  size_t attsize;
  size_t i;

  keysize = read_file(keyfile, sizeof(keyfile), FILE_KEYS);
  attsize = read_file(attfile, sizeof(attfile), FILE_ATTRIBUTES);

  for (i = 0; i < keysize; i += sizeof(struct key_player))
    {
      struct key_player *key;

      key = (struct key_player *) &keyfile[i];
      show_key_player(key);
      if (key->position == 'G')
        {
          struct att_goalie *att = (struct att_goalie *) &attfile[key->addr_1];
          show_att_goalie(att);
        }
      else
        {
          struct att_player *att = (struct att_player *) &attfile[key->addr_1];
          show_att_player(att);
        }
    }

  write_file(attfile, attsize, FILE_ATTRIBUTES);
  return 0;
}