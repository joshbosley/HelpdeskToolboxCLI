#ifndef HDTB_OSINCLUDES
#define HDTB_OSINCLUDES

#ifdef _WIN32

    #include "windows.h"

#elif __APPLE__

    // Yes, some things are included twice. This is okay, it is what header guards are for.
    // This doubles as knowing what libs the modules are using. Since modules are subject
    // to change, we include them twice and move on with our lives.

    // HDD Information
    #include <unistd.h>
    #include <sys/sysctl.h>
    #include <sys/statvfs.h>

    // Network Server
    #include <unistd.h>
    #include <stdlib.h>
    #include <sys/types.h>
    #include <sys/socket.h>

#else

#endif

#endif // HDTB_OSINCLUDES

