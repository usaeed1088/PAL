#pragma once

#include <cstdint>
#include <memory>

namespace PAL
{
	class PAL
	{
	private:
		static std::shared_ptr<PAL> s_PALInstance;

	protected:
		PAL();

	public:
		~PAL();

		virtual void Sleep(std::uint32_t milliseconds);
		virtual std::uint64_t Milliseconds();

		static std::shared_ptr<PAL> Instance();
	};

	typedef std::shared_ptr<PAL> PALPtr;
}