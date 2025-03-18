#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// func prototype needs to be declared before main
int create_socket();
int bind_socket(int sockfd, int port);
int start_listening(int server_socket, int backlog);
int accept_connection(int server_socket);
void handle_client(int client_socket);

int main(int argc, char *argv[])
{
    // check if the user has provided a port number
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <port number>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int port = atoi(argv[1]); // make provided port into int

    // make sure user has given a valid port number
    if (port <= 1024 || port > 65535)
    {
        fprintf(stderr, "Invalid port number. Use a port between 1025 and 65535.\n");
        exit(EXIT_FAILURE); // exit program
    }

    printf("Starting server on port %d...\n", port);

    // socket gets created
    int server_socket = create_socket();

    // socket gets bound
    if (bind_socket(server_socket, port) < 0)
    {
        fprintf(stderr, "Failed to bind socket\n"); // error message
        close(server_socket);
        exit(EXIT_FAILURE); // exit program
    }

    // start listening on all interfaces
    if (start_listening(server_socket, 5) < 0)
    {                                                   // queue backlog of 5, so we do not have to wait for a connection
        fprintf(stderr, "Failed to start listening\n"); // error message
        close(server_socket);
        exit(EXIT_FAILURE); // exit program
    }

    printf("Server is running. Waiting for connections...\n");

    // accept the connection and handle the client
    while (1)
    {
        int client_socket = accept_connection(server_socket);
        if (client_socket < 0)
        {
            fprintf(stderr, "Failed to accept client connection.\n");
            continue;
        }

        handle_client(client_socket); // handle client function handles the received message

        printf("Connection closed.\n");
    }

    close(server_socket);
    return 0;
}

int create_socket()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        fprintf(stderr, "Failed to create socket\n"); // error message
        exit(EXIT_FAILURE);                           // exit program
    }
    return sockfd;
}

int bind_socket(int sockfd, int port)
{
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        fprintf(stderr, "Failed to bind socket\n"); // error message
        return -1;
    }
    return 0;
}

int start_listening(int server_socket, int backlog)
{
    if (listen(server_socket, backlog) < 0)
    {                                          // if listen fails
        fprintf(stderr, "Failed to listen\n"); // error message
        exit(EXIT_FAILURE);                    // exit program
    }
    return 0;
}

int accept_connection(int server_socket)
{
    struct sockaddr_in client_address;                                                              // client address
    socklen_t client_addrlen = sizeof(client_address);                                              // length of client address
    int client_socket = accept(server_socket, (struct sockaddr *)&client_address, &client_addrlen); // accept connection
    if (client_socket < 0)
    {                                                     // if accept fails
        fprintf(stderr, "Failed to accept connection\n"); // error message
        exit(EXIT_FAILURE);                               // exit program
    }
    printf("Client connected: %s\n", inet_ntoa(client_address.sin_addr)); // print client address
    return client_socket;                                                 // return client socket
}

void handle_client(int client_socket)
{
    char buffer[1024];                                                       // standard buffer size should be plenty of space
    ssize_t bytes_read = recv(client_socket, buffer, sizeof(buffer) - 1, 0); // receive message from client
    if (bytes_read < 0)
    {                                                   // if recv fails
        fprintf(stderr, "Failed to receive message\n"); // error message
        exit(EXIT_FAILURE);                             // exit program
    }
    buffer[bytes_read] = '\0';                                                                                                                                                 // null terminate the buffer
    printf("Received message: %s\n", buffer);                                                                                                                                  // print received message
    const char *response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE html><html><head><title>Hey you!</title></head><body><h1>Hey you!</h1></body></html>"; // response message simple html page

    send(client_socket, response, strlen(response), 0); // send response to client

    close(client_socket); // close client socket
}
