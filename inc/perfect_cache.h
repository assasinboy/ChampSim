#include <vector>
#include <string>

using namespace std;

 extern char buf[8];
 extern unsigned long num_inputs;

struct blackscholes{
  float input1;
};

struct trace{
  uint64_t input1;
};

struct bodytrack{
  int input1;
  unsigned char input2;
};

struct canneal{
  int input1, input2;
  float input3;
};

struct streamcluster{
  float input1, input2, input3;
};

template <typename T>
inline void hash_combine(size_t& seed, const T& v) {
  std::hash<T> hasher;
  seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

struct KeyHash {
  size_t operator()(const streamcluster& k) const {
    size_t h = std::hash<float>()(k.input1);
    hash_combine(h,k.input2);
    hash_combine(h,k.input3);
    return h;
  }
  size_t operator()(const blackscholes& k) const {
    size_t h = std::hash<float>()(k.input1);
    return h;
  }
  size_t operator()(const bodytrack& k) const {
    size_t h = std::hash<int>()(k.input1);
    hash_combine(h, (int)k.input2);
    return h;
  }
  size_t operator()(const canneal& k) const {
    size_t h = std::hash<float>()((float)k.input1);
    hash_combine(h, (float)k.input2);
    hash_combine(h, k.input3);
    return h;
  }
  size_t operator()(const trace& k) const {
    size_t h = std::hash<uint64_t>()(k.input1);
    return h;
  }
};


struct StructEqual{
  /*bool operator()(const streamcluster& lhs, const streamcluster& rhs) const{
    const streamcluster* addr1 = &lhs;
    const streamcluster* addr2 = &rhs;
    bool Equal = true;
    for (size_t byte = 0; byte < sizeof(lhs); byte++){
      const unsigned char single1 = *(reinterpret_cast<const unsigned char*>(addr1)+byte);
      const unsigned char single2 = *(reinterpret_cast<const unsigned char*>(addr2)+byte);
      Equal = Equal && (single1 == single2);
    }
    return Equal;
  }*/
  template <typename T>
  bool operator()(const T& lhs, const T& rhs) const{
    const T* addr1 = &lhs;
    const T* addr2 = &rhs;
    bool Equal = true;
    for (size_t byte = 0; byte < sizeof(lhs); byte++){
      const unsigned char single1 = *(reinterpret_cast<const unsigned char*>(addr1)+byte);
      const unsigned char single2 = *(reinterpret_cast<const unsigned char*>(addr2)+byte);
      Equal = Equal && (single1 == single2);
    }
    return Equal;
  }
};

