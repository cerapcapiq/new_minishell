/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasarud <abasarud@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:00:06 by abasarud          #+#    #+#             */
/*   Updated: 2023/05/02 12:50:36 by abasarud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"

void	print_echo_args(char **argv, int start)
{
	int	i;

	i = start;
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

#include <stdbool.h>

int has_dollar_sign(const char *str)
{
    const char *ptr = str;
    while (*ptr != '\0')
	{
        if (*ptr == '$')
            return 1;
        ptr++;
    }
    return 0;
}

int	echo(int argc, char **argv, t_token curr)
{
	int	i;
	int	flag;

	if (argc < 2)
		return (1);
	i = 1;
	flag = 0;
	if (argv[i] && ft_strncmp(argv[i], "-n", 2) == 0)
	{
		flag = 1;
		i++;
	}
	if (curr.quote == 2 && ft_dollar(argv[i]))
	{
		argv[i] = ft_delete_quote(argv[i]);
		if (ft_dollar(argv[i]))
			argv[i] = strremove(argv[i], "$");
		show_var(argv[i], head_ref);
		printf("in here\n");
	}
	else if (curr.quote == 0)
	{
		if (ft_dollar(argv[i]))
		{
			argv[i] = strremove(argv[i], "$");
			show_var(argv[i], head_ref);
		}
		else 
			print_echo_args(argv, i);
	}
	else
		print_echo_args(argv, i);
	if (flag == 0)
		printf("\n");
	return (0);
}
