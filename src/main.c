#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>

int send_all(int socket, const char *buffer, size_t length);

int main(void) {

    struct sockaddr_in server_addr = {
        .sin_family = AF_INET, // IPV4
        .sin_port = htons(8080),
        .sin_addr.s_addr = INADDR_ANY
    };

    struct sockaddr_in client_addr;
    socklen_t client_addr_len;

    int server_socket;
    int client_socket;

    char client_ip[INET_ADDRSTRLEN];

    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (server_socket == -1){
        perror("Socket creation failed");
        return 1;
    }

    if(bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Bind failed");
        close(server_socket);
        return 1;
    }

    if(listen(server_socket, 5) == -1) {
        perror("Listen failed");
        close(server_socket);
        return 1;
    }

    printf("TCP Socket created successfully\n");
    printf("Socket descriptor: %d\n", server_socket);
    printf("Socket successfully bound to port 8080\n");
    printf("Server is listening on port 8080\n");

    while (1) {
        client_addr_len = sizeof(client_addr);

        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_len);

        if(client_socket == -1) {
            perror("Accept failed");
            continue;
        }
        
        inet_ntop(AF_INET, &(client_addr.sin_addr), client_ip, sizeof(client_ip));
        
        int client_port= ntohs(client_addr.sin_port);

        printf("Client connected\n");
        printf("Client IP: %s\n", client_ip);
        printf("Client Port: %d\n", client_port);

        char buffer[1024];

        while (1) {
            ssize_t bytes_received = recv( //ssize_t: a signed type used for byte count returned by recv()
            client_socket,
            buffer, 
            sizeof(buffer) - 1, 
            0);
            
            if(bytes_received == -1) {
                perror("Receive failed");
                break;
            }
            
            if(bytes_received == 0) {
                printf("Client disconnected\n");
                break;
            }
            
            buffer[bytes_received] = '\0';
            printf("Received message: %s\n", buffer);
            
            if (send_all(client_socket, buffer, bytes_received) == -1) {
                break;
            }
            
            printf("Echoed %zd bytes to client\n", bytes_received);
        }
        
        close(client_socket);
        printf("Client socket closed\n");
    }
}

int send_all(int socket, const char *buffer, size_t length){
    size_t total_sent = 0;
    while (total_sent < length) {
        ssize_t bytes_sent = send(socket, buffer + total_sent, length - total_sent, 0);
        if (bytes_sent == -1) {
            perror("Send failed");
            return -1;
        }

        if (bytes_sent == 0) {
            return -1;
        }
        total_sent += bytes_sent;
    }

    return 0;
}