
// peer.cpp
#include "udp_chat.h"

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cout << "Usage: " << argv[0] << " <local_port> <peer_ip> <peer_port>" << std::endl;
        return 1;
    }

    int localPort = std::stoi(argv[1]);
    std::string peerIP = argv[2];
    int peerPort = std::stoi(argv[3]);

    UDPChat peer(localPort, peerIP);
    std::cout << "P2P chat started on port " << localPort << std::endl;
    std::cout << "Connected to peer at " << peerIP << ":" << peerPort << std::endl;
    
    peer.start();
    
    std::string message;
    while (true) {
        std::getline(std::cin, message);
        if (message == "quit") break;
        peer.sendMessage(message, peerIP, peerPort);
    }
    
    peer.stop();
    return 0;
}