#include "Trance.h"

#include <Windows.h>

namespace PAL
{
	namespace API
	{
		namespace Windows
		{
			Trance::Trance()
			{

			}

			Trance::~Trance()
			{

			}

			bool Trance::Sleep(std::uint32_t milliseconds)
			{
				::Sleep(milliseconds);
				return true;
			}
		}
	}
}