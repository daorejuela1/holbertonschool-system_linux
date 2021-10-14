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

extern int todo_id;
/**
 * create_response - response using object json format
 * @task - task used
 *
 * Return: Nothing
 */
static char *create_response(todo_task *task)
{
	int i = 0;
	static char response[1000];
	char data[1000];
	char value[1000];
	char content_length[20];

	memset(data, 0, 1000);
	strcpy(data, "{");
	for (i = 0; i < 3; i++)
	{
		if (i == 0)
			sprintf(value, "\"id\":%d,", task->id);
		if (i == 1)
			sprintf(value, "\"title\":\"%s\",", task->title);
		if (i == 2)
			sprintf(value, "\"description\":\"%s\"", task->description);
		strcat(data, value);
	}
	strcat(data, "}");
	sprintf(content_length, "%lu", strlen(data));
	memset(response, 0, 1000);
	strcpy(response, CREATED_RESPONSE);
	strcat(response, "Content-Length: ");
	strcat(response, content_length);
	strcat(response, "\r\n");
	strcat(response, "Content-Type: application/json\r\n\r\n");
	strcat(response, data);
	return (response);
}

/**
 * parse_message - extracts information from socket message
 * @message: full message
 * @response: line to scan
 *
 * Return: 1 on success 0 on failure
 */
char *create_todo(char message[])
{
	int num_headers = 0, num_body = 0;
	char *title = NULL, *description = NULL;
	char *content_length = NULL;
	query_data **headers = NULL, **body = NULL;
	todo_task *new_task = NULL;

	headers = parse_headers(message, &num_headers);
	content_length = get_key_value("Content-Length", headers, num_headers);
	if (!content_length)
		return (LENGTH_REQ_RESPONSE);
	body = parse_body(message, &num_body);
	title = get_key_value("title", body, num_body);
	description = get_key_value("description", body, num_body);
	if (!title || !description)
		return (UNPROCCESABLE_RESPONSE);
	new_task = malloc(sizeof(todo_task));
	new_task->id = todo_id++;
	strcpy(new_task->title, title);
	strcpy(new_task->description, description);
	free_query(body, num_body);
	free_query(headers, num_headers);
	return (create_response(new_task));
}
