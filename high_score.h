#pragma once

#include <string>

namespace high_score {

int table(const std::string &high_scores_filename, std::string user_name,
          int attempts);

} // namespace high_score