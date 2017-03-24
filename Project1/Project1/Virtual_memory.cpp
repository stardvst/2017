#include <exception>
#include "Virtual_memory.hpp"


Virtual_memory::Virtual_memory(int virtual_size)
  : p_size(1024), v_size(virtual_size), v_next_addr(0), p_next_addr(0) {}

int Virtual_memory::allocate(int size) {
  if(p_next_addr == p_size) {
    throw std::exception("no more memory available\n");
  }

  table[v_next_addr] = p_next_addr;

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
  if(p_next_addr - table[v_addr] > 0) {
    int empty_mem = table[v_addr];
    std::map<int, int>::const_iterator current = table.find(v_addr);
    std::map<int, int>::const_iterator old = current;
    ++current; // to start copying bytes from the next segment

    // calculate memory size to be deleted
    int del_size = (*current).second - (*old).second;

    for(int i = (*current).second; i < p_next_addr; ++i) {
      p_mem[empty_mem++] = p_mem[i];
    }

    // starting from the next segment, decrement physical addresses in table
    for(std::map<int, int>::iterator it = ++table.find(v_addr); it != table.end(); ++it) {
      (*it).second -= del_size;
    }
  }

  p_next_addr -= table[v_addr];
  table.erase(v_addr);
}

char& Virtual_memory::operator[](int v_addr) {
  if(table.find(v_addr) == table.end()) {
    throw std::exception("invalid memory access\n");
  }

  return p_mem[table[v_addr]];
}
