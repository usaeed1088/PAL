#pragma once

#include "../../Objects/ISocket.h"
#include "../../Objects/SocketDefinitions.h"

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

				std::uint64_t m_Descriptor;
			public:
				Socket(SocketType type, SocketFamily family);
				~Socket() override;

				virtual bool Open() override;
				virtual bool Close() override;

				// Server socket
				virtual bool Bind(std::int32_t port) override;
				virtual bool Listen() override;
				virtual std::shared_ptr<ISocket> Accept() override;

				// Client socket
				virtual bool Connect(const std::string server, std::int32_t port) override;

				// Configurations
				virtual bool SetNonBlocking() override;

				// Data I/O
				virtual bool Send(const std::vector<unsigned char>& data) override;
				virtual bool SendTo(const std::string destination, std::int32_t port, const std::vector<unsigned char>& data) override;

				virtual std::vector<unsigned char> Receive() override;
				virtual std::vector<unsigned char> ReceiveFrom(std::string& source, std::int32_t& port) override;
			};
		}
	}
}
