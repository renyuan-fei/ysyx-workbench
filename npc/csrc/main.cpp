#include <nvboard.h>
#include "../obj_dir/Vtop.h"

static TOP_NAME dut;

void nvboard_bind_all_pins(TOP_NAME* top);


int main(int argc, const char** argv) {

  // bindk all pins
  nvboard_bind_all_pins(&dut);
  nvboard_init();

  while (1)
  {
    int a = rand() & 1;
    int b = rand() & 1;
    dut.a = a;
    dut.b = b;
    dut.eval();
    printf("a = %d, b = %d, f = %d\n", a, b, dut.f);

    nvboard_update();
  }
  // nvboard_quit();
}