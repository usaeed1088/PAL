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
			private:
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
