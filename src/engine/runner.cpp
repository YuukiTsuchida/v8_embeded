#include "runner.hpp"

namespace engine {

void runner::run_code(v8::Isolate* isolate, v8::Local<v8::Context> context,
                      std::string_view code) {
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
}

void runner::execute(v8::Isolate* isolate, std::string_view code) {
  auto context = context_.Get(isolate);
  v8::Context::Scope scope(context);

  bind_local_object(isolate, context);
  run_code(isolate, context, code);
}

void runner::bind_local_object(v8::Isolate* isolate,
                               v8::Local<v8::Context> context) {
  test_object1 = make_object<object::test::test_object1>(isolate, 1);
  test_object1->bind(isolate, context);
}

}  // namespace engine