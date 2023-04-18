/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasarud <abasarud@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:01:05 by abasarud          #+#    #+#             */
/*   Updated: 2023/04/12 13:01:33 by abasarud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

struct s_node	*display_s_node(struct s_node *head_ref)
{
	struct s_node	*temp;

	temp = head_ref;
	while (temp != NULL)
	{
		if (temp->nxtpointer == NULL)
		{
			printf(" %s->NULL\n", temp->data);
		}
		else
		{
			printf("\n%s->", temp->data);
		}
		temp = temp->nxtpointer;
	}
	return (head_ref);
}

char	*get_name(char *linestr)
{
	char	*str;
	char	*cpy;
	int		i;

	str = linestr;
	i = 0;
	while (str[i] != '=')
		i++;
	cpy = ft_substr(str, 0, i);
	return (cpy);
}

void	get_arg(char *lineptr)
{
	char	*str;
	char	*arg;
	char	*after;
	size_t	j;
	size_t	len;

	after = NULL;
	j = 0;
	str = lineptr;
	arg = str;
	if (arg == ft_strchr(str, '='))
	{
		len = ft_strlen (++arg);
		if (len > j - 1)
		{
			printf("error");
		}
		memcpy (after, arg, len + 1);
		printf ("the arg(value) is %s\n", arg);
	}
}

char	*get_arg_content(char *lineptr)
{
	size_t	i;
	char	*interesting_stuff;

	i = 0;
	while (i < strlen(lineptr))
	{
		if (lineptr[i] == '=')
		{
			interesting_stuff = lineptr + i + 2;
		}
		i++;
	}
	return (interesting_stuff);
}

struct s_node	*create_list(struct s_node **head_ref, char *lineptr)
{
	char			*s_nodedata;
	struct s_node	*new;
	struct s_node	*last;

	new = malloc(sizeof(struct s_node));
	s_nodedata = lineptr;
	new->data = s_nodedata;
	new->nxtpointer = NULL;
	if (*head_ref == NULL)
		*head_ref = new;
	else
	{
		last = *head_ref;
		while (last->nxtpointer != NULL)
		{
			last = last->nxtpointer;
		}
		last->nxtpointer = new;
	}
	return (*head_ref);
}
