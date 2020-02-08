#pragma once

#include <libplatform/libplatform.h>
#include <v8.h>
#include <memory>
#include <string_view>
#include <vector>
#include "javascript.hpp"

namespace engine {

class engine {
 public:
  explicit engine();
  ~engine();
  void initialize(std::string_view execute_path);
  void dispose();

  void run_js_code(std::string_view src);

 private:
  std::vector<char> load_binary(std::string_view file_name);

 private:
  v8::Isolate* isolate_;
  std::unique_ptr<v8::Platform> platform_;
  v8::Isolate::CreateParams create_params_;
  std::unique_ptr<javascript> javascript_;
};

}  // namespace engine