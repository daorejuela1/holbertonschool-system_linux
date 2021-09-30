#ifndef H_COMMON_TOOLS
#define H_COMMON_TOOLS

#define MSG_LEN 8192

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>

/**
 * struct socket_params - socket neccesary params
 * @fd: socket file descriptor
 * @port: socket port
 * @ip_addr: socket ip address
 * @addr: socket data structure
 *
 * Description: This structure give us input arguments
 * to use sockets - for Holberton project
 */
typedef struct socket_params
{
	int fd;
	int port;
	char *ip_addr;
	struct sockaddr_in *addr;
} socket_params;

/**
 * struct response_parse - stores the HTTP response params
 * @method: stores the method of the HTTP request
 * @path: stores the path to be used
 * @version: stores the version
 *
 * Description: This structure give us input arguments
 * to use sockets - for Holberton project
 */
typedef struct response_parse
{
	char *method;
	char *path;
	char *version;
} response_parse;

typedef struct sockaddr_in sockaddr_in;
typedef struct sockaddr sockaddr;

int create_socket(int domain, int type, int protocol);
int bind_listen_socket(socket_params *my_socket);
int accept_connection(socket_params *my_socket, socket_params *my_client);
int parse_message(char message[], response_parse *response);
int free_response(response_parse *response);
#endif
