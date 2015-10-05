#ifndef HDTB_NETWORKDIRECTORY
#define HDTB_NETWORKDIRECTORY

// Functions
#define HDTB_NETWORK_CMD_PING           0   // Ping host
#define HDTB_NETWORK_CMD_RESET          1   // Reset adapter
#define HDTB_NETOWRK_CMD_REACH          2   // Generate traffic
#define HDTB_NETWORK_CMD_KNOCK_SEQUENCE 3   // Port knocker

#define HDTB_NETWORK_CMD_KILL           99  // Stop whatever is happening

// Sub-Modules
#define HDTB_NETWORK_CMD_COMMLINK       4   // Chat server - Initiates CLIENT_COMM


// Submodule that the user doesn't directly interact with
#define HDTB_NETWORK_SUB_CLIENT         5

    #define HDTB_CLIENT_LOAD       6  // Initiate the client
    #define HDTB_CLIENT_SEND       7  // Send data to a port
    #define HDTB_CLIENT_COMM       8  // Begin human convo to server
    #define HDTB_CLIENT_BLIND_COMM 9  // Begin automated transfer process (allow automated comms not seen by user

#endif // HDTB_NETWORKDIRECTORY

