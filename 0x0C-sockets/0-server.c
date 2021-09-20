#include "socket.h"
#define SOCKET_SIZE sizeof(my_socket)

/**
 * main - opens an IPv4/TCP socket, and listens to traffic on port 12345
 *
 * Return: 1 on success 0 on failure
 */
int main(void)
{
	const int port_number = 12345;
	int file_descriptor = 0;
	struct sockaddr_in my_socket;

	file_descriptor = socket(AF_INET, SOCK_STREAM, 0);
	if (file_descriptor == -1)
	{
		printf("Socket error %s\n", strerror(errno));
		return (EXIT_FAILURE);
	}
	my_socket.sin_family = AF_INET;
	my_socket.sin_port = htons(port_number);
	my_socket.sin_addr.s_addr = inet_addr("0.0.0.0");
	if (bind(file_descriptor, (struct sockaddr *)&my_socket, SOCKET_SIZE) == -1)
	{
		printf("Binding error %s\n", strerror(errno));
		return (EXIT_FAILURE);
	}
	if (listen(file_descriptor, 132) == -1)
	{
		printf("Listen error %s\n", strerror(errno));
		return (EXIT_FAILURE);
	}
	printf("Server listening on port %d\n", port_number);
	while (1)
	{

	}
	return (EXIT_SUCCESS);
}
