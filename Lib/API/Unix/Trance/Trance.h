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
				// NOTE: Constructor should and must be private and only
				// be accessible by Factory class. However, g++ complains
				// "error: ‘PAL::API::Unix::Time::Time()’ is private" because
				// it compiles Factory class after compiling this class and
				// hence, cannot associate friendship between both. MSVC is happy
				// with this constructor being private.
				// Also, this note should be pasted on every Unix API class until
				// this is resolved
				// TODO: Find a workaround
			//private:
			public:
				friend class Factory;
				Trance();

			public:
				~Trance() override;

				virtual bool Sleep(std::uint32_t milliseconds) override;
			};
		}
	}
}
