#pragma once

#include "../../APIs/ITrance.h"

namespace PAL
{
	namespace API
	{
		namespace Unix
		{
			class Trance : public ITrance
			{
			private:
				friend class Factory;
				Trance();

			public:
				~Trance() override;

				virtual bool Sleep(std::uint32_t milliseconds) override;
			};
		}
	}
}
