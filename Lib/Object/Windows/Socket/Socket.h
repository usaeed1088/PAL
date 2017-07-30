#pragma once

#include "../../Objects/ISocket.h"
#include "../../Objects/SocketDefinitions.h"

namespace PAL
{
	namespace Object
	{
		namespace Windows
		{
			class Socket : public ISocket
			{
			private:
				SocketType m_Type;
				SocketFamily m_Family;

				std::uint64_t m_Descriptor;

			public:
				Socket(SocketType type, SocketFamily family);
				~Socket() override;

				bool Open() override;
				bool Close() override;

				// Server socket
				bool Bind(std::int32_t port) override;
				bool Listen() override;
				std::shared_ptr<ISocket> Accept() override;

				// Client socket
				bool Connect(const std::string server, std::int32_t port) override;

				// Configurations
				bool SetNonBlocking() override;

				// Data I/O
				bool Send(const std::vector<unsigned char>& data) override;
				bool SendTo(const std::string destination, std::int32_t port, const std::vector<unsigned char>& data) override;

				std::vector<unsigned char> Receive() override;
				std::vector<unsigned char> ReceiveFrom(const std::string source, std::int32_t port) override;
			};
		}
	}
}