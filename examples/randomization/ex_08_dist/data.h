//enum for one hot coding
enum onehot_t {
  STATE_0 = 0, STATE_1 = 1, STATE_2 = 2, STATE_3 = 4,
  STATE_4 = 8, STATE_5 = 16, STATE_6 = 32 };

struct data_t {
  sc_uint<8> field;
  unsigned   payload[5];
  onehot_t   state;
};

