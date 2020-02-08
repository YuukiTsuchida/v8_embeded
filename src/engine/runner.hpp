#pragma once

#include <v8.h>
#include <string_view>

namespace engine {

class runner {
 public:
  explicit runner(v8::Isolate* isolate);
  void run(v8::Isolate* isolate, std::string_view code);

 private:
  v8::Global<v8::Context> context_;
};

}  // namespace engine