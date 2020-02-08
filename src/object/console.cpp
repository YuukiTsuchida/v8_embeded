#include "console.hpp"
#include <iostream>
#include "../engine/v8_utils.hpp"

#if STACK_TRACE
#include <boost/stacktrace.hpp>
#endif

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#include <boost/format.hpp>
#pragma clang diagnostic pop


namespace object {

void console::log(const v8::FunctionCallbackInfo<v8::Value>& info) {
  auto str = engine::utils::to_string(info.GetIsolate(), info[0]);

#ifdef STACK_TRACE
  auto log = boost::format("[log]\t%1%\n\n%2%") % str %
             boost::stacktrace::stacktrace();
#else
  auto log = boost::format("[log]\t%1%") % str;
#endif

  std::cout << log << std::endl;
}

}  // namespace object