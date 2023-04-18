/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasarud <abasarud@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:42:25 by abasarud          #+#    #+#             */
/*   Updated: 2023/04/18 15:50:45 by abasarud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"

int	for_env(char *token)
{
	if (ft_strstr(token, "="))
	{
		return (ENV);
		printf("in able env\n");
	}
	return (0);
}

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

int	ft_dollar(char *new)
{
	while (*new != '\0')
	{
		if (*new == '$')
			return (1);
		new++;
	}
	return (0);
}

char	*ft_delete_quote(char *data)
{
	char	*new;

	new = ft_strdup(data);
	new = strremove(new, "\"");
	new = strremove(new, "\'");
	return (new);
}
