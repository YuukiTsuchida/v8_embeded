#pragma once

#include <v8.h>
#include <iostream>
#include <string_view>

namespace object {

class console {
 public:
  static constexpr std::string_view object_name = "console";

  explicit console() = default;

  template <class Binder>
  static void bind_template(v8::Isolate* isolate, Binder& binder) {
    binder.template bind_function<&console::log>(isolate, "log");
  }
  
  template <class ObjectInstance>
  void bind_instance(v8::Isolate* isolate, ObjectInstance& objectInstance){}

  void log(const v8::FunctionCallbackInfo<v8::Value>& info);
};

}  // namespace object