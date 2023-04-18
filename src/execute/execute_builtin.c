/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasarud <abasarud@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:06:35 by abasarud          #+#    #+#             */
/*   Updated: 2023/04/18 12:20:09 by abasarud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//calls the builtin function for execution

int	call_builtin(char **argv, char *command, t_token token)
{
	int	argc;
	int	builtin_cmd;

	argc = count_argc(argv);
	builtin_cmd = 0;
	if (!ft_strcmp(command, "echo"))
		builtin_cmd = echo(argc, argv, *token.next);
	else if (!ft_strcmp(command, "pwd"))
		builtin_cmd = pwd();
	else if (!ft_strcmp(command, "exit"))
		builtin_cmd = mini_exit();
	return (builtin_cmd);
}

static	void	post_call(char **argv, char *command, t_mini *ms, int exit_code)
{
	int	argc;

	argc = count_argc(argv);
	if (!ft_strcmp(command, "exit"))
		mini_exit();
	if (!ft_strcmp(command, "cd"))
		cd(argc, argv);
	ms->execute_code = exit_code;
}

int	execute_builtin(char **argv, char *command, t_mini *ms)
{
	pid_t	pid;
	int		exit_code;

	pid = fork();
	if (pid != 0)
	{
		if (ms->pipe_read != -1)
		{
			close(ms->pipe_write);
			dup2(ms->pipe_read, STDIN_FILENO);
		}
		waitpid(pid, &exit_code, 0);
		post_call(argv, command, ms, exit_code);
	}
	else
	{
		if (ms->pipe_write != -1)
		{
			close(ms->pipe_read);
			dup2(ms->pipe_write, STDOUT_FILENO);
		}
		exit_code = call_builtin(argv, command, *ms->tokens);
		exit(exit_code);
	}
	return (exit_code);
}
