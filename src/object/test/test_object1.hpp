#pragma once

#include <v8.h>
#include <string_view>

namespace object::test {

class test_object1 {
 public:
  static constexpr std::string_view object_name = "test_object1";

  explicit test_object1(int value) : value_(value) {}

  template<class Binder>
  static void bind_template(v8::Isolate* isolate, Binder& binder){
      binder.template bind_function<&test_object1::func>(isolate, "func");
  }

  template <class ObjectInstance>
  void bind_instance(v8::Isolate* isolate, ObjectInstance& objectInstance){}

  void func(const v8::FunctionCallbackInfo<v8::Value>& info){
      info.GetReturnValue().Set(value_);
  };

 private:
  int value_;
};

}  // namespace object::test