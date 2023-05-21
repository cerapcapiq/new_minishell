/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gualee <gualee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:15:45 by abasarud          #+#    #+#             */
/*   Updated: 2023/05/21 18:25:18 by gualee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	create_pipe(t_mini *mini)
{
	int		fd[2];
	int		status;

	status = pipe(fd);
	if (status < 0)
	{
		mini->pipe_read = -1;
		mini->pipe_write = -1;
		return (0);
	}
	mini->pipe_read = fd[0];
	mini->pipe_write = fd[1];
	return (1);
}

char	*add_spaces_around_pipe(const char *s)
{
	char	*result;
	size_t	len;
	size_t	j;
	size_t	i;

	len = ft_strlen(s);
	result = malloc(sizeof(char) * (len * 2 + 1));
	if (!result)
		return (NULL);
	j = 0;
	i = 0;
	while (i < len)
	{
		handle_pipe_character(s, i, &result, &j);
		i++;
	}
	result[j] = '\0';
	return (result);
}

void	handle_pipe_character(const char *s, size_t i, char **result, size_t *j)
{
	if (s[i] == '|' && ((*j) == 0 || (*result)[(*j) - 1] != ' ')
		&& (s[i + 1] != ' ' && s[i + 1] != '\0'))
	{
		(*result)[(*j)++] = ' ';
		(*result)[(*j)++] = '|';
		(*result)[(*j)++] = ' ';
	}
	else if (s[i] == '|' && ((*j) == 0 || (*result)[(*j) - 1] != ' '))
	{
		(*result)[(*j)++] = ' ';
		(*result)[(*j)++] = '|';
	}
	else if (s[i] == '|' && (s[i + 1] != ' ' && s[i + 1] != '\0'))
	{
		(*result)[(*j)++] = '|';
		(*result)[(*j)++] = ' ';
	}
	else
	{
		(*result)[(*j)++] = s[i];
	}
}