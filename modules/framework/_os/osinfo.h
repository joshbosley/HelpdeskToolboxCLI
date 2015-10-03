#ifndef HDTB_OSINFO
#define HDTB_OSINFO

// OS information
#ifdef _WIN32

    #define HDTB_OS "WIN_OS"
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

    // Terminal Colors !
    #define HDTB_PUT_RESET       "\033[0m"
    #define HDTB_PUT_BLACK       "\033[30m"             /* Black */
    #define HDTB_PUT_RED         "\033[31m"             /* Red */
    #define HDTB_PUT_GREEN       "\033[32m"             /* Green */
    #define HDTB_PUT_YELLOW      "\033[33m"             /* Yellow */
    #define HDTB_PUT_BLUE        "\033[34m"             /* Blue */
    #define HDTB_PUT_MAGENTA     "\033[35m"             /* Magenta */
    #define HDTB_PUT_CYAN        "\033[36m"             /* Cyan */
    #define HDTB_PUT_WHITE       "\033[37m"             /* White */
    #define HDTB_PUT_BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
    #define HDTB_PUT_BOLDRED     "\033[1m\033[31m"      /* Bold Red */
    #define HDTB_PUT_BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
    #define HDTB_PUT_BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
    #define HDTB_PUT_BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
    #define HDTB_PUT_BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
    #define HDTB_PUT_BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
    #define HDTB_PUT_BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

#else

    #define HDTB_OS "UNKNOWN_OS"
    #define HDTB_EGG  "YOU_SUCK"

#endif



#endif // HDTB_OSINFO

