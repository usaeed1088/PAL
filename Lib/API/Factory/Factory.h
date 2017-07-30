#pragma once

#include "../APIs/ITrance.h"
#include "../APIs/ITime.h"

#include <memory>

namespace PAL
{
	namespace API
	{
		class Factory : std::enable_shared_from_this<Factory>
		{
		private:
			static std::shared_ptr<Factory> s_Instance;

		private:
			static ITrancePtr s_TranceInstance;
			static ITimePtr s_TimeInstance;

		private:
			Factory();

		public:
			~Factory();

		public:
			static ITrancePtr GetTranceInstance();
			static ITimePtr GetTimeInstance();

			static std::shared_ptr<Factory> Instance();
		};

		typedef std::shared_ptr<Factory> FactoryPtr;
	}
}