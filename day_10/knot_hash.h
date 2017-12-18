
struct KnotHash {
  uint8_t data[16];
};

void process(uint8_t *data, unsigned pos, unsigned len) {
  for(unsigned i = 0; i < len / 2; ++i) {
    unsigned i1 = (pos + i) % 256;
    unsigned i2 = (pos + len - i - 1) % 256;
    uint8_t tmp = data[i1];
    data[i1] = data[i2];
    data[i2] = tmp;
  }
}


KnotHash knot_hash(std::vector<uint8_t> input) {
  input.push_back(17);
  input.push_back(31);
  input.push_back(73);
  input.push_back(47);
  input.push_back(23);
  
  uint8_t data[256];
  for(unsigned i = 0; i < 256; ++i) {
    data[i] = uint8_t(i);
  }

  unsigned pos = 0;
  unsigned skip = 0;

  for(int turn = 0; turn < 64; ++turn) {
    for(auto const len: input) {
      process(data, pos, len);
      pos = (pos + skip + len) % 256;
      ++skip;
    }
  }

  KnotHash hash;
  for(int i=0; i < 16; ++i) {
    hash.data[i] = 0;
    for(int k = 0; k < 16; ++k) {
      hash.data[i] ^= data[16*i+k];
    }
  }

  return hash;
}
