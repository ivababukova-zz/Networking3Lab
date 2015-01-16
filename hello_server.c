//  The server should listen on TCP port 5000 for incoming connections. It should accept
//  the first connection made, read all the data it can from that connection, print that data to the screen,
//  close the connection, and exit.
#include <stdio.h>
// to use the socket API:
#include <sys/types.h>
#include <sys/socket.h>

// *

// make the newly created socket into a TCP server:
// bind the socket into an appropriate port:

if (bind (fd, ))


// *



struct addrinfo hints;
struct addrinfo *ai0;
int i;

// ...

memset(&hints, 0, sizeof(hints));
hints.ai_family = PF_UNSPEC;
// Can use either IPv4 or IPv6
hints.ai_socktype = SOCK_STREAM; // Want a TCP socket
if ((i = getaddrinfo("www.example.com", "5000", &hints, &ai0)) != 0) {
    printf("Error: unable to lookup IP address: %s", gai_strerror(i));
// ...
}

// ai0 is a pointer to the head of a linked list of struct addrinfo
// values containing the possible addresses of the server; interate
// through the list, trying to connect to each turn, stopping when
// a connection succeeds:
struct addrinfo *ai;

int fd;  // create a socket
for (ai = ai0; ai != NULL; ai = ai->ai_next) {
    fd = socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol);
    if (fd == -1) {
        // Unable to create socket, try next address in list
        continue;
    }
    if (connect(fd, ai->ai_addr, ai->ai_addrlen) == -1) {
        // couldn’t connect to the address, try next in list
        close(fd);
        continue;
    }
    break; // successfully connected
}
if (ai != NULL) {
    // Successfully connected: fd is a file descriptor of a socket
    // connected to the server; use the connection
    // ...
} else {
    // Couldn’t connect to any of the addresses, handle failure...
    // ...
}

