/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gualee <gualee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:15:41 by abasarud          #+#    #+#             */
/*   Updated: 2023/05/21 19:46:40 by gualee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"
#include <histedit.h>
#include <string.h>

void	free_tokens(char **tokens, int tokenCount)
{
	int	i;

	i = 0;
	while (i < tokenCount)
	{
		free(tokens[i]);
		i++;
	}
	//free(tokens);
}

int	ft_whitespace(char *buff)
{
	while (*buff == '\t' || *buff == ' ' )
		buff++;
	if (*buff == '\0' || ft_strlen(buff) == 0)
		return (1);
	return (0);
}

void	exit_status(void)
{
	char	decimal_exit_status[20];
	char	command[256];

	snprintf(decimal_exit_status, sizeof(decimal_exit_status),
		"%d", g_exit_num);
	snprintf(command, sizeof(command), "expr %s", decimal_exit_status);
}

void	parse(t_mini *mini, char *buff)
{
	char	**split;
	int		i;
	t_token	*head;
	char	*cpy;

	split = NULL;
	head = NULL;
	cpy = NULL;
	if (buff == NULL)
		exit(0);
	buff = add_spaces_around_pipe(buff);
	cpy = ft_strdup(buff);
	ft_linked_list(cpy);
	ft_whitespace(cpy);
	split = ft_split(cpy, ' ');
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