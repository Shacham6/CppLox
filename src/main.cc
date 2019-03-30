#include <iostream>
#include <lox.hh>

using Shach::RunFile;
using Shach::RunPrompt;

int main(int argc, char **argv) {
  if (argc > 2) {
    std::cout << "Usage: lox [script]" << std::endl;
    return 64;
  } else if (argc == 2) {
    RunFile(argv[1]);
  } else {
    RunPrompt();
  }

  return 0;
}