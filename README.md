# UDP Chat Application

A versatile UDP-based chat application implemented in C++ that supports both peer-to-peer and client-server communication modes. This application demonstrates the use of Berkeley socket primitives and can be analyzed using Wireshark for network packet inspection.

## Features

- Peer-to-peer chat mode
- Client-server chat mode
- UDP socket implementation for fast, lightweight communication
- Multithreaded message handling
- Support for message broadcasting in server mode
- Real-time message display with sender information
- Clean shutdown mechanism
- Compatible with Wireshark packet analysis

## Prerequisites

- C++ compiler with C++11 support
- POSIX-compliant operating system (Linux/Unix/macOS)
- pthread library
- Wireshark (for packet analysis)

## Project Structure

```
udp-chat/
│
├── udp_chat.h         # Header file with class definition
├── udp_chat.cpp       # Implementation of UDP chat functionality
├── server.cpp         # Server mode implementation
├── peer.cpp          # Peer-to-peer mode implementation
└── README.md         # This file
```

## Compilation

Use the following commands to compile the application:

```bash
# Compile the shared components
g++ -c udp_chat.cpp -o udp_chat.o

# Compile the server
g++ server.cpp udp_chat.o -o server -pthread

# Compile the peer application
g++ peer.cpp udp_chat.o -o peer -pthread
```

## Usage

### Client-Server Mode

1. Start the server:
```bash
./server
```
The server will start listening on port 8888.

2. Start peers (in different terminals):
```bash
# First peer
./peer 8889 127.0.0.1 8888

# Second peer
./peer 8890 127.0.0.1 8888
```

### Peer-to-Peer Mode

1. On the first machine:
```bash
./peer 8889 192.168.1.2 8890  # Replace IP with actual peer IP
```

2. On the second machine:
```bash
./peer 8890 192.168.1.1 8889  # Replace IP with actual peer IP
```

## Wireshark Packet Analysis

To capture and analyze the UDP packets:

1. Open Wireshark and select your network interface
2. Set up a display filter:
```
udp.port == 8889 || udp.port == 8890
```
3. Start packet capture
4. Run the chat application and exchange messages
5. Observe the UDP packets in Wireshark

### What to Look For in Wireshark

- UDP datagrams containing chat messages
- Source and destination port numbers
- Message contents in packet payload
- No connection establishment packets (UDP is connectionless)
- Packet timestamps and intervals

## Command Reference

### Peer Application
```bash
./peer <local_port> <peer_ip> <peer_port>
```
- `local_port`: Port number for this peer to listen on
- `peer_ip`: IP address of the peer to connect to
- `peer_port`: Port number of the peer to connect to

### Server Application
```bash
./server
```
Starts the server on port 8888 by default.

## Chat Commands

- Type your message and press Enter to send
- Type `quit` and press Enter to exit the application

## Implementation Details

- Uses UDP Berkeley sockets for communication
- Implements multithreading for simultaneous send/receive operations
- Handles network byte order conversion
- Includes error handling for socket operations
- Supports clean application shutdown

## Error Handling

The application includes error handling for:
- Socket creation failures
- Binding errors
- Send/receive failures
- Invalid input parameters

## Limitations

- No message encryption
- No user authentication
- Messages limited to 1024 bytes
- No message persistence
- No message delivery confirmation (UDP limitation)

## Contributing

1. Fork the repository
2. Create a feature branch
3. Commit your changes
4. Push to the branch
5. Create a Pull Request

## License

This project is released under the MIT License. See the LICENSE file for details.

## Troubleshooting

### Common Issues

1. **Bind error: Address already in use**
   - Wait a few minutes for the port to be released
   - Use a different port number
   - Check if another application is using the port

2. **Connection refused**
   - Verify the IP address and port
   - Check if the peer/server is running
   - Check firewall settings

3. **Messages not receiving**
   - Verify network connectivity
   - Check port numbers
   - Ensure correct IP addresses

### Debug Tips

- Use `netstat -uap` to check UDP ports in use
- Run with `strace` for detailed system call information
- Check system logs for network-related errors

## Contact

For bug reports and feature requests, please open an issue in the project repository.
