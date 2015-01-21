//  The server should listen on TCP port 5000 for incoming connections. It should accept
//  the first connection made, read all the data it can from that connection, print that data to the screen,
//  close the connection, and exit.
// * socket(), bind(), listen(), accept(), recv(), send(), close()
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>  // tels which group of sockets has data available to read, this is for handling multiple sockets
#include <unistd.h>

int main (int argc, char *argv[]) {
struct sockaddr_in addr;


    // socket():
    int fd = socket (AF_INET, SOCK_STREAM, 0); // create a new communication end point
    if (fd == -1) {
        return -1; // an error occured
    }

    
    addr.sin_family = AF_INET;
    addr.sin_port = htons (5000);
    addr.sin_addr.s_addr = htonl (INADDR_ANY);
    

    // bind():
    // make the newly created socket into a TCP server:
    // bind the socket into an appropriate port:
    if (bind (fd, (struct sockaddr *) &addr, sizeof(addr) ) == -1) {  // attach a local address  to a socket
        return -1; // an error occured
    }


    // listen():
    int listens;
    listens = listen (fd, 10); 
    if (listens == -1) {
        return -1;  // error has occured
    }


    // accept();
    // accepts a connection,  returns new file descriptor for the connection (connfd) and   clientaddr (cliaddr) 
    int connfd;
    struct sockaddr_in cliaddr;
    socklen_t cliaddrlen;
    cliaddrlen = sizeof(cliaddr);

    connfd = accept (fd, (struct sockaddr *) &cliaddr, &cliaddrlen);
    if (connfd == -1) {
        return -1; // error has occured
    }


    // read():


    // write():
    char data[] = "Hello, world!"; 
    int datalen, count;

    datalen = strlen(data);
    count = write(connfd, data, datalen); 
    if (count == -1) {
        perror ("Error while writing.\n");
    }

    // ...


    // close():
    int status;
    status = close(connfd); // closing the socket, status = 0 if successful, -1 if error

}



