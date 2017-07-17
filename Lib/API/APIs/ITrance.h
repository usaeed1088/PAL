#pragma once

#include <cstdint>
#include <memory>

namespace PAL
{
	namespace API
	{
		class ITrance : std::enable_shared_from_this<ITrance>
		{
		public:
			virtual ~ITrance() {}
			virtual bool Sleep(std::uint32_t milliseconds) = 0;
		};

		typedef std::shared_ptr<ITrance> ITrancePtr;
	}
}