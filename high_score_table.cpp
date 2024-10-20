#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <vector>

#include "high_score_table.h"

int high_score_table(const std::string &high_scores_filename,
                     std::string user_name, int attempts, bool only_show) {
  struct Users {
    std::string name;
    int count;
    bool operator==(const Users &t) { return name == t.name; }
  };
  std::vector<Users> users;

  std::ofstream score_file_out(high_scores_filename, std::ios_base::app);
  if (!score_file_out.is_open()) {
    std::cerr << "Failed to open file " << high_scores_filename;
    score_file_out.close();
    return -1;
  }
  score_file_out << user_name << "\001" << attempts << std::endl;
  score_file_out.close();

  std::ifstream score_file_in(high_scores_filename);
  if (!score_file_in.is_open()) {
    std::cerr << "Failed to open file " << high_scores_filename;
    score_file_in.close();
    return -1;
  }
  std::string text_line;
  std::string attempts_str;
  while (std::getline(score_file_in, text_line)) {
    bool find_user = false;
    size_t n = text_line.find("\001");
    int attempts = stoi(text_line.substr(n + 1));
    text_line.resize(n);
    for (auto &user : users) {
      if (user.name == text_line) {
        user.count = std::min(user.count, attempts);
        find_user = true;
      }
    }
    if (!find_user) {
      users.push_back({text_line, attempts});
    }
  }
  std::cout << "\x1b[32m           High score table:           \x1b[0m\n"
            << "+-----------------------------+-----------+\n";
  for (auto &user : users) {
    std::cout << "| " << user.name << "\x1b[31G| " << std::right
              << std::setw(10) << user.count << " |\n";
  }
  std::cout << "+-----------------------------+-----------+\n";
  score_file_in.close();
  return 0;
}