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
#define TOKEN " \n"
/**
 * parse_line - extracts information from socket message
 * @message: full message
 * @line: line to scan
 *
 * Return: 1 on success 0 on failure
 */
int parse_message(char message[], response_parse *response)
{
	char cpy_message[MSG_LEN];
	char *method, *path, *version;

	if (!strcpy(cpy_message, message))
		return (0);
	method = strtok(cpy_message, TOKEN);
	response->method = calloc(strlen(method) + 1, 1);
	strcpy(response->method, method);
	path = strtok(NULL, TOKEN);
	response->path= calloc(strlen(path) + 1, 1);
	strcpy(response->path, path);
	version = strtok(NULL, TOKEN);
	response->version= calloc(strlen(version) + 1, 1);
	strcpy(response->version, version);
	return (1);
}
/**
 * free_response - frees the memory for a response
 * @response - structure with the response
 *
 * Returns: 1 on success
 */
int free_response(response_parse *response)
{
	free(response->method);
	free(response->path);
	free(response->version);
	return (1);
}
