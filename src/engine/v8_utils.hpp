#pragma once

#include <v8.h>
#include <iostream>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#include <boost/format.hpp >
#pragma clang diagnostic pop

namespace engine::utils {

static inline std::string to_string(v8::Isolate* isolate, const v8::Local<v8::Value> value){
    v8::String::Utf8Value utf8_string(isolate, value);
  return *utf8_string ? std::string(*utf8_string) : "string conversion failed";
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
  auto line = message->GetLineNumber(isolate->GetCurrentContext()).FromJust();
  auto log_str =
      boost::format("%1% [line %2%]") % to_string(isolate, message->Get()) % line;
  std::cerr << log_str.str() << std::endl;
}

}  // namespace engine::utils