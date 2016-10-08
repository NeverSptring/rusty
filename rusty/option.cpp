/* Copyright 2016 NeverSpring<never.spring@outlook.com> */
#include "rusty/option.hpp"

#include <iostream>

namespace rusty {

void ThrowExceptionWithMsg::operator()(void) const {
  if (_msg) {
    std::cerr << _msg << std::endl;
  }
  throw;
}

typedef Option<double> OptionDouble;

#ifdef RUSTY_TEST
extern OptionDouble bar(double x) {
  if (x > 0) {
    return OptionDouble(x);
  } else {
    return OptionDouble();
  }
}
#endif
} // namespace rusty
