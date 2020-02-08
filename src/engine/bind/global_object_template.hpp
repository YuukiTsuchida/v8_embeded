#pragma once

#include <v8.h>
#include <cassert>
#include "object_template_binder.hpp"

namespace engine::bind {

template <class Type>
class global_object_template {
 public:
  explicit global_object_template() = default;
  explicit global_object_template(v8::Isolate* isolate) { initialize(isolate); }

  ~global_object_template() { object_template_.Reset(); }

  void initialize(v8::Isolate* isolate) {
    if (!object_template_.IsEmpty()) {
      assert(false);
    }

    auto object_template = v8::ObjectTemplate::New(isolate);
    object_template->SetInternalFieldCount(1);

    object_template_binder<Type> binder(object_template);
    binder.bind(isolate);

    auto global_template =
        v8::Global<v8::ObjectTemplate>(isolate, object_template);
    object_template_ = global_template.Pass();
  }

  v8::Local<v8::Object> create(v8::Isolate* isolate) const {
    return object_template_.Get(isolate)
        ->NewInstance(isolate->GetCurrentContext())
        .ToLocalChecked();
  }

 private:
  v8::Global<v8::ObjectTemplate> object_template_;
};

}  // namespace engine::bind