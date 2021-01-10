// copyright 2020 typeperfest
#include <iostream>
#include <boost/filesystem.hpp>
#include "directory_parser.hpp"

#define DEBUG

namespace fs = boost::filesystem;

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
#ifndef DEBUG
  if (argc == 1) {
    std::cout << "you need to enter directory" << std::endl;
    return 1;
  } else if (argc > 2) {
    std::cout << "you need enter only one directory" << std::endl;
    return 2;
  } else {
    fs::path path(argv[1]);
    if (!fs::exists(path)) {
      std::cout << "no such file or directory" << std::endl;
      return 3;
    }
    directory_analysis(path, std::cout);
  }
#endif
#ifdef DEBUG
  fs::path debug_path("../misc");
  directory_analysis(debug_path, std::cout);
#endif
  return 0;
}
