#include "../include/minishell.h"
#include "../libft/libft.h"

int	ft_detect_dollar(char	*s1)
{
	int	i;
   
	i = 0;
	while (s1[i])
	{
		if (s1[i] == '$')
			return (1);
		i++;
    }
    return (0);
}

int	detect_q(char *data)
{
	char *arg_letters;
	
	arg_letters	= data;
 	for (int i = 0, j = ft_strlen(arg_letters); i < j; i++)
	{
		for (int k = i+1; k < j; k++)
		{
			if (arg_letters[i] == arg_letters[k])
			{
				if (arg_letters[i] == '\'')
					return (1);
			}
		}
	}
	return (0);
}

int	closed_quote(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'')
		{
			while (line[i] != '\0')
			{
				if (line[i] == '\'')
				{
					return (1);
					break ;
				}
				i++;
			}
		}
		i++;
	}
	return (0);
}

int	closed_dub_quote(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\"')
		{
			while (line[i] != '\0')
			{
				if (line[i] == '\"')
				{
					return (1);
					break ;
				}
				i++;
			}
		}
		i++;
	}
	return (0);
}

int	echo(int argc, char **argv)
{
	int	i;
	int	flag;

	if (argc < 2)
		return (1);
	i = 1;
	flag = 0;
	if (argv[i] && strncmp(argv[i], "-n", 2) == 0)
	{
		flag = 1;
		i++;
	}
	if (ft_detect_dollar(argv[i]) && !detect_q(argv[i]))
	{
		argv[i] = ft_delete_quote(argv[i]);
		show_var(argv[i], head_ref);
	}
	else
	{
		while (argv[i])
		{
			if (closed_quote(argv[i]) || closed_dub_quote(argv[i]))
				argv[i] = ft_delete_quote(argv[i]);
			printf("%s", argv[i]);
			if (argv[i + 1])
				printf(" ");
			i++;
		}
	}
	if (flag == 0)
		printf("\n");
	return (0);
}
