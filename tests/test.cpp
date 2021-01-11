// Copyright 2018 Your Name <your_email>

#include <gtest/gtest.h>
#include "directory_parser.hpp"
#include <boost/filesystem.hpp>

TEST(Example, EmptyTest) {
  namespace fs = boost::filesystem;
  // setup testing directory
    fs::create_directory("test_directory/");
    fs::create_directory("test_directory/corp1/");
    fs::create_directory("test_directory/corp2/");
// ____
    std::vector<std::ofstream> files;
    files.emplace_back(std::ofstream(
        "/test_directory/corp2/balance_00000001_20010101.txt"));  // 1
    files.emplace_back(std::ofstream(
        "test_directory/corp2/balance_00000004_20010104.txt"));  // 2
    files.emplace_back(std::ofstream(
        "test_directory/corp2/balance_00000001_20010102.txt"));  // 3
    files.emplace_back(std::ofstream(
        "test_directory/corp2/balance_00000001_20010104.txt"));  // 4
    files.emplace_back(std::ofstream(
        "test_directory/corp2/balance_00000004_20010101.txt"));  // 5
    files.emplace_back(std::ofstream(
        "test_directory/corp2/balance_00000006_20020103.txt"));  // 6
    files.emplace_back(std::ofstream(
        "test_directory/corp2/balance_00000004_20010103.txt"));  // 7
    files.emplace_back(std::ofstream(
        "test_directory/corp2/balance_00000006_20020102.txt"));  // 8
    files.emplace_back(std::ofstream(
        "test_directory/corp2/balance_00000006_20020105.txt"));  // 9
    files.emplace_back(std::ofstream(
        "test_directory/corp2/balance_00000006_20020104.txt"));  // 10
    files.emplace_back(std::ofstream(
        "test_directory/corp2/balance_00000004_20010102.txt"));  // 11
// _____
    files.emplace_back(std::ofstream(
        "test_directory/corp1/balance_00000002_20000101.txt"));  // 12
    files.emplace_back(std::ofstream(
        "test_directory/corp1/balance_00000001_20000103.txt"));  // 13
    files.emplace_back(std::ofstream(
        "test_directory/corp1/balance_00000001_20010101.txt"));  // 14
    files.emplace_back(std::ofstream(
        "test_directory/corp1/balance_00000001_20000102.txt"));  // 15
    files.emplace_back(std::ofstream(
        "test_directory/corp1/balance_00000001_20010103.txt"));  // 16
    files.emplace_back(std::ofstream(
        "test_directory/corp1/balance_00000001_20000101.txt"));  // 17
    files.emplace_back(std::ofstream(
        "test_directory/corp1/balance_00000002_20000102.txt"));  // 18
    files.emplace_back(std::ofstream(
        "test_directory/corp1/balance_00000003_20000101.txt"));  // 19
  std::stringstream out_stream;
  directory_analysis(fs::path("test_directory"), out_stream);
  std::cout << out_stream.str() << std::endl;
  std::stringstream expected_stream;
  expected_stream <<
  "corp1 balance_00000001_20000101.txt\n" <<
  "corp1 balance_00000001_20010101.txt\n" <<
  "corp1 balance_00000002_20000102.txt\n" <<
  "corp1 balance_00000002_20000101.txt\n" <<
  "corp1 balance_00000001_20010103.txt\n" <<
  "corp1 balance_00000001_20000103.txt\n" <<
  "corp1 balance_00000001_20000102.txt\n" <<
  "corp1 balance_00000003_20000101.txt\n" <<
  "corp2 balance_00000006_20020102.txt\n" <<
  "corp2 balance_00000001_20010102.txt\n" <<
  "corp2 balance_00000004_20010102.txt\n" <<
  "corp2 balance_00000006_20020105.txt\n" <<
  "corp2 balance_00000006_20020104.txt\n" <<
  "corp2 balance_00000001_20010104.txt\n" <<
  "corp2 balance_00000004_20010103.txt\n" <<
  "corp2 balance_00000006_20020103.txt\n" <<
  "corp2 balance_00000004_20010101.txt\n" <<
  "corp2 balance_00000004_20010104.txt\n" <<
      "printing brokers_info\n" <<
      "broker:corp1 account:00000001 files:5 lastdate:20010103\n" <<
      "broker:corp1 account:00000002 files:2 lastdate:20000102\n" <<
      "broker:corp1 account:00000003 files:1 lastdate:20000101\n" <<
      "broker:corp2 account:00000001 files:2 lastdate:20010104\n" <<
      "broker:corp2 account:00000004 files:4 lastdate:20010104\n" <<
      "broker:corp2 account:00000006 files:4 lastdate:20020105\n";
  EXPECT_TRUE(expected_stream.str() == out_stream.str());
}
