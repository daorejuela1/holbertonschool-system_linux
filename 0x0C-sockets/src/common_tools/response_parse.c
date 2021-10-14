/*
 * ===========================================================================
 *
 *       Filename:  socket_creation.c
 *
 *    Description: Module to parse a socket information
 *
 *        Version:  1.0
 *        Created:  09/29/2021 04:45:30 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  David Orejuela
 *   Organization:
 *
 * ===========================================================================
 */
#include "common_tools.h"
#define TOKEN " \t\r\n"
/**
 * parse_response - gets what to do with the response method & path
 * @message: full message
 * @response: line to scan
 *
 * Return: 1 on success 0 on failure
 */
char *parse_response(char message[], response_parse *response)
{
	char path[MSG_LEN];
	char *filtered_path = NULL;

	strcpy(path, response->path);
	filtered_path = strtok(path, "?");
	if (strcmp(filtered_path, "/todos") == 0)
	{
		if (strcmp(response->method, "POST") == 0)
			return (create_todo(message));
		else if (strcmp(response->method, "GET") == 0)
			return (get_todos());
		return (BAD_RESPONSE);
	}
	else
	{
		return (BAD_RESPONSE);
	}
}

/**
 * get_key_value - gets the value of the desired key
 * @key: Key used to get the value
 *
 * Return: value on success or null if not found
 */
char *get_key_value(char *key, query_data **structure, int struct_len)
{
	int i = 0;

	for (i = 0; i < struct_len; i++)
	{
		if (strcmp(structure[i]->name, key) == 0)
			return (structure[i]->value);
	}
	return (NULL);
}
