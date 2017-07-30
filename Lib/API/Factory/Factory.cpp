#include "Factory.h"

#include "../../Common/Config.h"

#include "../Unix/Trance/Trance.h"
#include "../Unix/Time/Time.h"

#include "../Windows/Trance/Trance.h"
#include "../Windows/Time/Time.h"

namespace PAL
{
	namespace API
	{
		FactoryPtr Factory::s_Instance(nullptr);

		ITrancePtr Factory::s_TranceInstance(nullptr);
		ITimePtr Factory::s_TimeInstance(nullptr);

		Factory::Factory()
		{

		}

		Factory::~Factory()
		{
			s_Instance = nullptr;
			s_TranceInstance = nullptr;
			s_TimeInstance = nullptr;
		}

		ITrancePtr Factory::GetTranceInstance()
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

		ITimePtr Factory::GetTimeInstance()
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

		FactoryPtr Factory::Instance()
		{
			if (s_Instance == nullptr)
			{
				s_Instance = FactoryPtr(new Factory());
			}

			return s_Instance;
		}
	}
}