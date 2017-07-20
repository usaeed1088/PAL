#include "System.h"

#include "../Common/Config.h"

#include "Unix/Trance/Trance.h"
#include "Unix/Time/Time.h"

#include "Windows/Trance/Trance.h"
#include "Windows/Time/Time.h"

namespace PAL
{
	namespace API
	{
		ITrancePtr System::s_TranceInstance(nullptr);
		ITimePtr System::s_TimeInstance(nullptr);

		System::System()
		{

		}

		System::~System()
		{
			s_TranceInstance = nullptr;
			s_TimeInstance = nullptr;
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

		ITimePtr System::Time()
		{
			if (s_TimeInstance == nullptr)
			{
#if defined(__BUILD_FOR_UNIX__)
				s_TimeInstance = ITimePtr(new Unix::Time());
#elif defined(__BUILD_FOR_WINDOWS__)
				s_TimeInstance = ITimePtr(new Windows::Time());
#endif
			}
			return s_TimeInstance;
		}
	}
}