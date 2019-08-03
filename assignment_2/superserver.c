#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <signal.h>
#include <errno.h>

#define MAX_SERVICES 10

typedef struct sockets_data {
    char protocol[3];
    char service_mode[6];
    char service_port[5];
    char *service_path;
    char *service_name;
    int socket_fd;
    int pid;
} sockets_data;

void handle_signal(int sig);

int main(int argc, char **argv, char **env) {
    sockets_data sockets[MAX_SERVICES];
    struct sockaddr_in addr;
	short int services_count = 0;

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    //...
    for (int i = 0; i < services_count; i++) {
        int sockfd = 0;
        int sock_type = 0;
        int sock_proto = 0;

        if (strncmp(sockets[i].protocol, "udp", 3) == 0) {
            sock_type = SOCK_DGRAM;
            sock_proto = IPPROTO_UDP;
        } else if (strncmp(sockets[i].protocol, "tcp", 3) == 0) {
            sock_type = SOCK_STREAM;
            sock_proto = IPPROTO_TCP;
        }
        sockfd = socket(AF_INET, sock_type, sock_proto);
        if (sockfd < 0) {
            perror("Error on \"socket\" function");
            exit(EXIT_FAILURE);
        }
        sockets[i].socket_fd = sockfd;
        addr.sin_port = htons(atoi(sockets[i].port));
        if (bind(sockfd, &addr, sizeof(addr)) < 0) {
            perror("Error on \"bind\" function");
            exit(EXIT_FAILURE);
        }
        if (strncmp(sockets[i].protocol, "tcp", 3) == 0) {
            if (listen(sockfd, SOMAXCONN) < 0) {
                perror("Error on \"listen\" function");
                exit(EXIT_FAILURE);
            }
        }
    }	
	signal(SIGCHLD, handle_signal);
	//...
	return 0;
}

// handle_signal implementation
void handle_signal (int sig) {
	// Call to wait system-call goes here
	
	
	switch (sig) {
		case SIGCHLD : 
			// Implementation of SIGCHLD handling goes here	
			
			
			break;
		default : printf ("Signal not known!\n");
			break;
	}
}
