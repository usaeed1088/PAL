#include "Factory.h"

#include "../../Common/Config.h"

#include "../Windows/Socket/Socket.h"

#include "../Unix/Socket/Socket.h"

namespace PAL
{
	namespace Object
	{
		FactoryPtr Factory::s_Instance(nullptr);

		Factory::Factory()
		{

		}

		Factory::~Factory()
		{
			s_Instance = nullptr;
		}

		ISocketPtr Factory::CreateSocket(SocketType type, SocketFamily family)
		{
			ISocketPtr socket = nullptr;

#if defined(__BUILD_FOR_UNIX__)
				socket = ISocketPtr(new Unix::Socket(type, family));
#elif defined(__BUILD_FOR_WINDOWS__)
				socket = ISocketPtr(new Windows::Socket(type, family));
#endif
			return socket;
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
