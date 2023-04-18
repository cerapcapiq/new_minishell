/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasarud <abasarud@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:06:26 by abasarud          #+#    #+#             */
/*   Updated: 2023/04/12 13:06:27 by abasarud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//calls the a propreate function to execute

int	execute(t_mini *mini)
{
	char	**argv;
	t_token	*tok;
	t_token	*command;

	tok = mini->tokens;
	while (tok)
	{
		command = tok;
		argv = convert_argv(command);
		tok = tok->next;
		while (tok && tok->type == ARG)
			tok = tok->next;
		call_pipe_redirect(mini, command, tok);
		if (command->type == BUILTIN)
			mini->execute_code = execute_builtin(argv, command->str, mini);
		else if (command->type == CMD)
			mini->execute_code = call_cmd(argv);
		agrv_free(argv);
	}
	return (0);
}
