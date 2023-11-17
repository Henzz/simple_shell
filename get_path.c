#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include "main.h"
/**
 * get_path - Fetches actual path of a command.
 * @cmd: command path.
 *
 * Return: On success actual path of the command,
 * Otherwise NULL if not found.
 */
char *get_path(char *cmd)
{
	char **path_tokens, *file_path;
	char *actual_path;
	int index;
	char *path = "PATH";

	index = get_path_index(path);
	path_tokens = tokenize_path(index, path);
	/* Check if actual path is found */
	if (path_tokens == NULL)
		return (NULL);

	file_path = get_directory(path_tokens, cmd);
	/* Check if file path is found */
	if (file_path == NULL)
	{
		arr_free(path_tokens);
		return (NULL);
	}

	actual_path = build_path(file_path, cmd);
	if (actual_path == NULL)
	{
		arr_free(path_tokens);
		return (NULL);
	}
	arr_free(path_tokens);

	return (actual_path);
}

/**
 * get_path_index - Fetches index of an environment variable.
 * @str: Environment variable to search.
 *
 * Return: On success index of the environment variable,
 * Otherwise -1.
 */
int get_path_index(char *str)
{
	int i, j;
	int len;

	len = str_len(str);
	for (i = 0; environ[i] != NULL; i++)
	{
		for (j = 0; j < len; j++)
		{
			if (environ[i][j] != str[j])
				break;
		}
		if (j == len && environ[i][j] == '=')
			return (i);
	}

	return (-1);
}

/**
 * tokenize_path - Fetches actual file path of a command.
 * @index: Index of the path in the environment variables.
 * @str: String to environment variable name.
 *
 * Return: On success a NULL terminated array of pointer to strings,
 * Otherwise NULL.
 */
char **tokenize_path(int index, char *str)
{
	char **path_tokens, *file_path;
	const char *delim = ":\n";
	int ntoken_count;
	int len;

	len = str_len(str);
	ntoken_count = 0;
	/* Adding plus one to len for the slash sign */
	file_path = environ[index] + (len + 1);
	path_tokens = split_cmd(file_path, delim, ntoken_count);
	if (path_tokens == NULL)
		return (NULL);

	return (path_tokens);
}

/**
 * get_directory - Looks for command or file in directories
 * stored in path_tokens.
 * @path_tokens: An array pointer pointer to strings representing the different
 * paths contained in the PATH environment varible.
 * @cmd: Represents a command. For example ls, echo, pwd, /bin/ls etc.
 *
 * Return: On success a string with the upper most directory containing
 * the command file, Otherwise NULL.
 */
char *get_directory(char **path_tokens, char *cmd)
{
	int i, s;
	char *cwd;
	char *buf;
	size_t size;
	struct stat stat_buf;

	buf = NULL;
	size = 0;
	cwd = getcwd(buf, size);
	if (cwd == NULL)
		return (NULL);
	if (cmd[0] == '/')
		cmd = cmd + 1;
	for (i = 0; path_tokens[i] != NULL; i++)
	{
		s = chdir(path_tokens[i]);
		if (s == -1)
		{
			perror("ERROR!");
			return (NULL);
		}
		s = stat(cmd, &stat_buf);
		if (s == 0)
		{
			chdir(cwd);
			free(cwd);
			return (path_tokens[i]);
		}
	}
	chdir(cwd);
	free(cwd);

	return (NULL);
}

/**
 * build_path - Build correct file path with command file.
 * @directory: Represents a directory in the path.
 * @cmd: Represents a file in a directory of the path.
 *
 * Return: On success a string representing the full path of a command,
 * Otherwise NULL.
 */
char *build_path(char *directory, char *cmd)
{
	int i, j;
	int dir_len;
	int cmd_len;
	int len;
	char *built;

	if (directory == NULL || cmd == NULL)
		return (NULL);
	dir_len = str_len(directory) + 1;
	cmd_len = str_len(cmd) + 1;
	len = dir_len + cmd_len;

	built = malloc(sizeof(char) * len);
	if (built == NULL)
		return (NULL);

	for (i = 0; i < len; i++)
	{
		for (j = 0; directory[j] != '\0'; j++, i++)
			built[i] = directory[j];
		built[i] = '/';
		i++;
		for (j = 0; cmd[j] != '\0'; j++, i++)
			built[i] = cmd[j];
	}
	built[--i] = '\0';

	return (built);
}

