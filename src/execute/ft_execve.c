/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasarud <abasarud@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:06:29 by abasarud          #+#    #+#             */
/*   Updated: 2023/05/11 12:55:59 by abasarud         ###   ########.fr       */
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

	res = 0;
	pid = fork();
	g_info.g_exit_num = 0;
	if (!pid)
	{
		argv[i] = 0;
		execve(*argv, envp, ft_getenv());
		ft_error_exit(10);
	}
	if (waitpid(pid, &res, 0) == -1)
		ft_error_exit(11);
	wait(&res);
	return (WIFEXITED(res) && WEXITSTATUS(res));
}
*/
int	ft_ex(char **argv, char **envp, int i)
{	
	int	pid;

	pid = fork();
	if (!pid)
	{
		argv[i] = NULL;
		if (execve(*argv, envp, ft_getenv()) == -1)
		{
			g_exit_num = 55;
			exit(1);
		}
	}
	else
	{
		while (waitpid(pid, &g_exit_num, WNOHANG) == 0)
			continue ;
		if (WIFEXITED(g_exit_num))
			return (WEXITSTATUS(g_exit_num));
		else
			return (1);
	}
	return (0);
}

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
