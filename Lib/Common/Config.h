#pragma once

namespace PAL
{
#if defined(__linux__)
	
#define __BUILD_FOR_UNIX__
#define __BUILD_FOR_LINUX__

#elif defined(_WIN32)
	
#define __BUILD_FOR_WINDOWS__

#else

#endif
}