#pragma once

#include <string>
#include <cstdint>
#include <memory>
#include <vector>

namespace PAL
{
	namespace Object
	{
		class ISocket : public std::enable_shared_from_this<ISocket>
		{
		public:
			virtual ~ISocket() {}

			virtual bool Open() = 0;
			virtual bool Close() = 0;

			// Server socket
			virtual bool Bind(std::int32_t port) = 0;
			virtual bool Listen() = 0;
			virtual std::shared_ptr<ISocket> Accept() = 0;

			// Client socket
			virtual bool Connect(const std::string server, std::int32_t port) = 0;

			// Configurations
			virtual bool SetNonBlocking() = 0;

			// Data I/O
			virtual bool Send(const std::vector<unsigned char>& data) = 0;
			virtual bool SendTo(const std::string destination, std::int32_t port, const std::vector<unsigned char>& data) = 0;

			virtual std::vector<unsigned char> Receive() = 0;
			virtual std::vector<unsigned char> ReceiveFrom(std::string& source, std::int32_t& port) = 0;
		};

		typedef std::shared_ptr<ISocket> ISocketPtr;
	}
}
