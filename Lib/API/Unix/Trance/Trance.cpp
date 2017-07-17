#include "Trance.h"

#include <unistd.h>

namespace PAL
{
	namespace API
	{
		namespace Unix
		{
			Trance::Trance()
			{

			}

			Trance::~Trance()
			{

			}

			bool Trance::Sleep(std::uint32_t milliseconds)
			{
				return usleep(milliseconds * 1000);
			}
		}
	}
}