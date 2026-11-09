#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main(void) {

    struct sockaddr_in server_addr = {
        .sin_family = AF_INET, // IPV4
        .sin_port = htons(8080),
        .sin_addr.s_addr = INADDR_ANY
    };

    int server_socket;

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

    return 0;
}