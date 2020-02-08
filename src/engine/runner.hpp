#pragma once

#include <v8.h>
#include <string_view>
#include "v8_utils.hpp"

namespace engine {

class runner {
 public:
  explicit runner(v8::Isolate* isolate)
      : context_(isolate, v8::Context::New(isolate, nullptr)) {}

  template <class Arg>
  void bind(v8::Isolate* isolate, v8::Local<v8::Context> context, Arg arg) {
    arg->bind(isolate, context);
  }

  template <class Head, class... Tail>
  void bind(v8::Isolate* isolate, v8::Local<v8::Context> context, Head head,
            Tail... tail) {
    head->bind(isolate, context);
    bind(isolate, context, tail);
  }

  void run_code(v8::Isolate* isolate, v8::Local<v8::Context> context,
                std::string_view code) {
    auto source = utils::to_v8_string(isolate, code);

    // Compile the source code.
    v8::TryCatch try_catch(isolate);
    auto script = v8::Script::Compile(context, source);

    if (script.IsEmpty()) {
      utils::exception_log(isolate, try_catch);
      return;
    }

    // Run the script to get the result.
    auto result = script.ToLocalChecked()->Run(context).ToLocalChecked();
    if (result.IsEmpty()) {
      utils::exception_log(isolate, try_catch);
      return;
    }
  }

  void execute(v8::Isolate* isolate, std::string_view code) {
    auto context = context_.Get(isolate);
    v8::Context::Scope scope(context);

    run_code(isolate, context, code);
  }

  template <class... Args>
  void execute(v8::Isolate* isolate, std::string_view code, Args... args) {
    auto context = context_.Get(isolate);
    v8::Context::Scope scope(context);

    bind(isolate, context, args...);
    run_code(isolate, context, code);
  }

 private:
  v8::Global<v8::Context> context_;
};

}  // namespace engine