#pragma once

#include <v8.h>
#include <string_view>
#include "../v8_utils.hpp"

namespace engine::bind {

template <class TargetType>
class object_template_binder {
 private:
  using bind_func_type =
      void (TargetType::*)(const v8::FunctionCallbackInfo<v8::Value>&);

 public:
  explicit object_template_binder(v8::Local<v8::ObjectTemplate> object)
      : target_(object) {}

  void bind(v8::Isolate* isolate) { TargetType::bind_template(isolate, *this); }

  template <bind_func_type memfun>
  void bind_function(v8::Isolate* isolate, std::string_view property_name) {
    auto name = utils::to_v8_string(isolate, property_name);
    auto function = v8::FunctionTemplate::New(
        isolate, [](const v8::FunctionCallbackInfo<v8::Value>& args) {
          v8::HandleScope handle_scope(args.GetIsolate());
          auto holder = args.Holder()->GetInternalField(0);
          auto* instance = static_cast<TargetType*>(
              v8::Local<v8::External>::Cast(holder)->Value());
          (instance->*memfun)(args);
        });
    target_->Set(name, function);
  }

 private:
  v8::Local<v8::ObjectTemplate> target_;
};

}  // namespace engine::bind
