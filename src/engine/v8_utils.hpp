#pragma once

#include <v8.h>
#include <iostream>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#include <boost/format.hpp >
#pragma clang diagnostic pop

namespace engine::utils {

static inline std::string to_string(const v8::String::Utf8Value& value) {
  return *value ? std::string(*value) : "string conversion failed";
}

static inline v8::Local<v8::String> to_v8_string(v8::Isolate* isolate,
                                                 std::string_view string) {
  return v8::String::NewFromUtf8(isolate, string.data(),
                                 v8::NewStringType::kNormal)
      .ToLocalChecked();
}

static inline void exception_log(v8::Isolate* isolate,
                                 const v8::TryCatch& try_catch) {
  auto message = try_catch.Message();
  v8::String::Utf8Value exception_str(isolate, message->Get());
  auto line = message->GetLineNumber(isolate->GetCurrentContext()).FromJust();
  auto log_str =
      boost::format("%1% [line %2%]") % to_string(exception_str) % line;
  std::cerr << log_str.str() << std::endl;
}

}  // namespace engine::utils