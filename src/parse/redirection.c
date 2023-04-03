#include "../include/minishell.h"

#define _XOPEN_SOURCE 600

#define TMP_FILE	"temporary_file.txt"
# define IN		0
# define OUT	1

void	ft_putendl_fd(char *s, int fd)
{
	if (!s)
		return ;
	if (fd < 0)
		return ;
	ft_putstr_fd(s, fd);
	write(fd, "\n", 1);
}

static int	create_temporary_file(void)
{
	int	fd;

	fd = open(TMP_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd == -1)
		printf("error\n");
	return (fd);
}

static	void	get_and_write_input(int tmp_fd, char *eof)
{
	char	*input;

	while (true)
	{
		input = readline("> ");
		if (!input)
		{
			printf("warning,");
			close(tmp_fd);
			exit(0);
		}
		if (strcmp(input, eof))
			ft_putendl_fd(input, tmp_fd);
		else
		{
			close(tmp_fd);
			free(input);
			break ;
		}
		free(input);
	}
	exit(0);
}

static void	clear_tmp_file_input(void)
{
	int		tmp_fd;

	tmp_fd = open(TMP_FILE, O_WRONLY | O_TRUNC, 0600);
	close(tmp_fd);
}

static void	make_tmp_file_input(void)
{
	int		tmp_fd;

	tmp_fd = open(TMP_FILE, O_RDONLY);
	unlink(TMP_FILE);
	dup2(tmp_fd, IN);
	close(tmp_fd);
}

void	here_doc_input(char *eof, int *save_fd)
{
	int		tmp_fd;
	int		save_fd_out;
	int		pid;
	int		status;

	tmp_fd = create_temporary_file();
	if (tmp_fd == -1)
		return ;
	save_fd_out = dup(OUT);
	dup2(save_fd[OUT], STDOUT_FILENO);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
		get_and_write_input(tmp_fd, eof);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
	{
		clear_tmp_file_input();
	}
	make_tmp_file_input();
	dup2(save_fd_out, STDOUT_FILENO);
	close(save_fd_out);
}

int	redirect_input(t_mini *ms, t_token *token)
{
	if (ms->input != -1)
		close(ms->input);
	ms->input = open(token->str, O_RDONLY, S_IRWXU);
	if (ms->input == -1)
	{
		printf("minishell: %s : No such file or directory\n", token->str);
		return (1);
	}
	dup2(ms->input, STDIN_FILENO);
	return (0);
}

int	redirect_output(t_mini *ms, t_token *token, int type)
{
	if (ms->output != -1)
		close(ms->output);
	if (type == TRUNC)
		ms->output = open(token->str, O_CREAT | O_WRONLY
				| O_TRUNC, S_IRWXU);
	else if (type == APPEND)
		ms->output = open(token->str, O_CREAT | O_WRONLY
				| O_APPEND, S_IRWXU);
	if (ms->output == -1)
	{
		printf("minishell: %s : No such file or directory\n", token->str);
		return (1);
	}
	dup2(ms->output, STDOUT_FILENO);
	return (0);
}