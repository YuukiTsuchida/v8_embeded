#pragma once

#include <v8.h>
#include <memory>
#include <string_view>
#include "../engine/bind/object_template.hpp"
#include "../object/test/test_object1.hpp"
#include "bind/object_instance.hpp"
#include "v8_utils.hpp"

namespace engine {

class runner {
 public:
  explicit runner(v8::Isolate* isolate)
      : context_(isolate, v8::Context::New(isolate, nullptr)) {}

  void run_code(v8::Isolate* isolate, v8::Local<v8::Context> context,
                std::string_view code);

  void execute(v8::Isolate* isolate, std::string_view code);

  template <class... Args>
  void execute(v8::Isolate* isolate, std::string_view code, Args... args) {
    auto context = context_.Get(isolate);
    v8::Context::Scope scope(context);

    bind_global_object(isolate, context, args...);
    bind_local_object(isolate, context);
    run_code(isolate, context, code);
  }

 private:
  template <class Arg>
  void bind_global_object(v8::Isolate* isolate, v8::Local<v8::Context> context,
                          Arg arg) {
    arg->bind(isolate, context);
  }

  template <class Head, class... Tail>
  void bind_global_object(v8::Isolate* isolate, v8::Local<v8::Context> context,
                          Head head, Tail... tail) {
    head->bind(isolate, context);
    bind(isolate, context, tail);
  }

  template <class Type>
  auto make_object(v8::Isolate* isolate) {
    bind::object_template<Type> object_template(isolate);
    return std::make_unique<bind::object_instance<Type>>(
        isolate, object_template.create(isolate));
  }

  template <class Type, class... Args>
  auto make_object(v8::Isolate* isolate, const Args&... args) {
    bind::object_template<Type> object_template(isolate);
    return std::make_unique<bind::object_instance<Type>>(
        isolate, object_template.create(isolate), args...);
  }

  void bind_local_object(v8::Isolate* isolate, v8::Local<v8::Context> context);

 private:
  v8::Global<v8::Context> context_;
  std::unique_ptr<bind::object_instance<object::test::test_object1>>
      test_object1;
};

}  // namespace engine