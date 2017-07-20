#pragma once

#include <cstdint>
#include <memory>

namespace PAL
{
	namespace API
	{
		class ITime : std::enable_shared_from_this<ITime>
		{
		public:
			virtual ~ITime() {}

			virtual std::uint64_t Milliseconds() = 0;
		};

		typedef std::shared_ptr<ITime> ITimePtr;
	}
}