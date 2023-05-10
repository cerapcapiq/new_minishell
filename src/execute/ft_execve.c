/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasarud <abasarud@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:06:29 by abasarud          #+#    #+#             */
/*   Updated: 2023/04/18 13:41:21 by abasarud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/minishell.h"
#include <sys/stat.h>

int	it_works(char *cmd_path)
{
	struct stat	buffer;

	if (stat(cmd_path, &buffer) != 0)
		return (0);
	if ((buffer.st_mode & S_IFMT) == S_IFDIR)
		return (0);
	if ((buffer.st_mode & S_IXUSR))
		return (1);
	return (0);
}

char	*ft_getpath(char **av)
{
	char	**split;
	int		i;
	char	*path;

	i = 0;
	split = NULL;
	path = ft_var_content("PATH", head_ref);
	if (!path)
		return (NULL);
	else
	{
		split = ft_split(path + 5, ':');
		while (split[i] != NULL)
		{
			split[i] = ft_strjoin(split[i], "/");
			split[i] = ft_strjoin(split[i], av[0]);
			if (it_works(split[i]))
			{
				break ;
			}
			i++;
		}
		return (split[i]);
	}
	return (NULL);
}

/*int	ft_ex(char **argv, char **envp, int i)
{
	int	res;	
	int	pid;

	pid = fork();
	if (!pid)
	{
		argv[i] = 0;
		if (execve(*argv, envp, ft_getenv()) == -1)
			perror("error");
	}
	waitpid(pid, &res, 0);
		//return (printf("error"));
	return (WIFEXITED(res) && WEXITSTATUS(res));
}*/


int	ft_ex(char **argv, char **envp, int i)
{
	int	res;	
	int	pid;

	pid = fork();
	if (!pid)
	{
		argv[i] = NULL;
		if (execve(*argv, envp, ft_getenv()) == -1)
		{
			perror("error");
			exit(1);
		}
	}
	else
	{
		while (waitpid(pid, &res, WNOHANG) == 0)
			continue;
		if (WIFEXITED(res))
			return (WEXITSTATUS(res));
		else
			return (1);
	}
	return (0);
}
//In this modified version of ft_ex, the parent process waits for the child process to terminate using a loop that calls waitpid with the WNOHANG option. This ensures that the parent process collects the exit status of the child process as soon as it terminates, preventing the child process from becoming a zombie process. If the child process exits with an error status, the function returns 1 to indicate an error.








int	call_cmd(char **av)
{
	int		i;
	int		j;
	char	*env[4028];

	i = 0;
	j = 0;
	if (ft_strchr(*av, '/'))
		*env = av[0];
	else
		*env = ft_getpath(av);
	while (av[i++])
	{
		j = ft_ex(env, av, i);
		{
			if (j == 0)
				break ;
		}
	}
	return (j);
}
