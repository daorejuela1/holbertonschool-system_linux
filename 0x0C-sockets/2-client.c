#include "socket.h"
#define SOCKET_SIZE sizeof(my_socket)

/**
 * main - Creates a socket and connects to a server
 *
 * @argc: quantity of input parameters
 * @argv: array with the host & port to connect
 * Return: 1 on success 0 on failure
 */
int main(int argc, char *argv[])
{
	int socket_fd = 0, accept_fd = 0;
	struct sockaddr_in my_socket;
	char *host = NULL, *host_number = NULL;
	unsigned long port = 0;

	if (argc != 3)
	{
		printf("Usage: %s <host> <port>\n", argv[0]);
		return (EXIT_FAILURE);
	}
	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	host = argv[1];
	port = atoi(argv[2]);
	if (socket_fd == -1)
	{
		printf("Socket error %s\n", strerror(errno));
		return (EXIT_FAILURE);
	}
	host_number = strcmp(host, "localhost") == 0 ? "127.0.0.1" : host;
	my_socket.sin_family = AF_INET;
	my_socket.sin_port = htons(port);
	my_socket.sin_addr.s_addr = inet_addr(host_number);
	if (connect(socket_fd, (struct sockaddr *)&my_socket, SOCKET_SIZE) == -1)
	{
		printf("Connection error %s\n", strerror(errno));
		return (EXIT_FAILURE);
	}
	printf("Connected to %s:%lu\n", host, port);
	close(accept_fd);
	return (EXIT_SUCCESS);
}
