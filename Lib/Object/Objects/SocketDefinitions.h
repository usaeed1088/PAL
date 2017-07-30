#pragma once

#include <cstdint>

namespace PAL
{
	namespace Object
	{
		enum class SocketType : std::uint8_t
		{
			Unknown,
			Stream,
			Datagram,
		};

		enum class SocketFamily : std::uint8_t
		{
			Unknown,
			Internetwork,
		};
	}
}