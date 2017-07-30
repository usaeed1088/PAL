#pragma once

#include <cstdint>
#include <memory>
#include <string>

namespace PAL
{
	namespace API
	{
		class ITime : std::enable_shared_from_this<ITime>
		{
		public:
			virtual ~ITime() {}

			virtual std::uint64_t Milliseconds() = 0;

			virtual std::string DateFormat() = 0;

			virtual std::string TimeFormat() = 0;

			virtual std::string HumanReadableTimestamp(std::string format, bool fractionalSeconds) = 0;
		};

		typedef std::shared_ptr<ITime> ITimePtr;
	}
}