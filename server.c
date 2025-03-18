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

return 0;
}
