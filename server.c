#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char *argv[]) {

    printf("Number of arguments: %d\n", argc);
    printf("First argument: %s\n", argv[0]);
    printf("Second argument: %s\n", argv[1]);


    int port = 8080; //change to be defined by user

return 0;
}

int create_socket() {
    int server_socket = socket(AF_INET, SOCK_STREAM,  0); // Creates socket using ipv4, tcp and default protocol
    if (server_socket == -1) {
        printf("Failed to create socket\n");
        exit(EXIT_FAILURE);
    }
    return 0;
}

int bind_socket(int server_socket, int port) {
struct sockaddr_in server_address;
server_address.sin_family = AF_INET; // ipv4
server_address.sin_addr.s_addr = INADDR_ANY; // listen to any address (all interfaces)
server_address.sin_port = htons(port); // set port, needs to be changed to be defined by user

// standard library bind function, different from bind_socket function
if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
    printf("Failed to bind socket\n");
    exit(EXIT_FAILURE);
}
return 0;
}
