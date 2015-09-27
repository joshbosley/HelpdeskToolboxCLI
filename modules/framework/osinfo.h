#ifndef HDTB_OSINFO
#define HDTB_OSINFO

// OS information
#ifdef _WIN32
    #define HDTB_OS "WIN_OS
    #define HDTB_OS_ROOT "%SYSTEMROOT%"
    #define HDTB_OS_DRIVE "%SYSTEMDRIVE%"
    #define HDTB_OS_PROGRAM_INSTALLS "%ProgramFiles%"
    #define HDTB_OS_USER_HOME "%HOMEPATH%"

    // Windows specific
    #define HDTB_OS_WINDOWS_X86_INSTALLS "%ProgramFiles(86)%"
    #define HDTB_OS_WINDOWS_APP_DATA "%LOCALAPPDATA%"

#elif __APPLE__

    #define HDTB_OS "MAC_OS"
    #define HDTB_OS_USER_HOME "$HOME"

#else

    #define HDTB_OS "UNKNOWN_OS"

#endif



#endif // HDTB_OSINFO

