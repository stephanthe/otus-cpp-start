#include <ctime>
#include <iostream>
#include <string>

#include "args.h"
#include "game.h"
#include "high_score_table.h"

int main(int argc, char** argv) {

  std::string user_name;
  int max_value;
  int attempts = 0;
  const std::string high_scores_filename = "high_scores.txt";
  std::srand(std::time(nullptr));

  max_value = args::get_max(argc, argv); //return max; 0 if -table option; -1 if error in options
  
  if (max_value == 0){
  return high_score_table(high_scores_filename, user_name, attempts);
  }
  if (max_value == -1){
    return -1;
  }
  std::cout << "guess number 0.." << max_value - 1 << "\n";
  const int random_value = std::rand() % max_value;

  std::cout << "Enter your name please: ";
  //  std::cin >> user_name;
  std::getline(std::cin, user_name);
  
  attempts = game::run(random_value);

  std::cout << "\n\n\x1b[4m" << user_name << " - You win in " << attempts
            << " attempts!\x1b[0m\n\n";

  return high_score_table(high_scores_filename, user_name, attempts);
}
