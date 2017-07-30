#include "Socket.h"

namespace PAL
{
	namespace Object
	{
		namespace Unix
		{
			Socket::Socket(SocketType type, SocketFamily family):
				m_Type(type),
				m_Family(family)
			{

			}

			Socket::~Socket()
			{
				Close();
			}
		}
	}
}