#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>

#include "high_score_table.h"

int main(int argc, char *argv[]) {

  std::string arg;
  std::string user_name;
  int max_value = 100;
  int level;
  int user_number;
  int attempts = 0;
  const std::string high_scores_filename = "high_scores.txt";
  std::srand(std::time(nullptr));
  bool max_opt_present = false;
  bool level_opt_present = false;

  for (int i = 1; i < argc; ++i) {
    arg = argv[i];
    if (arg == "-max") {
      if (level_opt_present ==true){
        std::cout << "-max & -level can't be together\n";
        return 1;
      }
      max_opt_present = true;
      try {
        max_value = std::stoi(argv[++i]);
      } catch (const std::out_of_range &oofr) {
        std::cout << "value of -max is out of range\n";
        return 1;
      } catch (const std::invalid_argument &iarg) {
        std::cout << "invalid arg in -max parameter\n";
        return 1;
      }
    }
    if (arg == "-level") {
      if (max_opt_present ==true){
        std::cout << "-max & -level can't be together\n";
        return 1;
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
          return 1;
        }
      } catch (const std::out_of_range &oofr) {
        std::cout << "value of -level is out of range\n";
        return 1;
      } catch (const std::invalid_argument &iarg) {
        std::cout << "invalid arg in -level parameter\n";
        return 1;
      }
    }
  }
  if (max_value < 10) {
    std::cout << "-max must be >=10";
    return 1;
  }
  std::cout << "guess number 0.."<<max_value-1<<"\n";
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
