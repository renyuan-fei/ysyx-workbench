#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <verilated.h>
#include "verilated_vcd_c.h"
#include "../obj_dir/Vtop.h"

#define MAX_TIME 20
vluint64_t sim_time = 0;

int main(int argc, const char** argv) {
  Vtop *vtop = new Vtop;
  Verilated::traceEverOn(true);
  VerilatedVcdC *m_trace = new VerilatedVcdC;
  vtop->trace(m_trace, 5);
  m_trace->open("waveformd.vcd");
  while (sim_time<MAX_TIME)
  {
    int a = rand() & 1;
    int b = rand() & 1;
    vtop->a = a;
    vtop->b = b;
    vtop->eval();
    printf("a = %d, b = %d, f = %d\n", a, b, vtop->f);
    assert(vtop->f == (a ^ b));
    m_trace->dump(sim_time);
    sim_time++;
  }
  m_trace->close();
  delete vtop;
  exit(EXIT_SUCCESS);
}