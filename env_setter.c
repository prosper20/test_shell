#include "main.h"
#include <stdlib.h>
#include <string.h>

extern char **environ;

/**
 * copy_info - copies info to create
 * a new env or alias
 * @name: name (env or alias)
 * @value: value (env or alias)
 *
 * Return: new env or alias.
 */
char *copy_info(char *name, char *value)
{
	char *new;
	int len_name, len_value, len;

	len_name = _strlen(name);
	len_value = _strlen(value);
	len = len_name + len_value + 2;
	new = malloc(sizeof(char) * (len));
	_strcpy(new, name);
	_strcat(new, "=");
	_strcat(new, value);
	_strcat(new, "\0");

	return (new);
}

/**
 * set_env - sets an environment variable
 *
 * @name: name of the environment variable
 * @value: value of the environment variable
 * @datash: data structure (environ)
 * Return: no return
 */
/*void set_env(char *name, char *value)
{
	int i;
	char *var_env, *name_env;

	for (i = 0; environ[i]; i++)
	{
		var_env = _strdup(environ[i]);
		name_env = _strtok(var_env, "=");
		if (_strcmp(name_env, name) == 0)
		{
			free(environ[i]);
			environ[i] = copy_info(name_env, value);
			free(var_env);
			return;
		}
		free(var_env);
	}

	environ = _reallocdp(environ, i, sizeof(char *) * (i + 2));
	environ[i] = copy_info(name, value);
	environ[i + 1] = NULL;

	, int overwrite
}*/


int set_env(const char *name, const char *value) {
    size_t namelen, valuelen;
    char *envstr;
    int i;

    /* Check for valid arguments */
    if (name == NULL || name[0] == '\0' || strchr(name, '=') != NULL || value == NULL)
        return -1;

    /* Calculate the lengths of the name and value */
    namelen = strlen(name);
    valuelen = strlen(value);

    /* Allocate memory for the environment string */
    envstr = (char*)malloc(namelen + valuelen + 2);
    if (envstr == NULL)
        return -1;

    /* Build the environment string */
    strcpy(envstr, name);
    strcat(envstr, "=");
    strcat(envstr, value);

    /* Search for an existing environment variable with the same name */
    for (i = 0; environ[i] != NULL; i++) {
        if (strncmp(environ[i], name, namelen) == 0 && environ[i][namelen] == '=') {
            /* An existing variable was found 
            if (!overwrite) {
                free(envstr);
                return 0;
            }*/
            /* Overwrite the existing variable */
            environ[i] = envstr;
            return 0;
        }
    }

    /* No existing variable was found, add a new one */
    environ[i] = envstr;
    environ[i+1] = NULL;
    return 0;
}

/**
 * _setenv - compares env variables names
 * with the name passed.
 * @datash: data relevant (env name and env value)
 *
 * Return: 1 on success.
 */
int _setenv(char *argv[])
{

	if (argv[1] == NULL || argv[2] == NULL)
	{
		/*get_error(datash, -1);*/
		return (1);
	}

	set_env(argv[1], argv[2]);

	return (1);
}

/**
 * _unsetenv - deletes a environment variable
 *
 * @datash: data relevant (env name)
 *
 * Return: 1 on success.
 */
int _unsetenv(char *argv[])
{
	char **realloc_environ;
	char *var_env, *name_env;
	int i, j, k;

	if (argv[1] == NULL)
	{
		/*get_error(datash, -1);*/
		return (1);
	}
	k = -1;
	for (i = 0; environ[i]; i++)
	{
		var_env = _strdup(environ[i]);
		name_env = _strtok(var_env, "=");
		if (_strcmp(name_env, argv[1]) == 0)
		{
			k = i;
		}
		free(var_env);
	}
	if (k == -1)
	{
		/*get_error(datash, -1);*/
		return (1);
	}
	realloc_environ = malloc(sizeof(char *) * (i));
	for (i = j = 0; environ[i]; i++)
	{
		if (i != k)
		{
			realloc_environ[j] = environ[i];
			j++;
		}
	}
	realloc_environ[j] = NULL;
	free(environ[k]);
	free(environ);
	environ = realloc_environ;
	return (1);
}
