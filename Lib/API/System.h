#pragma once

#include "APIs/ITrance.h"
#include "APIs/ITime.h"

namespace PAL
{
	namespace API
	{
		class System
		{
		private:
			static ITrancePtr s_TranceInstance;
			static ITimePtr s_TimeInstance;

		private:
			System();

		public:
			~System();

		public:
			static ITrancePtr Trance();
			static ITimePtr Time();
		};
	}
}