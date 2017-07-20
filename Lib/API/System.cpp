#include "System.h"

#include "../Common/Config.h"

#include "Unix/Trance/Trance.h"

#include "Windows/Trance/Trance.h"

namespace PAL
{
	namespace API
	{
		ITrancePtr System::s_TranceInstance(nullptr);

		System::System()
		{

		}

		System::~System()
		{
			s_TranceInstance = nullptr;
		}

		ITrancePtr System::Trance()
		{
			if (s_TranceInstance == nullptr)
			{
#if defined(__BUILD_FOR_UNIX__)
				s_TranceInstance = ITrancePtr(new Unix::Trance());
#elif defined(__BUILD_FOR_WINDOWS__)
				s_TranceInstance = ITrancePtr(new Windows::Trance());
#endif
			}

			return s_TranceInstance;
		}
	}
}