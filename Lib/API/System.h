#pragma once

#include "APIs/ITrance.h"

namespace PAL
{
	namespace API
	{
		class System
		{
		private:
			static ITrancePtr s_TranceInstance;

		private:
			System();

		public:
			~System();

		public:
			static ITrancePtr Trance();
		};
	}
}