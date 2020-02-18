#pragma once

#include <v8.h>
#include <cassert>
#include "object_template_binder.hpp"

namespace engine::bind {

template <class Type>
class object_template {
 public:
  explicit object_template() = default;
  explicit object_template(v8::Isolate* isolate) { initialize(isolate); }

  void initialize(v8::Isolate* isolate) {
    if (!object_template_.IsEmpty()) {
      assert(false);
    }

    object_template_ = v8::ObjectTemplate::New(isolate);
    object_template_->SetInternalFieldCount(1);

    object_template_binder<Type> binder(object_template_);
    binder.bind(isolate);
  }

  v8::Local<v8::Object> create(v8::Isolate* isolate) const {
    return object_template_->NewInstance(isolate->GetCurrentContext()).ToLocalChecked();
  }

 private:
  v8::Local<v8::ObjectTemplate> object_template_;
};

}  // namespace engine::bind