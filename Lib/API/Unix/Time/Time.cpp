#include "Time.h"

#include <chrono>
#include <sstream>
#include <ctime>
#include <iomanip>

namespace PAL
{
	namespace API
	{
		namespace Unix
		{
			Time::Time()
			{

			}

			Time::~Time()
			{

			}

			std::string Time::DateFormat()
			{
				return std::string("%d-%m-%Y"); // DD-MM-YYYY
			}

			std::string Time::TimeFormat()
			{
				return std::string("%H:%M:%S");	// HH:MM:SS
			}

			std::string Time::HumanReadableTimestamp(std::string format, bool fractionalSeconds)
			{
				std::uint64_t ms = Milliseconds();

				std::time_t t = ms/1000;
				std::tm tm = *std::localtime(&t);

				std::stringstream ss;

				ss << std::put_time(&tm, format.c_str());

				if (fractionalSeconds)
				{
					std::size_t fractional_seconds = ms % 1000;
					ss << "." << std::dec << std::setw(3) << std::setfill('0') << fractional_seconds;
				}

				return ss.str();
			}

			std::uint64_t Time::Milliseconds()
			{
				return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
			}
		}
	}
}