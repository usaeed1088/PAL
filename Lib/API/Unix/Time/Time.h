#pragma once

#include "../../APIs/ITime.h"

namespace PAL
{
	namespace API
	{
		namespace Unix
		{
			class Time : public ITime
			{
				// NOTE: Constructor should and must be private and only
				// be accessible by Factory class. However, g++ complains
				// "error: ‘PAL::API::Unix::Time::Time()’ is private" because
				// it compiles Factory class after compiling this class and
				// hence, cannot associate friendship between both. MSVC is happy
				// with this constructor being private.
				// Also, this note should be pasted on every Unix API class until
				// this is resolved
				// TODO: Find a workaround
			//private:
			public:
				friend class Factory;
				Time();

			public:
				~Time() override;

				std::string DateFormat() override;

				std::string TimeFormat() override;

				std::string HumanReadableTimestamp(std::string format, bool fractionalSeconds) override;

				std::uint64_t Milliseconds() override;
			};
		}
	}
}
