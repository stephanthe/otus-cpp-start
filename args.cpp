#include "args.h"
#include <iostream>
#include <string>

namespace args {

int get_max(int argc, char **argv) {
  std::string arg;
  int max_value = 100;
  int level;
  bool max_opt_present = false;
  bool level_opt_present = false;

  for (int i = 1; i < argc; ++i) {
    arg = argv[i];
    if (arg == "-table") {
      return 0;
    }
    if (arg == "-max") {
      if (level_opt_present == true) {
        std::cout << "-max & -level can't be together\n";
        return -1;
      }
      max_opt_present = true;
      try {
        max_value = std::stoi(argv[++i]);
      } catch (const std::out_of_range &oofr) {
        std::cout << "value of -max is out of range\n";
        return -1;
      } catch (const std::invalid_argument &iarg) {
        std::cout << "invalid arg in -max parameter\n";
        return -1;
      }
    }
    if (arg == "-level") {
      if (max_opt_present == true) {
        std::cout << "-max & -level can't be together\n";
        return -1;
      }
      level_opt_present = true;
      try {
        level = std::stoi(argv[++i]);
        switch (level) {
        case 1:
          max_value = 10;
          break;
        case 2:
          max_value = 50;
          break;
        case 3:
          max_value = 100;
          break;
        default:
          std::cout << "value of -level must be in range 1..3\n";
          return -1;
        }
      } catch (const std::out_of_range &oofr) {
        std::cout << "value of -level is out of range\n";
        return -1;
      } catch (const std::invalid_argument &iarg) {
        std::cout << "invalid arg in -level parameter\n";
        return -1;
      }
    }
  }
  if (max_value < 10) {
    std::cout << "-max must be >=10\n";
    return -1;
  }
  return max_value;
}
} // namespace args
