#ifndef CHAISCRIPT_STDLIB
#define CHAISCRIPT_STDLIB

#include <memory>

namespace chaiscript {
class Module;
}

std::shared_ptr<chaiscript::Module> create_chaiscript_stdlib();

#endif
