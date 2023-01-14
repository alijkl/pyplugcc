
//enum class LogLevel {Error, Trace};
#include <string>

#if (__cplusplus >= 202002L)
#include <string_view>
#include <source_location>
void log(const std::string_view message = "",
         const std::source_location location =
	 std::source_location::current());
#define LOG_1(msg) { log(msg); }
#define LOG_0()    { log(); }
#define LOG_X(x,msg,FUNC, ...)  FUNC
#define LOG(...) LOG_X(,##__VA_ARGS__,	LOG_1(__VA_ARGS__), LOG_0(__VA_ARGS__));

#else

void log(const std::string p = __FILE__,
	 const int l = __LINE__,
	 const std::string  f = __FUNCTION__,
	 const std::string message = ""
	 );

#define LOG_1(msg) { log( __FILE__, __LINE__, __FUNCTION__, msg); }
#define LOG_0()    { log( __FILE__, __LINE__, __FUNCTION__); }
#define LOG_X(x,msg,FUNC, ...)  FUNC
#define LOG(...) LOG_X(,##__VA_ARGS__, LOG_1(__VA_ARGS__), LOG_0(__VA_ARGS__));
#endif

const std::string err_str = "\e[01;31merror:\e[0m";
