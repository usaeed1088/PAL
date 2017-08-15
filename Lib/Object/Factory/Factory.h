#pragma once

#include "../Objects/ISocket.h"
#include "../Objects/SocketDefinitions.h"

#include <memory>

namespace PAL
{
	namespace Object
	{
		class Factory : public std::enable_shared_from_this<Factory>
		{
		private:
			static std::shared_ptr<Factory> s_Instance;
			Factory();

		public:
			~Factory();

			static ISocketPtr CreateSocket(SocketType type, SocketFamily family);

			static std::shared_ptr<Factory> Instance();
		};

		typedef std::shared_ptr<Factory> FactoryPtr;
	}
}
