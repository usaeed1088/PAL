#pragma once

#include "../../APIs/ITime.h"

namespace PAL
{
	namespace API
	{
		namespace Windows
		{
			class Time : public ITime
			{
			private:
				friend class System;
				Time();

			public:
				~Time() override;

				std::uint64_t Milliseconds() override;
			};
		}
	}
}