#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "main.h"
/**
 * tokenize_path - Fetches actual path of a command.
 * @path: environment path of the OS.
 * @cmd: command path.
 * Return: Actual path of the command or NULL if not found.
 */
char *tokenize_path(char *path, char *cmd)
{
	char *path_token, *file_path;
	char *delim = ":";
	int cmd_length, path_length;
	struct stat buffer;

	/* Get the length of the cmd */
	cmd_length = strlen(cmd);
	/* Let's break down the path and get all the directories available */
	path_token = strtok(path, delim);
	while (path_token != NULL)
	{
		/* Get the length of the path */
		path_length = strlen(path_token);
		/* Allocate memory for storing the cmd together with the directory name. */
		/* NB: added 2 for the slash and NULL character that will be introduced */
		/* in the full cmd. */
		file_path = malloc(cmd_length + path_length + 2);
		/* Build path */
		strcpy(file_path, path_token);
		strcat(file_path, "/");
		strcat(file_path, cmd);
		/* Check if file path exists otherwise try the next directory path */
		if (stat(file_path, &buffer) == 0)
		{
			cmd = file_path;
			return (file_path);
		}
		else
		{
			/* Freeing up the file_path to check for the next path */
			free(file_path);
			path_token = strtok(NULL, delim);
		}
	}
	return (NULL);
}

/**
 * get_path - Fetches actual path of a command.
 * @cmd: command path.
 *
 * Return: Actual path of the command,
 * or NULL if not found.
 */
char *get_path(char *cmd)
{
	char *actual_path;
	char *path, *path_copy;
	struct stat buffer;

	/* Check if the cmd itself is the actual path */
	if (stat(cmd, &buffer) == 0)
		return (cmd);

	path = getenv("PATH"); /* Environment path */
	if (path)
	{
		/* Duplicate the path */
		path_copy = strdup(path);
		actual_path = tokenize_path(path_copy, cmd);
		/* Free up allocated memory path_copy before returning the actual_path */
		free(path_copy);
	}

	return (actual_path);
}

