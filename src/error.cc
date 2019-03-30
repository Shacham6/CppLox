#include <utility>
#include <iostream>

#include <error.hh>

static bool hadErrors = false;

void Shach::Err::Error(int line, string message) {
  Report(line, "", std::move(message));
}

void Shach::Err::Report(int line, string where, string message) {
  std::cerr << "[line " << line << "] Error " << where << ": " << message << std::endl;
  hadErrors = true;
}

bool Shach::Err::HadErrors() {
  return hadErrors;
}

void Shach::Err::SetHadErrors(bool value) {
  hadErrors = value;
}
