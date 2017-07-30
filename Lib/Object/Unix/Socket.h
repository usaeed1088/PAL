#pragma once

#include "../Objects/ISocket.h"
#include "../Objects/SocketDefinitions.h"

namespace PAL
{
	namespace Object
	{
		namespace Unix
		{
			class Socket : public ISocket
			{
			private:
				SocketType m_Type;
				SocketFamily m_Family;

			public:
				Socket(SocketType type, SocketFamily family);
				~Socket() override;
			};
		}
	}
}