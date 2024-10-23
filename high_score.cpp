#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <vector>

#include "high_score.h"

namespace high_score {

int table(const std::string &high_scores_filename, std::string user_name,
          int attempts) {
  struct Users {
    std::string name;
    int attempts;
    bool operator==(const Users &t) { return name == t.name; }
    bool operator<(const Users &t) { return attempts < t.attempts; }
  };
  std::vector<Users> users;

  std::ifstream score_file_in(high_scores_filename);
  if (score_file_in.is_open()) {
    std::string text_line;
    std::string attempts_str;
    while (std::getline(score_file_in, text_line)) {
      bool find_user = false;
      size_t n = text_line.find("\001");
      int attempts = stoi(text_line.substr(n + 1));
      text_line.resize(n);
      users.push_back({text_line, attempts});
    }
  }
  score_file_in.close();

  if (attempts > 0) {
    bool find_user = false;
    for (auto &user : users) {
      if (user.name == user_name) {
        user.attempts = std::min(user.attempts, attempts);
        find_user = true;
        break;
      }
    }
    if (!find_user) {
      users.push_back({user_name, attempts});
    }
  }
  std::sort(begin(users), end(users));
  std::ofstream score_file_out(high_scores_filename, std::ios_base::out);
  if (!score_file_out.is_open()) {
    std::cerr << "Failed to open file " << high_scores_filename;
    score_file_out.close();
    return -1;
  }
  for (auto &user : users) {
    score_file_out << user.name << "\001" << user.attempts << std::endl;
  }
  score_file_out.close();

  std::cout << "\x1b[32m           High score table:           \x1b[0m\n"
            << "+-----------------------------+------------+\n";
  for (auto &user : users) {
    std::cout << "| " << user.name << "\x1b[31G| " << std::right
              << std::setw(10) << user.attempts << " |\n";
  }
  std::cout << "+-----------------------------+------------+\n";

  return 0;
}

} // namespace high_score