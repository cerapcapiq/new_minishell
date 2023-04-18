/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasarud <abasarud@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:14:36 by abasarud          #+#    #+#             */
/*   Updated: 2023/04/12 13:14:37 by abasarud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	token_free(t_token *tok)
{
	t_token	*temp;

	while (tok)
	{
		temp = tok;
		tok = tok->next;
		free(temp->str);
		free(temp);
		temp = tok;
	}
}

void	agrv_free(char **argv)
{
	int	i;

	i = 0;
	if (argv == NULL)
		return ;
	while (argv[i])
	{
		free(argv[i++]);
	}
	free(argv);
}
