#include "Socket.h"

#include <Windows.h>
#include <WinSock.h>
#pragma comment(lib, "ws2_32.lib")

namespace PAL
{
	namespace Object
	{
		namespace Windows
		{
			static inline SOCKADDR_IN SocketAddressToSOCKADDR_IN(const std::string& addr, std::int32_t port, SocketFamily family)
			{
				SOCKADDR_IN sockAddr_in = {};
				int length_SOCKADDR_IN = sizeof(SOCKADDR_IN);
				sockAddr_in.sin_family = AF_INET;	//TODO: Should be deduced from 'family' (set the type of connection to TCP/IP)
				sockAddr_in.sin_addr.s_addr = inet_addr(addr.c_str());
				sockAddr_in.sin_port = htons(port);

				return sockAddr_in;
			}

			Socket::Socket(SocketType type, SocketFamily family):
				m_Type(type),
				m_Family(family),
				m_Descriptor(-1)
			{

			}

			Socket::~Socket()
			{
				Close();
			}

			bool Socket::Open()
			{
				WSADATA webservicesdata = {};				/* Declare WSAData */
				WORD winsockVersion = MAKEWORD(2, 0);		/* Winsock 2.0 */

				if (WSAStartup(winsockVersion, &webservicesdata) != 0)
				{
					return false;
				}

				int socketFamily = 0;
				int socketType = 0;

				switch (m_Family)
				{
				case SocketFamily::Internetwork:
					socketFamily = AF_INET;
					break;
				}

				switch (m_Type)
				{
				case SocketType::Stream:
					socketType = SOCK_STREAM;
					break;
				case SocketType::Datagram:
					socketType = SOCK_DGRAM;
					break;
				}

				std::int32_t protocol = 0;
				m_Descriptor = ::socket(socketFamily, socketType, protocol);
				
				return m_Descriptor > 0;
			}

			bool Socket::Close()
			{
				return ::closesocket(m_Descriptor) == 0;
			}

			// Server socket
			bool Socket::Bind(std::int32_t port)
			{
				SOCKADDR_IN sockAddr_in = SocketAddressToSOCKADDR_IN(std::string(), port, m_Family);
				sockAddr_in.sin_addr.S_un.S_addr = INADDR_ANY;	// Assign any network interface
				return ::bind(m_Descriptor, (sockaddr*)&sockAddr_in, sizeof(SOCKADDR)) == 0;
			}

			bool Socket::Listen()
			{
				return ::listen(m_Descriptor, SOMAXCONN) == 0;
			}

			std::shared_ptr<ISocket> Socket::Accept()
			{
				SOCKADDR_IN sockAddr_in = {};
				int length_SOCKADDR_IN = sizeof(SOCKADDR_IN);

				// ::accept function returns a new socket
				// Second argument is optional and will contain the address of the new socket
				std::int64_t descriptor = ::accept(m_Descriptor, (sockaddr*)&sockAddr_in, &length_SOCKADDR_IN);

				if (descriptor <= 0)
				{
					return nullptr;
				}

				std::shared_ptr<Socket> socket(new Socket(m_Type, m_Family));
				// TODO: See if anything else is needed to updated on this new Socket object?
				socket->m_Descriptor = descriptor;
				return std::static_pointer_cast<ISocket>(socket);
			}

			// Client socket
			bool Socket::Connect(const std::string server, std::int32_t port)
			{
				SOCKADDR_IN sockAddr_in = SocketAddressToSOCKADDR_IN(server, port, m_Family);
				return ::connect(m_Descriptor, (sockaddr*)&sockAddr_in, sizeof(SOCKADDR_IN)) == 0;
			}

			// Configurations
			bool Socket::SetNonBlocking()
			{
				u_long arg = 1;
				return ioctlsocket(m_Descriptor, FIONBIO, &arg) == 0;
		
				// Note: This is left commented for info only, in case a socket
				// needs to be configured as broadcast
				/*case SocketControl::Broadcast:
					cmd = SO_BROADCAST;
					return ::setsockopt(socket, SOL_SOCKET, SO_BROADCAST, (const char*)&so_broadcast, sizeof so_broadcast) == 0;*/
			}

			// Data I/O
			bool Socket::Send(const std::vector<unsigned char>& data)
			{
				std::vector<char> buffer(data.begin(), data.end());
				return ::send(m_Descriptor, &buffer[0], static_cast<int>(buffer.size()), 0) == data.size();
			}

			bool Socket::SendTo(const std::string destination, std::int32_t port, const std::vector<unsigned char>& data)
			{
				SOCKADDR_IN sockAddr_in = SocketAddressToSOCKADDR_IN(destination, port, m_Family);
				std::vector<char> buffer(data.begin(), data.end());
				return ::sendto(m_Descriptor, &buffer[0], static_cast<int>(buffer.size()), 0, (sockaddr*)&sockAddr_in, sizeof(SOCKADDR_IN)) == data.size();
			}

			std::vector<unsigned char> Socket::Receive()
			{
				const int ReceiveBufferLength = 1024 * 10; //10KB
				char buffer[ReceiveBufferLength] = {};
				int n = ::recv(m_Descriptor, buffer, ReceiveBufferLength, 0);
				if (n > 0)
				{
					return std::vector<unsigned char>(buffer, buffer + n);
				}
				else
				{
					return std::vector<unsigned char>();
				}
			}

			std::vector<unsigned char> Socket::ReceiveFrom(const std::string source, std::int32_t port)
			{
				SOCKADDR_IN sockAddr_in = SocketAddressToSOCKADDR_IN(source, port, m_Family);
				int sizeOf_SOCKADDR_IN = sizeof(SOCKADDR_IN);

				const int ReceiveBufferLength = 1024 * 10; //10KB
				char buffer[ReceiveBufferLength] = {};

				int n = ::recvfrom(m_Descriptor, buffer, ReceiveBufferLength, 0, (sockaddr*)&sockAddr_in, (int*)&sizeOf_SOCKADDR_IN);

				if (n > 0)
				{
					return std::vector<unsigned char>(buffer, buffer + n);
				}
				else if (n == SOCKET_ERROR)
				{
					int err = WSAGetLastError();
					return std::vector<unsigned char>();
				}

				return std::vector<unsigned char>();
			}
		}
	}
}