/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasarud <abasarud@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:00:59 by abasarud          #+#    #+#             */
/*   Updated: 2023/04/27 12:29:22 by abasarud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"
#define J 100000000

struct s_node	*del_path(char *now)
{
	char	**s;
	int		i;
	size_t	len;

	i = 0;
	s = &now;
	while (s[i])
	{
		if (ft_strstr(s[i], "PATH"))
		{
			len = ft_strlen(s[i]);
			ft_memcpy(s[i], now, len);
			printf("%s\n [%d] \n", s[i], i);
		}
		i++;
	}
	return (head_ref);
}

void	ft_add_back(char *cpy)
{
	struct s_node	*fs_node;
	struct s_node	*tmp;

	fs_node = (struct s_node *)malloc(sizeof(struct s_node));
	if (fs_node == NULL)
	{
		printf(" Memory can not be allocated.");
	}
	else
	{
		fs_node->data = cpy;
		fs_node->nxtpointer = NULL;
		tmp = head_ref;
		while (tmp->nxtpointer != NULL)
			tmp = tmp->nxtpointer;
		tmp->nxtpointer = fs_node;
	}
}

void	ft_linked_list(char *cpy)
{
	if (ft_strchr(cpy, '$') && !ft_strstr(cpy, "export $")
		&& !ft_strstr(cpy, "export \"$"))
		show_var(cpy, head_ref);
	else if (ft_strchr(cpy, '=') && !ft_detect_quote(cpy)
		&& !ft_strstr(cpy, "export ") && !ft_strstr(cpy, "unset "))
	{
		head = add_to_var(cpy, head);
		display_linked_s_node(head);
	}
	else if (ft_strstr(cpy, "export "))
		ft_export(cpy);
	ft_unset(cpy);
}
