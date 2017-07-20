#include "Time.h"

#include <chrono>

namespace PAL
{
	namespace API
	{
		namespace Windows
		{
			Time::Time()
			{

			}

			Time::~Time()
			{

			}

			std::uint64_t Time::Milliseconds()
			{
				return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
			}
		}
	}
}