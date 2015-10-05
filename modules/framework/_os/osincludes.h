#ifndef HDTB_OSINCLUDES
#define HDTB_OSINCLUDES

#ifdef _WIN32

    #include "windows.h"

#elif __APPLE__

    // HDD Information
    #include <unistd.h>
    #include <sys/sysctl.h>
    #include <sys/statvfs.h>

    // Network Server
    #include<netdb.h>
    #include<string.h>
    #include<arpa/inet.h>
    #include<sys/socket.h>

#else

#endif

#endif // HDTB_OSINCLUDES

