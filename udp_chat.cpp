// udp_chat.cpp
#include "udp_chat.h"

UDPChat::UDPChat(int port, const std::string& ip) {
    // Create UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        std::cerr << "Error creating socket" << std::endl;
        exit(1);
    }

    // Configure address
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    
    if (ip.empty()) {
        addr.sin_addr.s_addr = INADDR_ANY; // Server mode
    } else {
        addr.sin_addr.s_addr = inet_addr(ip.c_str()); // P2P mode
    }

    // Bind socket
    if (bind(sockfd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        std::cerr << "Error binding socket" << std::endl;
        close(sockfd);
        exit(1);
    }

    isRunning = false;
}

UDPChat::~UDPChat() {
    stop();
    close(sockfd);
}

void UDPChat::receiveMessages() {
    char buffer[1024];
    struct sockaddr_in senderAddr;
    socklen_t senderLen = sizeof(senderAddr);

    while (isRunning) {
        memset(buffer, 0, sizeof(buffer));
        int bytesReceived = recvfrom(sockfd, buffer, sizeof(buffer) - 1, 0,
                                   (struct sockaddr*)&senderAddr, &senderLen);
        
        if (bytesReceived > 0) {
            std::string senderIP = inet_ntoa(senderAddr.sin_addr);
            int senderPort = ntohs(senderAddr.sin_port);
            std::cout << "[" << senderIP << ":" << senderPort << "]: " 
                      << buffer << std::endl;
        }
    }
}

void UDPChat::start() {
    isRunning = true;
    receiveThread = std::thread(&UDPChat::receiveMessages, this);
}

void UDPChat::stop() {
    if (isRunning) {
        isRunning = false;
        if (receiveThread.joinable()) {
            receiveThread.join();
        }
    }
}

void UDPChat::sendMessage(const std::string& message, const std::string& destIP, int destPort) {
    struct sockaddr_in destAddr;
    memset(&destAddr, 0, sizeof(destAddr));
    destAddr.sin_family = AF_INET;
    
    if (!destIP.empty() && destPort > 0) {
        destAddr.sin_addr.s_addr = inet_addr(destIP.c_str());
        destAddr.sin_port = htons(destPort);
    } else {
        // Use pre-configured address (for P2P mode)
        destAddr = addr;
    }

    sendto(sockfd, message.c_str(), message.length(), 0,
           (struct sockaddr*)&destAddr, sizeof(destAddr));
}

