/* Copyright 2016 NeverSpring<never.spring@outlook.com> */
#ifndef RUSTY_OPTION_HPP_
#define RUSTY_OPTION_HPP_

#include <functional>

namespace rusty {

struct ThrowExceptionWithMsg {
public:
  ThrowExceptionWithMsg(char const *msg) : _msg(msg) {}
  // Noreturn
  void operator()(void) const;

  ThrowExceptionWithMsg() : _msg(nullptr) {}

private:
  char const *_msg;
};

template <typename T, typename P = rusty::ThrowExceptionWithMsg> struct Option {
private:
  typedef T value_t;
  typedef P panic_handler;

public:
  Option() : _has_init(false) {}

  explicit Option(value_t const &data) : _has_init(true), _data(data) {}

  Option(Option const &rhs) { *this = rhs; }

  ~Option() {}

  Option &operator=(Option const &rhs) {
    this->_has_init = rhs._has_init;
    if (_has_init) {
      this->_data = rhs._data;
    }
    return *this;
  }

  void Set(value_t const &data) {
    this->_has_init = true;
    this->_data = data;
  }

  value_t const &Unwrap() const { return this->Unwrap_or(panic_handler()); }

  value_t const &Unwrap_or(std::function<void(void)> fun) const {
    if (!this->_has_init) {
      fun();
    } else {
      return this->_data;
    }
  }

  template <typename R>
  Option<R> And_then(std::function<R(value_t const &)> fun) const {
    if (!this->_has_init) {
      return Option<R>();
    } else {
      return Option<R>(fun(this->_data));
    }
  }

  T const &Expect(char const *msg) const {
    return this->Unwrap_or(panic_handler(msg));
  }

private:
  bool _has_init;
  T _data;

}; // struct Option
} // namespace rusty

#endif // RUSTY_OPTION_HPP_
