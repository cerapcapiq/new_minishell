/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasarud <abasarud@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 12:48:55 by abasarud          #+#    #+#             */
/*   Updated: 2023/04/18 15:53:38 by abasarud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	int				quote;
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

struct s_node
{
	char			*data;
	struct s_node	*nxtpointer;
}*head_ref;

struct s_linked
{
	char			*data;
	struct s_linked	*next;
}*head;
//init signals, pipes etc

extern char	**environ;

//parser
char			*display_readline(char *input);
int				ft_strcmp(char *s1, char *s2);
void			print_tokens(t_token *tokens);
int				builtin_cmd(char *token);
int				delim_token(char *token);
int				token_type(t_mini *mini, char *token);
t_token			*new_token(t_mini *mini, char *data);
void			token_addend(char *data, t_mini *mini);
int				create_pipe(t_mini *mini);
int				redirect_output(t_mini *ms, t_token *token, int type);
int				redirect_input(t_mini *ms, t_token *token);
void			parse(t_mini *mini, char *buff);
char			*ft_strstr(char *str, const char *to_find);

struct s_node	*ft_link_env(void);
struct s_node	*delete_var(char *lineptr, struct s_node *head_ref);

//execue
int				count_argc(char **args);
void			call_pipe_redirect(t_mini *mini, t_token *command,
					t_token *tok);
void			here_doc_input(t_token *command, int pid);
char			**convert_argv(t_token	*tokens);

int				call_builtin(char **argv, char *command, t_token token);
int				execute_builtin(char **argv, char *command, t_mini *ms);
int				ft_cmd(char *str, char *lineptr);
int				getenv_cmd(int argc, char **argv);
char			*traverse_dir(char *path, char *exe);
int				call_cmd(char **argv);
int				execute(t_mini *mini);
int				ft_clear_data(char *data);
int				it_works(char *cmd_path);
void			check_heredoc(char **argv);
int				ft_ex(char **argv, char **envp, int i);

//builtin_commands
int				echo(int argc, char **argv, t_token curr);
int				pwd(void);
int				mini_exit(void);
int				cd(int argc, char **argv);
void			ft_home_dir(void);
void			ft_prev_dir(char *path);
void			ft_unset(char *str);
void			ft_export(char *str);

//int ft_var(char *argv, struct s_node *head);

void			ft_linked_list(char *cpy);
char			**ft_getenv(void);
int				for_env(char *token);
char			*get_name(char *linestr);

int				ft_var(char **argv);
void			ft_add_back(char *cpy);
void			show_var(char *lineptr, struct s_node *head);
char			*ft_var_content(char *lineptr, struct s_node *head);
char			*get_arg_content(char *lineptr);
char			*ft_add_var_content(char *lineptr, struct s_linked *head);

char			*get_the_new_var(char *lineptr, struct s_linked *head);
char			*strremove(char *str, const char *sub);
void			moving_the_s_node(char *str);

struct s_node	*ft_var_main(char *argv, struct s_node *head);
struct s_node	*create_list(struct s_node **head_ref, char *lineptr);
struct s_linked	*ft_create_list(struct s_linked **head, char *str);
struct s_node	*display_s_node(struct s_node *head_ref);
struct s_linked	*creates_node(void);
struct s_linked	*adds_node(struct s_node head, char *value);
struct s_linked	*add_to_var(char *str, struct s_linked *head);
struct s_linked	*display_linked_s_node(struct s_linked *head);

//quote
int				ft_detect_quote(char *data);
int				closed_dub_quote(char *line);
int				ft_dollar(char *new);
int				detect_q(char *data);
int				ft_detect_dollar(char	*s1);
char			*ft_delete_quote(char *data);
int				closed_quote(char *line);
int				ft_dollar_sign(char *str);
int				ft_double_detect_quote(char *data);

//signal
void			define_signal(void);
void			disable_veof(void);

//free
void			token_free(t_token *tok);
void			agrv_free(char **argv);

#endif
