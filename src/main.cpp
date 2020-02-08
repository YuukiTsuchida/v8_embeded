#include <v8.h>
#include <iostream>
#include "engine/engine.hpp"

int main(int argc, char* argv[]) {
  std::cout << argv[0] << std::endl;
  engine::engine engine_instance;
  engine_instance.initialize(argv[0]);

  engine_instance.run_js_code("1 + 1");
  engine_instance.dispose();

#if WIN
  system("pause");
#endif
  return 0;
}