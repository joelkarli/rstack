#ifndef _RSTR_H
#define _RSTR_H

#include <string>
#include <vector>
#include <algorithm>

namespace rstr {

  std::vector<std::string> split(std::string const & str, std::string const & pattern);
  std::string strip(std::string const & str);
  std::string lstrip(std::string const & str);
  std::string rstrip(std::string const & str);
  bool end_with(std::string const & str, std::string const & pattern);
  bool include(std::string const & str, std::string const & pattern);
  std::string reverse(std::string const & str);
  bool start_with(std::string const & str, std::string const & pattern);

}

#endif
