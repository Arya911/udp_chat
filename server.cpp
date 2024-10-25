// server.cpp
#include "udp_chat.h"

int main() {
    UDPChat server(8888); // Server mode
    std::cout << "Chat server started on port 8888" << std::endl;
    
    server.start();
    
    std::string message;
    while (true) {
        std::getline(std::cin, message);
        if (message == "quit") break;
        // Messages from server will be broadcast to all connected clients
        server.sendMessage("Server: " + message);
    }
    
    server.stop();
    return 0;
}
