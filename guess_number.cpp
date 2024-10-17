#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>

#include "high_score_table.h"


int main() {

  std::string user_name;
  int max_value = 100;
  int user_number;
  int attempts = 0;
  const std::string high_scores_filename = "high_scores.txt";
  std::srand(std::time(nullptr));
  const int random_value = std::rand() % max_value;

  std::cout << "Enter your name please: ";
  //  std::cin >> user_name;
  std::getline(std::cin, user_name);
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

  std::cout << "\n\n\x1b[4m" << user_name << " - You win in " << attempts
            << " attempts!\x1b[0m\n\n";

  return high_score_table(high_scores_filename, user_name, attempts, false);
}
