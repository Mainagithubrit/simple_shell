#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>


/**
 * struct env_list - singly linked list
 * @str: string - (malloc'ed string)
 * @next: points to the next node
 */
typedef struct env_list
{
	char *str;
	struct env_list *next;
} list_t;

/**
 * struct shell_data - shell data
 * @tokens: number of token in linearg
 * @estatus: exit status
 * @token: tokenize linearg
 * @linearg: User input
 * @envp: enviromental variables
 * @av: argument vectory to main
 */

typedef struct shell_data
{
	unsigned int tokens;
	int estatus;
	char **token;
	char *linearg;
	list_t *envp;
	char **av;
} data_t;


/**** Macros *****/
#define CLEAR {0, 0, NULL, NULL, NULL, NULL}
#define BUFF_SIZE 1024

/**
 * struct cmd_data - command line argument
 * @arg: argument
 * @ptr: pointer to execution function
 */
typedef struct cmd_data
{
	char *arg;
	void (*ptr)(data_t *);
} builtin;


/** Builtin Handlers */
int check_builtin(data_t *data);
void exit_shell(data_t *);
void env(data_t *);
void _setenv(data_t *data);
void _unsetenv(data_t *data);

/****** Environments *******/
void add_node_end(list_t **head, char *str);
void initialize_path(data_t *data, char **envp);
int get_index(char *s);
void free_list(list_t *head);
void new_free(data_t *data);




unsigned int get_tok(char *str);
void tokenize(char *linearg, char **token, int tokens);
void execute(data_t *data, char *path, char**);
char *getpath(data_t);
char *get_cmd(char *path, char *command);
void start_shell(char*[], char *[]);
int is_number(char *s);
char *_strtok(char *str, char *delim);

/***** Print *****/
int perr_str(char *s, char *s2);
int perr_ch(char c);
int p_ch(char c);
int p_str(char *s1, char *s2);



/***** String Fuctions *******/
char *_strcpy(char *dest, char *src);
char *_strcat(char *dest, char *src);
char *_strdup(const char *str);
int _strcmp(char *s1, char *s2);
int _strncmp(const char *str1, const char *str2, size_t n);
size_t _strlen(char *str);
int _atoi(char *s);


/***** Signals *******/
void handle_sigint(__attribute__((unused))int sig);




#endif
