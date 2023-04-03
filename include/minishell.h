#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <signal.h>
# include <string.h>
# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include <stdbool.h>
# include "../libft/libft.h"

// Token types
// builtin : builtin cmd: e.g. echo, cd
// cmd: any type of other command
// arg : any type of argument
// input : '<' 
// heredoc : '<<'
// trunc : '>'
// append : '>>'
// pipe : '|'

# define BUILTIN 1
# define CMD 2
# define ARG 3
# define INPUT 4
# define HEREDOC 5
# define TRUNC 6
# define APPEND 7
# define PIPE 8
# define ENV 9

# define PROMPT		0
# define EOT		100

// str - token string
// type - token type
// prev and next - linked list pointers to previous and next token


typedef struct s_token
{
	char			*str;
	int				type;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct s_mini
{
	t_token		*tokens;
	int			cmd;
	int			pipe_read;
	int			pipe_write;
	int			input;
	int			output;
	int			stdin;
	int			stdout;
	int			execute_code;
	t_list		*env;
}	t_mini;

struct node
{
  char *data;
  struct node *nxtpointer;
}*head_ref;

typedef struct LinkedList *node; //Define node as pointer of data type struct LinkedList

struct LinkedList{
    char * data;
    struct LinkedList *next;
 }*head;
//init signals, pipes etc
typedef struct s_global
{
	int		sigint;
	t_mini	*mini;
	int		pipe;
}	t_global;

extern t_global g_global;
extern char **environ;

//parser
char * display_readline(char *input);
int		ft_strcmp(char *s1, char *s2);
void	print_tokens(t_token *tokens);
int		builtin_cmd(char *token);
int		delim_token(char *token);
int		token_type(t_mini *mini, char *token);
t_token	*new_token(t_mini *mini, char *data);
void	token_addend(char *data, t_mini *mini);
int		create_pipe(t_mini *mini);
int		redirect_output(t_mini *ms, t_token *token, int type);
int		redirect_input(t_mini *ms, t_token *token);
void	parse(t_mini *mini, char *buff);
int ft_single_detect_quote(char *data);
int ft_double_detect_quote(char *data);
char   *ft_delete_quote(char *data);
struct node* ft_link_env();
struct node * delete_var(char *lineptr, struct node* head_ref);
char *get_name(char *linestr);
//execute
int		count_argc(char **args);
void	call_pipe_redirect(t_mini *mini, t_token *command, t_token *tok);
void	here_doc_input(char *eof, int *save_fd);
char	**convert_argv(t_token	*tokens);
int		call_builtin(char **argv, char *command);
int		execute_builtin(char **argv, char *command, t_mini *ms);
int		ft_cmd(char *str, char *lineptr);
int		getenv_cmd(int argc, char **argv);
char	*traverse_dir(char *path, char *exe);
int		call_cmd(char **argv);
int		execute(t_mini *mini);
int     ft_clear_data(char *data);
int ft_dollar_sign(char *str);
int ft_detect_dollar(char* s1);

//builtin_commands
int		echo(int argc, char **argv);
int		pwd(void);
int		mini_exit(void);
int		cd(int argc, char **argv);

void ft_unset(char *str);

//int ft_var(char *argv, struct node *head);
struct node * ft_var_main(char *argv, struct node *head);
struct node* create_list(struct node **head_ref, char *lineptr);
struct node* display_node(struct node *head_ref);
int ft_var(char **argv);
void ft_add_back(char *cpy);
void show_var(char *lineptr, struct node *head);
void ft_echo_var(char *str);
int ft_detect_quote(char *data);

 char *ft_var_content(char *lineptr, struct node *head);
char * get_arg_content(char *lineptr);

struct LinkedList* display_linked_node(struct LinkedList *head);
char *ft_add_var_content(char *lineptr, struct LinkedList *head);
struct LinkedList* add_to_var(char *str, struct LinkedList *head);
char *get_the_new_var(char *lineptr, struct LinkedList *head);
char *strremove(char *str, const char *sub);

struct LinkedList* createNode();
struct LinkedList*  addNode(node head, char *value);
void moving_the_node(char *str);


void ft_export(char *str);


//signal
void	define_signal(void);
void 	disable_veof(void);

void ft_linked_list(char *cpy); 

//free
void	token_free(t_token *tok);
void	agrv_free(char **argv);

#endif