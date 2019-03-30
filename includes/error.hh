#pragma once

#include <types.hh>

namespace Shach::Err {
  bool HadErrors();

  void SetHadErrors(bool value);

  void Error(int line, string message);

  void Report(int line, string where, string message);
}
