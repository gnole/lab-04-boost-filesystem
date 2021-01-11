#include <directory_parser.hpp>
#include <map>
#include <boost/regex.hpp>


std::ostream& directory_analysis(const boost::filesystem::path& path,
                                 std::ostream& out)
{
  namespace fs = boost::filesystem;
  std::map<std::pair<std::string, std::string>,
      std::pair<int, int64_t>> brokers_info;
  boost::regex filename_format("balance_[0-9]{8}_[0-9]{8}\\.txt$");
  for (const fs::directory_entry& p : fs::recursive_directory_iterator(path)) {
    if (fs::is_regular_file(p.path())) {
      if (boost::regex_match(p.path().filename().string(), filename_format)) {
        std::string parent_dir = p.path().parent_path().filename().string();
        out << parent_dir << ' ';
        out << p.path().filename().string() << std::endl;
        std::string broker_id =
            p.path().filename().string().substr(8, 8);
        int64_t current_date =
            stoi(p.path().filename().string().substr(17, 8));
        std::pair<std::string, std::string>
            trader_account(parent_dir, broker_id);
        if (brokers_info.find(trader_account) == brokers_info.end()) {
          brokers_info[trader_account] =
              std::pair<int, int64_t>(1, current_date);
        } else {
          brokers_info[trader_account].first++;
          if (brokers_info[trader_account].second < current_date) {
            brokers_info[trader_account].second = current_date;
          }
        }
      }
    }
  }
  out << "printing brokers_info" << std::endl;
   for (const auto& iterator : brokers_info) {
    out << "broker:" << iterator.first.first <<" account:"
        << iterator.first.second << " files:" << iterator.second.first
        << " lastdate:" << iterator.second.second << std::endl;
  }
  return out;
}
