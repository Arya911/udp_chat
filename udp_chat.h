// udp_chat.h
#pragma once
#include <string>
#include <iostream>
#include <thread>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>

class UDPChat {
private:
    int sockfd;
    struct sockaddr_in addr;
    bool isRunning;
    std::thread receiveThread;
    
    void receiveMessages();

public:
    UDPChat(int port, const std::string& ip = "");
    ~UDPChat();
    void start();
    void stop();
    void sendMessage(const std::string& message, const std::string& destIP = "", int destPort = 0);
};