/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasarud <abasarud@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:15:54 by abasarud          #+#    #+#             */
/*   Updated: 2023/05/18 17:03:52 by abasarud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"

//int g_exit_num = 0;

//get builtin command
int	builtin_cmd(char *token)
{
	if (!ft_strcmp(token, "echo")
		|| !ft_strcmp(token, "cd")
		|| !ft_strcmp(token, "pwd")
		|| !ft_strcmp(token, "export")
		|| !ft_strcmp(token, "unset")
		|| !ft_strcmp(token, "env")
		|| !ft_strcmp(token, "exit")
		|| !ft_strcmp(token, "history"))
		return (1);
	return (0);
}

//to detect delimiter tokens
int	delim_token(char *token)
{
	if (!ft_strcmp(token, ">"))
		return (TRUNC);
	if (!ft_strcmp(token, ">>"))
		return (APPEND);
	if (!ft_strcmp(token, "<"))
		return (INPUT);
	if (!ft_strcmp(token, "<<"))
		return (HEREDOC);
	if (!ft_strcmp(token, "|"))
		return (PIPE);
	return (0);
}

int	token_type(t_mini *mini, char *token)
{
	char	command[256];

	if (!ft_strcmp(token, "$?"))
	{
		snprintf(command, sizeof(command), "%d", g_exit_num);
		token = command;
		return (ARG);
	}
	if (delim_token(token))
	{
		mini->cmd = 1;
		return (delim_token(token));
	}
	if (!mini->cmd)
		return (ARG);
	else
	{
		mini->cmd = 0;
		if (for_env(token))
			return (ENV);
		else if (builtin_cmd(token))
			return (BUILTIN);
		else
			return (CMD);
	}
	return (0);
}

t_token	*new_token(t_mini *mini, char *data)
{
	t_token	*res;
	char	*new;
	int		quote_type;

	quote_type = 0;
	res = (t_token *)malloc(sizeof(t_token));
	if (detect_q(data))
		quote_type = 1;
	else if (ft_double_detect_quote(data))
		quote_type = 2;
	if (quote_type)
		new = ft_delete_quote(data);
	else
		new = ft_strdup(data);
	if (quote_type != 0)
		res->type = ARG;
	else
		res->type = token_type(mini, data);
	res->str = ft_strdup(new);
	res->prev = 0;
	res->next = 0;
	res->quote = quote_type;
	return (res);
}

//addes a token to the end of the list
void	token_addend(char *data, t_mini *mini)
{
	t_token	*tok;
	t_token	*temp;

	tok = mini->tokens;
	while (tok->next)
		tok = tok->next;
	temp = new_token(mini, data);
	tok->next = temp;
	tok->next->prev = tok;
}
