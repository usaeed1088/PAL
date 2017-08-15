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


			bool Socket::Open()
			{
				return false;
			}

			bool Socket::Close()
			{
				return false;
			}

			// Server socket
			bool Socket::Bind(std::int32_t port)
			{
				return false;
			}

			bool Socket::Listen()
			{
				return false;
			}

			std::shared_ptr<ISocket> Socket::Accept()
			{
				return nullptr;
			}

			// Client socket
			bool Socket::Connect(const std::string server, std::int32_t port)
			{
				return false;
			}

			// Configurations
			bool Socket::SetNonBlocking()
			{
				return false;
			}

			// Data I/O
			bool Socket::Send(const std::vector<unsigned char>& data)
			{
				return false;
			}

			bool Socket::SendTo(const std::string destination, std::int32_t port, const std::vector<unsigned char>& data)
			{
				return false;
			}

			std::vector<unsigned char> Socket::Receive()
			{
				return std::vector<unsigned char>();
			}

			std::vector<unsigned char> Socket::ReceiveFrom(const std::string source, std::int32_t port)
			{
				return std::vector<unsigned char>();
			}
		}
	}
}
