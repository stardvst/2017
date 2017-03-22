#include <exception>
#include "Virtual_memory.hpp"


Virtual_memory::Virtual_memory(int virtual_size)
  : p_size(1024), v_size(virtual_size), v_next_addr(0), p_next_addr(0) {}

int Virtual_memory::allocate(int size) {
  if(p_next_addr == p_size) {
    throw std::exception("no more memory available\n");
  }

  table[v_next_addr].first = p_next_addr;
  table[v_next_addr].second = size;

  int old_addr = v_next_addr;
  p_next_addr += size;
  v_next_addr += size;
  return old_addr;
}

void Virtual_memory::free(int v_addr) {
  if(table.find(v_addr) == table.end()) {
    throw std::exception("invalid or unallocated memory address\n");
  }

  // if the segment is not the last one, shift the segments, update the table
  // else just decrement the pointer
  if(table[v_addr].first + table[v_addr].second != p_next_addr) {
    int empty_mem = table[v_addr].first;
    for(int i = table[v_addr].first + table[v_addr].second; i < p_next_addr; ++i) {
      p_mem[empty_mem++] = p_mem[i];
    }

    for(std::map<int, std::pair<int, int> >::iterator it = table.find(v_addr);
        it != table.end(); ++it) {
      it->second.first -= table[v_addr].second;
    }
  }

  p_next_addr -= table[v_addr].second;
  table.erase(v_addr);
}

char& Virtual_memory::operator[](int v_addr) {
  if(table.find(v_addr) == table.end()) {
    throw std::exception("invalid memory access\n");
  }

  return p_mem[table[v_addr].first];
}
