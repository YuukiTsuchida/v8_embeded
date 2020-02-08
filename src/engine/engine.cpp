#include "engine.hpp"
#include <sstream>

namespace engine {

engine::engine() : isolate_(nullptr) {}
engine::~engine() {
  v8::V8::Dispose();
  v8::V8::ShutdownPlatform();
}

void engine::initialize(std::string_view execute_path) {
  v8::V8::InitializeICUDefaultLocation(execute_path.data());
  v8::V8::InitializeExternalStartupData(execute_path.data());
  platform_ = v8::platform::NewDefaultPlatform();
  v8::platform::NewDefaultPlatform();
  v8::V8::InitializePlatform(platform_.get());
  v8::V8::Initialize();
  create_params_.array_buffer_allocator =
      v8::ArrayBuffer::Allocator::NewDefaultAllocator();

  isolate_ = v8::Isolate::New(create_params_);
  v8::Isolate::Scope scope(isolate_);
  v8::HandleScope handle_scope(isolate_);

  javascript_ = std::make_unique<javascript>(isolate_);
}

void engine::dispose() {
  {
    v8::Isolate::Scope isolate_scope(isolate_);
    v8::HandleScope handle_scope(isolate_);
    javascript_->dispose(isolate_);
    javascript_.reset(nullptr);
  }
  isolate_->Dispose();
}

void engine::run_js_code(std::string_view src) {
  v8::Isolate::Scope scope(isolate_);
  v8::HandleScope handle_scope(isolate_);
  javascript_->run_code(isolate_, src);
}

}  // namespace engine