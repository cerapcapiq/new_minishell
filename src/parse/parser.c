/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasarud <abasarud@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:15:41 by abasarud          #+#    #+#             */
/*   Updated: 2023/04/18 14:43:22 by abasarud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 && *s2 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

void	ft_whitespace(char *buff)
{
	while (*buff == ' ' || *buff == '\t')
		buff++;
	if (*buff == '\0')
		mini_exit();
}

void	parse(t_mini *mini, char *buff)
{
	char	**split;
	int		i;
	t_token	*head;
	char	*cpy;

	split = NULL;
	if (buff == NULL)
		exit(0);
	ft_whitespace(buff);
	cpy = ft_strdup(buff);
	ft_linked_list(cpy);
	split = ft_split(buff, ' ');
	head = new_token(mini, *split);
	mini->tokens = head;
	i = 0;
	while (split[++i])
		token_addend(split[i], mini);
	execute(mini);
	mini->cmd = 1;
	token_free(mini->tokens);
	agrv_free(split);
}
