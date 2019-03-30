// STD
#include <fstream>
#include <iostream>

// Project-Level
#include <scanner.hh>
#include <lox.hh>
#include <error.hh>

string ReadLine();

void Shach::RunFile(string filepath) {
  std::ifstream infile(filepath);

  if (!infile) {
    std::cerr << "Well not good." << std::endl;
    return;
  }

  string buffer((std::istreambuf_iterator<char>(infile)),
                std::istreambuf_iterator<char>());

  Run(buffer);
}

void Shach::RunPrompt() {
  bool shouldContinue = true;
  while (shouldContinue) {
    std::cout << ">> ";
    auto line = ReadLine();
    if (line == "quit") {
      std::cout << "Bye-Bye!!" << std::endl;
      shouldContinue = false;
      continue;
    }
    Run(line);
    Shach::Err::SetHadErrors(false);
  }
}

string ReadLine() {
  string line;
  std::getline(std::cin, line);
  return line;
}

void Shach::Run(string source) {
  Scanner scanner(move(source));

  auto tokens = scanner.ScanTokens();

  for (const auto &token: tokens) {
    std::cout << token.ToString() << std::endl;
  }
}
