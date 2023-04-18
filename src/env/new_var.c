/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasarud <abasarud@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:01:01 by abasarud          #+#    #+#             */
/*   Updated: 2023/04/18 15:50:45 by abasarud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_the_new_var(char *lineptr, struct s_linked *head)
{
	int					i;
	char				*search;
	struct s_linked		*temp;

	i = 1;
	lineptr = ft_delete_quote(lineptr);
	if (*lineptr == '$')
		lineptr++;
	search = lineptr;
	temp = head;
	while (temp != NULL)
	{
		if (ft_strstr(temp->data, search))
		{
			printf("$var saved is : %s\n", temp->data);
			return (temp->data);
		}
		temp = temp->next;
		i++;
	}
	return (NULL);
}

struct s_linked	*ft_pass_content(char *cpy, struct s_linked *head)
{
	head = ft_create_list(&head, cpy);
	return (head);
}

struct s_linked	*add_to_var(char *str, struct s_linked *head)
{
	head = ft_pass_content(str, head);
	return (head);
}
