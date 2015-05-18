#include "rstr.h"

namespace rstr {

  std::vector<std::string> split(std::string const & str, std::string const & pattern) {
    size_t found = str.find(pattern);
    if (found == std::string::npos) {
      return std::vector<std::string>({str});
    }
    else {
      std::string current_string = str;
      std::vector<std::string> splitted;
      while (found != std::string::npos) {
        splitted.push_back(current_string.substr(0, found));
        current_string = current_string.substr(found + 1);
        found = current_string.find(pattern);
        if (found == std::string::npos) {
          splitted.push_back(current_string);
        }
      }
      return splitted;
    }
  }

  std::string strip(std::string const & str) {
    std::string new_str = str;
    size_t found = new_str.find_first_not_of(' ');
    if (found != std::string::npos) {
      new_str = new_str.substr(found);
    }
    found = new_str.find_last_not_of(' ');
    if (found != std::string::npos) {
      new_str = new_str.substr(0, found + 1);
    }
    return new_str;
  }
  
  std::string lstrip(std::string const & str) {
    std::string new_str = str;
    size_t found = new_str.find_last_not_of(' ');
    if (found != std::string::npos) {
      new_str = new_str.substr(found);
    }
    return new_str;
  }

  std::string rstrip(std::string const & str) {
    std::string new_str = str;
    size_t found = new_str.find_first_not_of(' ');
    if (found != std::string::npos) {
      new_str = new_str.substr(found);
    }
    return new_str;
  }

  bool end_with(std::string const & str, std::string const & pattern) {
    return (pattern.compare(str.substr(str.size() - pattern.size())) == 0);
  }

  bool include(std::string const & str, std::string const & pattern) {
    return (str.find(pattern) != std::string::npos);
  }

  std::string reverse(std::string const & str) {
    std::string new_string = str;
    std::reverse(new_string.begin(), new_string.end());
    return new_string;
  }
  
  bool start_with(std::string const & str, std::string const & pattern) {
    return (pattern.compare(str.substr(0, pattern.size())) == 0);
  }

}
