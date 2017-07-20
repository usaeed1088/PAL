#include "PAL.h"

#include "API/System.h"

namespace PAL
{
	PALPtr PAL::s_PALInstance(nullptr);

	PAL::PAL()
	{

	}

	PAL::~PAL()
	{
		s_PALInstance = nullptr;
	}

	void PAL::Sleep(std::uint32_t milliseconds)
	{
		API::System::Trance()->Sleep(milliseconds);
	}

	std::uint64_t PAL::Milliseconds()
	{
		return API::System::Time()->Milliseconds();
	}

	std::shared_ptr<PAL> PAL::Instance()
	{
		if (s_PALInstance == nullptr)
		{
			s_PALInstance = PALPtr(new PAL());
		}

		return s_PALInstance;
	}
}