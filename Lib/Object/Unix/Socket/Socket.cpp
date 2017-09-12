#include "Socket.h"

#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <fcntl.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <fcntl.h>

namespace PAL
{
	namespace Object
	{
		namespace Unix
		{
			static inline sockaddr_in SocketAddressToSockaddr_in(const std::string& addr, std::int32_t port, SocketFamily family)
			{
				sockaddr_in sockAddr_in = {};
				sockAddr_in.sin_family = AF_INET;	//TODO: Should be deduced from 'family' (set the type of connection to TCP/IP)
				sockAddr_in.sin_addr.s_addr = inet_addr(addr.c_str());
				sockAddr_in.sin_port = htons(port);

				return sockAddr_in;
			}

			static inline void Sockaddr_inToSocketAddress(const sockaddr_in& sockAddr, std::string& addr, std::int32_t& port)
			{
				port = ntohs(sockAddr.sin_port);
				addr = inet_ntoa(sockAddr.sin_addr);
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
				int socketFamily = 0;
				int socketType = 0;

				switch (m_Family)
				{
				case SocketFamily::Internetwork:
					socketFamily = AF_INET;
					break;
				case SocketFamily::Unknown:
				default:
					return false;
				}

				switch (m_Type)
				{
				case SocketType::Stream:
					socketType = SOCK_STREAM;
					break;
				case SocketType::Datagram:
					socketType = SOCK_DGRAM;
					break;
				case SocketType::Unknown:
				default:
					return false;
				}

				std::int32_t protocol = 0;
				m_Descriptor = ::socket(socketFamily, socketType, protocol);

				return m_Descriptor > 0;
			}

			bool Socket::Close()
			{
				return ::close(m_Descriptor) == 0;
			}

			// Server socket
			bool Socket::Bind(std::int32_t port)
			{
				sockaddr_in sockAddr_in = SocketAddressToSockaddr_in(std::string(), port, m_Family);
				sockAddr_in.sin_addr.s_addr = INADDR_ANY;	// Assign any network interface
				return ::bind(m_Descriptor, (sockaddr*)&sockAddr_in, sizeof(sockaddr_in)) == 0;
			}

			bool Socket::Listen()
			{
				return ::listen(m_Descriptor, SOMAXCONN) == 0;
			}

			std::shared_ptr<ISocket> Socket::Accept()
			{
				sockaddr_in sockAddr_in = {};
				unsigned int length_SOCKADDR_IN = sizeof(sockaddr_in);

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
				socket->SetNonBlocking();
				return std::static_pointer_cast<ISocket>(socket);
			}

			// Client socket
			bool Socket::Connect(const std::string server, std::int32_t port)
			{
				sockaddr_in sockAddr_in = SocketAddressToSockaddr_in(server, port, m_Family);
				return ::connect(m_Descriptor, (sockaddr*)&sockAddr_in, sizeof(sockaddr_in)) == 0;
			}

			// Configurations
			bool Socket::SetNonBlocking()
			{
				int flags = ::fcntl(m_Descriptor, F_GETFL, 0);
				return ::fcntl(m_Descriptor, F_SETFL, flags | O_NONBLOCK) == 0;
			}

			// Data I/O
			bool Socket::Send(const std::vector<unsigned char>& data)
			{
				std::vector<char> buffer(data.begin(), data.end());
				return ::send(m_Descriptor, &buffer[0], buffer.size(), 0) == (int)data.size();
			}

			bool Socket::SendTo(const std::string destination, std::int32_t port, const std::vector<unsigned char>& data)
			{
				sockaddr_in sockAddr_in = SocketAddressToSockaddr_in(destination, port, m_Family);
				std::vector<char> buffer(data.begin(), data.end());
				return ::sendto(m_Descriptor, &buffer[0], static_cast<int>(buffer.size()), 0, (sockaddr*)&sockAddr_in, sizeof(sockaddr_in)) == (int)data.size();
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

			std::vector<unsigned char> Socket::ReceiveFrom(std::string& source, std::int32_t& port)
			{
				sockaddr_in sockAddr_in = {};
				unsigned int sizeOf_SOCKADDR_IN = sizeof(sockaddr_in);

				const int ReceiveBufferLength = 1024 * 10; //10KB
				char buffer[ReceiveBufferLength] = {};

				int n = ::recvfrom(m_Descriptor, buffer, ReceiveBufferLength, 0, (sockaddr*)&sockAddr_in, &sizeOf_SOCKADDR_IN);

				if (n > 0)
				{
					Sockaddr_inToSocketAddress(sockAddr_in, source, port);
					return std::vector<unsigned char>(buffer, buffer + n);
				}

				return std::vector<unsigned char>();
			}
		}
	}
}
