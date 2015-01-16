// Your client should connect to TCP port 5000 of a host named on the command line,
// send the text “Hello, world!”, then close the connection. The client should take the name of the
// machine on which the server is running as its single command line argument (i.e., if the server
// is running on machine bo720-1-01.dcs.gla.ac.uk you should run your client using the
// command hello client bo720-1-01.dcs.gla.ac.uk.

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>

struct sockaddr_in addr;
// ...

// *

// creating a socket:
int fd = socket(AF_INET, SOCK_STREAM, 0); // returns an integer known as a file descriptor that identifies the newly created socket

if (fd == -1) {
    return -1; // an error has occured
}




// *


if (connect (fd, (struct sockaddr *) &addr, sizeof(addr)) == -1) {
    //... error has occured
} 

// ...


