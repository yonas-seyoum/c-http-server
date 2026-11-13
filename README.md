# C HTTP Server

## Current Features
- Creates an IPv4 TCP socket.
- Binds to port `8080` and listens for incoming connections.
- Accepts incoming client connections.
- Receives data from connected clients.
- Echoes received data back to clients.
- Handles multiple successive client connections.
- Detects client disconnections.
- Handles partial TCP writes.
- Handles interrupted system calls (`EINTR`).
- Handles `SIGINT` for graceful server shutdown.
- Uses `SO_REUSEADDR` to support convenient server restarts.
- Includes basic socket error handling and resource cleanup.

## Requirements
- Linux or WSL2 with Ubuntu
- GCC or another compatible C compiler
- CMake 3.20 or later
- Netcat (`nc`) for manual testing

## Project Structure
```text
c-http-server/
├── src/
│   └── main.c
├── CMakeLists.txt
├── .gitignore
└── README.md
```

## Build Instructions

Clone the repository:

```bash
git clone https://github.com/yonas-seyoum/c-http-server.git
cd c-http-server
```

Configure the project:

```bash
cmake -S . -B build
```
Build the server:

```bash
cmake --build build
```

## Run the Server

Start the server:

```bash
./build/server
```

The server listens on port `8080` on all IPv4 interfaces.

## Test the Server

Open another terminal and connect using Netcat:

```bash
nc 127.0.0.1 8080
```

Send a message:

```text
Hello server
```

The server should echo the message back:

```text
Hello server
```

You can send multiple messages over the same connection.

To disconnect, press `Ctrl+C` in the client terminal.

To stop the server, press `Ctrl+C` in the server terminal.

## Verify the Listening Port

To check whether the server is listening:

```bash
ss -ltnp 'sport = :8080'
```

## Current Architecture

The server currently handles connections sequentially:

1. Create and configure the server socket.
2. Bind the socket to port `8080`.
3. Start listening for connections.
4. Accept an incoming client connection.
5. Receive data from the connected client.
6. Echo the received data back.
7. Detect client disconnection and close its socket.
8. Return to accepting the next client.
9. Close the listening socket during shutdown.

## Current Limitations

- The server handles one connected client at a time.
- It does not implement HTTP request parsing or HTTP response formatting yet.
- It does not support concurrent client connections.
- It does not implement persistent HTTP connections or advanced networking features.
