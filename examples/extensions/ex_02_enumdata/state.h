//enum for one hot coding
enum onehot_t {
  STATE_0 = 0, STATE_1 = 1, STATE_2 = 2, STATE_3 = 4,
  STATE_4 = 8, STATE_5 = 16, STATE_6 = 32 };

struct state_t {
  onehot_t state;
  int      delay;
  unsigned data;
};

