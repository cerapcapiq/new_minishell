/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_var_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasarud <abasarud@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:03:47 by abasarud          #+#    #+#             */
/*   Updated: 2023/04/18 15:50:45 by abasarud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"

void	show_var(char *lineptr, struct s_node *head)
{
	int				i;
	char			*contact;
	struct s_node	*temp;

	i = 1;
	if (*lineptr == '$')
		lineptr++;
	get_name(lineptr);
	contact = lineptr;
	temp = head;
	while (temp != NULL)
	{
		if (ft_strstr(temp->data, contact))
		{
			printf("$var saved is : %s\n", temp->data);
		}
		temp = temp->nxtpointer;
		i++;
	}
}

char	*ft_var_content(char *lineptr, struct s_node *head)
{
	char			*contact;
	char			*new;
	int				i;
	struct s_node	*temp;

	if (*lineptr == '$')
		lineptr++;
	contact = lineptr;
	new = NULL;
	i = 1;
	temp = head;
	while (temp != NULL)
	{
		if (!ft_strcmp(get_name(temp->data), contact))
		{
			new = get_arg_content(temp->data);
		}
		temp = temp->nxtpointer;
		i++;
	}
	return (new);
}

char	*get_arg_to_del(char *lineptr)
{
	size_t	i;
	char	*interesting_stuff;

	i = 0;
	while (i < strlen(lineptr))
	{
		if (lineptr[i] == ' ')
		{
			interesting_stuff = lineptr + i + 1;
		}
		i++;
	}
	return (interesting_stuff);
}

char	*ft_remove_value(char *str)
{
	char	*ptr;

	ptr = ft_strchr(str, '=');
	if (ptr != NULL)
		*ptr = '\0';
	return (ptr);
}
