#include "javascript.hpp"

namespace engine {

javascript::javascript(v8::Isolate* isolate)
    : global_context_(isolate, v8::Context::New(isolate, nullptr)) {
  bind_object(isolate);
}

void javascript::dispose(v8::Isolate* isolate) { global_context_.Reset(); }

void javascript::run_code(v8::Isolate* isolate, std::string_view src) {
  runner js_runner(isolate);
  js_runner.execute(isolate, src, console_);

  runners_.push_back(std::move(js_runner));
}

/** private method **/
void javascript::bind_object(v8::Isolate* isolate) {
  auto context = global_context_.Get(isolate);
  v8::Context::Scope context_scope(context);

  console_ = make_object<object::console>(isolate);
}

}  // namespace engine