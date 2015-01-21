// Your client should connect to TCP port 5000 of a host named on the command line,
// send the text “Hello, world!”, then close the connection. The client should take the name of the
// machine on which the server is running as its single command line argument (i.e., if the server
// is running on machine bo720-1-01.dcs.gla.ac.uk you should run your client using the
// command hello client bo720-1-01.dcs.gla.ac.uk.

#include <stdio.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define BUFLEN 1500


int main (int argc, char *argv[]) {

    
    struct addrinfo hints, *ai, *ai0;
    struct hostent *server;
    int status, fd, rcount;
    ssize_t i;
    char buf[BUFLEN];
    

    // creating a socket:
    fd = socket(AF_INET, SOCK_STREAM, 0); // returns an integer known as a file descriptor that identifies the newly created socket
    if (fd == -1) {
        perror ("error opening socket\n");
        exit (1);
    }
    

    // connect() via a DNS query:
    // struct sockaddr_in addr;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = PF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM; // Want a TCP socket

    if ((status = getaddrinfo (argv[1], "5000", &hints, &ai0) ) != 0) {
        printf("Error: unable to lookup IP address: %s", gai_strerror(status));
    }

    // ai0 is a pointer to the head of a linked list of struct addrinfo
    // values containing the possible addresses of the server; interate
    // through the list, trying to connect to each turn, stopping when
    // a connection succeeds:
    for (ai = ai0; ai != NULL; ai = ai->ai_next) {
        fd = socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol);
        if (fd == -1) {
            // Unable to create socket, try next address in list
            continue;
            //perror ("Unable to connect1.\n");
        }

        if (connect(fd, ai->ai_addr, ai->ai_addrlen) == -1) {
            // couldn’t connect to the address, try next in list
            close(fd);
            continue;
        }
        
        break;
    }

    if (ai == NULL) {
        // Unsuccessfully connected, handle the error
        perror ("Unable to connect.\n");
        exit (1);
    }
    
    
    // write():
    
    rcount = write (fd, buf, strlen(buf));
    if (rcount == -1) {
        perror ("error occured while writing to the socket.\n");
        exit (1);
    }
    
    // read() server response:
      rcount = read (fd, buf, BUFLEN);  // reads up to BUFLEN bytes of data from connection -     blocks until data available
    
    if (rcount == -1) {
        // an error has occured
        perror ("Error occured while reading data from the connection.\n");
        exit (1);
    }
    
    for (i = 0; i<rcount; i++) {
        printf ("%c", buf[i]);
    }

    // close():
/*    int statusa;
    statusa = close(fd);
*/
    close(fd);
    freeaddrinfo(ai0);
    return 0;
}





