#include "socket.h"
#define MSG_LEN 1024
#define SOCKET_SIZE sizeof(my_socket)
#define PORT_NUMBER 12345
#define DEF_MSG "Message received"

/**
 * main - opens an IPv4/TCP socket, and listens to traffic on port 12345
 *
 * Return: 1 on success 0 on failure
 */
int main(void)
{
	int socket_fd = 0, accept_fd = 0;
	struct sockaddr_in my_socket, my_client;
	char *client_address, message[MSG_LEN];
	socklen_t client_size;

	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_fd == -1)
	{
		printf("Socket error %s\n", strerror(errno));
		return (EXIT_FAILURE);
	}
	my_socket.sin_family = AF_INET, my_socket.sin_port = htons(PORT_NUMBER);
	my_socket.sin_addr.s_addr = inet_addr("0.0.0.0");
	if (bind(socket_fd, (struct sockaddr *)&my_socket, SOCKET_SIZE) == -1)
	{
		printf("Binding error %s\n", strerror(errno));
		return (EXIT_FAILURE);
	}
	if (listen(socket_fd, 132) == -1)
	{
		printf("Listen error %s\n", strerror(errno));
		return (EXIT_FAILURE);
	}
	printf("Server listening on port %d\n", PORT_NUMBER);
	client_size = sizeof(my_client);
	accept_fd = accept(socket_fd, (struct sockaddr *) &my_client, &client_size);
	if (accept_fd == -1)
	{
		printf("Accept error %s\n", strerror(errno));
		return (EXIT_FAILURE);
	}
	client_address = inet_ntoa(my_client.sin_addr);
	printf("Client connected: %s\n", client_address);
	if (recv(accept_fd, message, MSG_LEN, MSG_WAITALL) == -1)
	{
		printf("Read error %s\n", strerror(errno));
		return (EXIT_FAILURE);
	}
	printf("%s: \"%s\"\n", DEF_MSG, message), close(accept_fd), close(socket_fd);
	return (EXIT_SUCCESS);
}
