#include "../common_tools/common_tools.h"
/*
 * ===========================================================================
 *
 *       Filename:  main.c
 *
 *    Description: IPv4/TCP socket, and listens to traffic on port 8080
 *
 *        Version:  1.0
 *        Created:  09/29/2021 04:33:27 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  David Orejuela
 *   Organization:
 *
 * ===========================================================================
 */
#define SOCKET_SIZE sizeof(my_socket)
#define PORT_NUMBER 8080
#define DEF_MSG "Raw request"
int todo_id = 0;
todo_task **todo_tasks = NULL;
/**
 * main - opens an IPv4/TCP socket, and listens to traffic on port 12345
 *
 * Return: 1 on success 0 on failure
 */
int main(void)
{
	int msg_len = 0, num_headers = 0, i = 0;
	char ok_response[] = "HTTP/1.1 200 OK\n\n", message[MSG_LEN];
	sockaddr_in my_addr, client_addr;
	socket_params my_socket, my_client;
	response_parse response;
	query_data **headers = NULL;

	setbuf(stdout, NULL);
	my_client.addr = &client_addr, my_socket.addr = &my_addr;
	my_socket.port = PORT_NUMBER, my_socket.ip_addr = "0.0.0.0";
	my_socket.fd = create_socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (my_socket.fd == -1)
		return (EXIT_FAILURE);
	if (!bind_listen_socket(&my_socket))
		return (EXIT_FAILURE);
	while (1)
	{
		memset(message, 0, MSG_LEN);
		if (!accept_connection(&my_socket, &my_client))
			return (EXIT_FAILURE);
		msg_len = recv(my_client.fd, message, MSG_LEN, 0);
		if (msg_len == -1)
		{
			printf("Read error %s\n", strerror(errno));
			return (EXIT_FAILURE);
		}
		parse_message(message, &response);
		printf("%s: \"%s\"\n", DEF_MSG, message);
		headers = parse_headers(message, &num_headers);
		for (i = 0; i < num_headers; i++)
			printf("Header: \"%s\" -> \"%s\"\n", headers[i]->name,  headers[i]->value);
		free_response(&response), free_query(headers, num_headers);
		if (send(my_client.fd, ok_response, strlen(ok_response), 0) == -1)
		{
			printf("Send error %s\n", strerror(errno));
			return (EXIT_FAILURE);
		}
		close(my_client.fd);
	}
	close(my_socket.fd);
	return (EXIT_SUCCESS);
}
