#include "engine.hpp"
#include <sstream>

namespace engine {

engine::engine() : isolate_(nullptr) {}
engine::~engine() {}

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
}

void engine::dispose() { isolate_->Dispose(); }

void engine::run_js_code(std::string_view src) {}

}  // namespace engine