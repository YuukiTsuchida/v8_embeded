#pragma once

#include <v8.h>
#include <type_traits>
#include "../v8_utils.hpp"
#include "global_object_instance.hpp"

namespace engine::bind {

template <class Type>
class object_instance {
 public:
  template <class... Args>
  explicit object_instance(v8::Isolate* isolate, v8::Local<v8::Object> object,
                           const Args&... args)
      : object_(object), instance_(args...) {
    object->SetInternalField(0, v8::External::New(isolate, &instance_));
  }

  template <class Context,
            std::enable_if_t<std::is_same_v<Context, v8::Local<v8::Context>>,
                             std::nullptr_t> = nullptr>
  void bind(v8::Isolate* isolate, Context context) {
    instance_.bind_instance(isolate, *this);
    context->Global()->Set(utils::to_v8_string(isolate, Type::object_name),
                           object_);
  }

  template <class ValueType>
  void bind(v8::Isolate* isolate, global_object_instance<ValueType>& parent) {
    instance_.bind_instance(isolate, *this);
    parent.object_->Set(utils::to_v8_string(isolate, Type::object_name),
                        object_);
  }

 private:
  v8::Local<v8::Object> object_;
  Type instance_;
};

}  // namespace engine::bind