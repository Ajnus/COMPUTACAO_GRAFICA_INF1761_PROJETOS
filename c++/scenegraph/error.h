#ifndef ERROR_H
#define ERROR_H

#include <string>

class Error {
public:
  static void Check (const std::string& msg);
};
#endif