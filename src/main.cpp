#include <v8.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <string_view>
#include "engine/engine.hpp"

std::string load_file(std::string_view file_name) {
  std::stringstream file_string;
  std::ifstream stream;
  stream.open(file_name.data(), std::ios::in);
  std::string line("");
  while (std::getline(stream, line)) {
    file_string << line << "\n";
  }

  return file_string.str();
}

int main(int argc, char* argv[]) {
  std::cout << argv[0] << std::endl;
  engine::engine engine_instance;
  engine_instance.initialize(argv[0]);
  std::string code = load_file("resource/main.js");
  engine_instance.run_js_code(code);
  engine_instance.dispose();

#if WIN
  system("pause");
#endif
  return 0;
}