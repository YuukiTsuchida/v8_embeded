#pragma once

#include <v8.h>
#include <list>
#include <memory>
#include <string_view>
#include "../object/console.hpp"
#include "bind/global_object_instance.hpp"
#include "bind/global_object_template.hpp"
#include "runner.hpp"

namespace engine {

class javascript {
 public:
  explicit javascript(v8::Isolate* isolate);
  void dispose(v8::Isolate* isolate);

  void run_code(v8::Isolate* isolate, std::string_view src);

 private:
  void bind_object(v8::Isolate* isolate);

  template <class Type, class... Args>
  auto make_object(v8::Isolate* isolate, Args&... args) {
    bind::global_object_template<Type> object_template(isolate);
    return std::make_shared<bind::global_object_instance<Type>>(
        isolate, object_template.create(isolate), args...);
  }

 private:
  v8::Global<v8::Context> global_context_;
  std::list<runner> runners_;

  std::shared_ptr<bind::global_object_instance<object::console>> console_;
};

}  // namespace engine