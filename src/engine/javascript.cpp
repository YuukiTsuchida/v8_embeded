#include "javascript.hpp"

namespace engine {

javascript::javascript(v8::Isolate* isolate)
    : global_context_(isolate, v8::Context::New(isolate, nullptr)) {
  make_global_object(isolate);
}

void javascript::dispose(v8::Isolate* isolate) { global_context_.Reset(); }

void javascript::run_code(v8::Isolate* isolate, std::string_view src) {
  runner js_runner(isolate);
  js_runner.run(isolate, src);

  runners_.push_back(std::move(js_runner));
}

/** private method **/

void javascript::make_global_object(v8::Isolate* isolate) {}

}  // namespace engine