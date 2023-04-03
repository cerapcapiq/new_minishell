#include "../include/minishell.h"
#include "../include/minishell.h"
#include <sys/stat.h>

int	ft_cmd(char *str, char *lineptr)
{
	char	*cmd;
	char	*argv[] = {lineptr, NULL};
	char	*env[] = {NULL};
	int		status;
	int		pid;

	cmd = str;

	pid = fork();
	if (!pid)
	{
		if (execve(cmd, argv, env) == -1)
			return (-1);
	}
	waitpid(pid, &status, 0);
	return (2);
}

int	getenv_cmd(int argc, char **argv)
{
	char	**split;
	int		i;
	char	*path;

	i = 0;
	split = NULL;
	if (argc < 1)
		return (1);
	path = get_arg_content("PATH");
	split = ft_split(path + 5, ':');
	while (split[i] != NULL)
	{
		split[i] = ft_strjoin(split[i], "/");
		split[i] = ft_strjoin(split[i], argv[0]);
		if (ft_cmd(split[i], *argv) != -1)
		{
			break ;
		}
		i++;
	}
	return (0);
}

/*int	it_works(char *cmd_path)
{
	struct stat	buffer;

	if (stat(cmd_path, &buffer) == 0 && buffer.st_mode & S_IXUSR)
		return (1);
	else
		return (0);
}*/

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
	if (!(path = ft_var_content("PATH", head_ref)))
	{
		printf("no path");
		return (NULL);
	}
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

char	**ft_getenv(void)
{
	char	**s;
	int		i;

	s = environ;
	i = 0;
	while (s[i] != NULL)
	{
		if (it_works(s[i]))
		{
			break ;
		}
		i++;
	}
	return (s);
}

int	ft_ex(char **argv, char **envp, int i)
{
	int	res;	
	int	pid;
   
	pid	= fork();
	if (!pid)
	{
		argv[i] = 0;
		execve(*argv, envp, ft_getenv());
		return (printf("error"));
	}
	if (waitpid(pid, &res, 0) == -1)
		return (printf("error"));
	return (WIFEXITED(res) && WEXITSTATUS(res));
}

int	call_cmd(char **av)
{
	int		i;
	int		j;
	char	*env[4028];

	i = 0;
	j = 0;
	if (ft_strchr(*av, '/'))
	{
		*env = av[0];
		while (av[i++])
		{
			if ((j = ft_ex(env, av, i)) == 0)
				break ;
		}
	}
	else
	{
		*env = ft_getpath(av);
		while (av[i++])
		{
			if ((j = ft_ex(env, av, i)) == 0)
				break ;
		}
	}
	return (j);
}
