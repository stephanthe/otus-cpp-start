#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>

#include "high_score_table.h"


int high_score_table(const std::string& high_scores_filename, std::string user_name, int attempts, bool only_show)
  {
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
    std::cout << "\x1b[32m           High score table:           \x1b[0m\n"
              << "+-----------------------------+-----------+\n";
    while (std::getline(score_file_in, text_line)) {
      size_t n = text_line.find("\001");
      attempts_str = text_line.substr(n);
      text_line.resize(n);
      std::cout << "| " << text_line << "\x1b[31G| " << std::right
                << std::setw(10) << attempts_str << " |\n";
    }
    std::cout << "+-----------------------------+-----------+\n";
    score_file_in.close();
    return 0;
  }