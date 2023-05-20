/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasarud <abasarud@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:06:26 by abasarud          #+#    #+#             */
/*   Updated: 2023/05/18 17:00:51 by abasarud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	execute(t_mini *mini)
{
	char	**argv;
	char exitStatus[16];
	t_token	*tok;
	t_token	*command;
	int		i;

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
		{
			i = 0;
			while (argv[i] != NULL)
			{
				if (ft_strstr(argv[i], "$?"))
				{				
					snprintf(exitStatus, sizeof(exitStatus), "%d", g_exit_num);
					argv[i] = exitStatus;
				}
				i++;
			}
			mini->execute_code = call_cmd(argv);
		}
	}
	wait(NULL);
	return (0);
}
