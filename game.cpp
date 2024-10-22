#include <iostream>
#include <limits>

#include "game.h"

namespace game {

int run(int random_value) {
  int attempts = 0;
  int user_number = 0;

  do {
    ++attempts;
    std::cout << "Enter number: ";

    while (!(std::cin >> user_number)) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Invalid input. Please enter a positive integer: ";
    }

    if (user_number < random_value) {
      std::cout << user_number << " less than my number\n";
    }
    if (user_number > random_value) {
      std::cout << user_number << " greater than my number\n";
    }

  } while (user_number != random_value);

  return attempts;
}

} // namespace game