#ifndef VIRTUAL_MEMORY_HPP
#define VIRTUAL_MEMORY_HPP

#include <utility>
#include <map>


class Virtual_memory {
public:
  Virtual_memory(int = 4096);

  int /* virtual address */ allocate(int);
  void free(int);

  char& operator[](int);
private:
  const int p_size;
  int v_size;
  int v_next_addr;
  int p_next_addr;
  char p_mem[1024];
  std::map<int, std::pair<int, int> > table;
};

#endif // !VIRTUAL_MEMORY_HPP
