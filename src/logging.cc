#include <filesystem>
#include <iostream>

#if (__cplusplus >= 202002L)

#include <string_view>
#include <source_location>

void log(const std::string_view message = "",
         const std::source_location location =
	 std::source_location::current())
{
  std::filesystem::path path{location.file_name()};
  std::clog << path.filename() << "("
	    << location.line() << ":"
	    << location.column() << ") `"
	    << location.function_name() << "`: "
	    << message << '\n';
}

#else

void log(const std::string p = __FILE__,
	 const int l = __LINE__,
	 const std::string f = __FUNCTION__,
	 const std::string message = "")
{
  std::filesystem::path path{p};
  std::clog << "file: "
	    << path.filename() << "("
	    << std::to_string(l) << ") "
    "["<< f << "] "
	    << message << '\n';
}

#endif
