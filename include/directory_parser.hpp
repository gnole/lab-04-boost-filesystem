
#ifndef INCLUDE_DIRECTORY_PARSER_HPP_
#define INCLUDE_DIRECTORY_PARSER_HPP_

#include <iostream>
#include <boost/filesystem.hpp>

std::ostream& directory_analysis(const boost::filesystem::path& path,
                                 std::ostream& out);

#endif // INCLUDE_DIRECTORY_PARSER_HPP_
