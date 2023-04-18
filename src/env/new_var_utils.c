/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_var_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasarud <abasarud@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:05:30 by abasarud          #+#    #+#             */
/*   Updated: 2023/04/18 15:50:45 by abasarud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

struct s_linked	*display_linked_s_node(struct s_linked *head)
{
	struct s_linked	*temp;

	temp = head;
	while (temp != NULL)
	{
		if (temp->next == NULL)
		{
			printf(" %s->NULL\n", temp->data);
		}
		else
		{
			printf("\n%s->", temp->data);
		}
		temp = temp->next;
	}
	return (head);
}

char	*ft_add_var_content(char *lineptr, struct s_linked *head)
{
	char				*contact;
	char				*new;
	int					i;
	struct s_linked		*temp;

	temp = head;
	if (*lineptr == '$')
		lineptr++;
	contact = lineptr;
	new = NULL;
	i = 1;
	while (temp != NULL)
	{
		if (ft_strstr(temp->data, contact))
		{
			new = temp->data;
		}
		temp = temp->next;
		i++;
	}
	return (new);
}

struct s_linked	*ft_create_list(struct s_linked **head, char *str)
{
	char				*s_nodedata;
	struct s_linked		*new;
	struct s_linked		*last;

	new = malloc(sizeof(struct s_linked));
	s_nodedata = str;
	new->data = s_nodedata;
	new->next = NULL;
	if (*head == NULL)
		*head = new;
	else
	{
		last = *head;
		while (last->next != NULL)
		{
			last = last->next;
		}
		last->next = new;
	}
	return (*head);
}
