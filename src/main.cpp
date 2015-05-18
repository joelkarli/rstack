#include <iostream>
#include <fstream>
#include <stack>
#include <string>

#include "environment.h"

int main(int argc, char ** argv)  {
  if (argc > 1) {
    auto environment = Environment();
    environment.load(std::string(argv[1]));
  }
  return 0;
}
