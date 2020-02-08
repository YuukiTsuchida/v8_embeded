#pragma once

#include <v8.h>
#include <list>
#include <string_view>
#include "runner.hpp"

namespace engine {

class javascript {
 public:
  explicit javascript(v8::Isolate* isolate);
  void dispose(v8::Isolate* isolate);

  void run_code(v8::Isolate* isolate, std::string_view src);

 private:
  void make_global_object(v8::Isolate* isolate);

 private:
  v8::Global<v8::Context> global_context_;
  std::list<runner> runners_;
};

}  // namespace engine