typedef struct key_player_t
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
} key_player;

typedef struct att_player_t
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
} att_player;

typedef struct att_goalie_t
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
} att_goalie;

void show_key_player(key_player *key);

void show_att_player(att_player *att);

void show_att_goalie(att_goalie *att);

void read_player_data(void);
