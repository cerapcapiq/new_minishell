/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasarud <abasarud@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 12:58:39 by abasarud          #+#    #+#             */
/*   Updated: 2023/04/18 15:55:10 by abasarud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_strstr(char *str, const char *to_find)
{
	int	i;
	int	j;

	i = 0;
	if (to_find[0] == '\0')
		return (str);
	while (str[i] != '\0')
	{
		j = 0;
		while (str[i + j] != '\0' && str[i + j] == to_find[j])
		{
			if (to_find[j + 1] == '\0')
				return (&str[i]);
			++j;
		}
		++i;
	}
	return (0);
}

void	ft_export(char *str)
{
	if (ft_strstr(str, "export $") || ft_strstr(str, "export ")
		|| ft_strstr(str, "export \"$"))
	{
		str = strremove(str, "export ");
		str = get_the_new_var(str, head);
		if (str != NULL)
			ft_add_back(str);
		else
			printf("non exisxtent");
	}
	else if (!ft_strcmp(str, "export"))
		display_s_node(head_ref);
}

void	ft_unset(char *str)
{
	if (ft_strstr(str, "unset $") || ft_strstr(str, "unset ")
		|| ft_strstr(str, "unset \"$"))
	{
		str = strremove(str, "unset ");
		delete_var(str, head_ref);
	}
	else
		return ;
}
