#include "runner.hpp"
#include <iostream>
#include "v8_utils.hpp"

namespace engine {

runner::runner(v8::Isolate* isolate)
    : context_(isolate, v8::Context::New(isolate, nullptr)) {}

void runner::run(v8::Isolate* isolate, std::string_view code) {
  auto context = context_.Get(isolate);
  v8::Context::Scope scope(context);

  auto source = utils::to_v8_string(isolate, code);

  // Compile the source code.
  v8::TryCatch try_catch(isolate);
  auto script = v8::Script::Compile(context, source);

  if (script.IsEmpty()) {
    utils::exception_log(isolate, try_catch);
    return;
  }

  // Run the script to get the result.
  auto result = script.ToLocalChecked()->Run(context).ToLocalChecked();
  if (result.IsEmpty()) {
    utils::exception_log(isolate, try_catch);
    return;
  }

  if (result->IsNumber()) {
    auto value = v8::Local<v8::Uint32>::Cast(result)->Value();
    std::cout << value << std::endl;
  }
}

}  // namespace engine