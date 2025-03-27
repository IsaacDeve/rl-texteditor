#if defined(_WIN32) || defined(_WIN64) || (defined(__CYGWIN__) && !defined(_WIN32))
    #define PLATFORM_WINDOWS
#endif

#ifdef PLATFORM_WINDOWS
    #include "winh.hpp"
#endif
