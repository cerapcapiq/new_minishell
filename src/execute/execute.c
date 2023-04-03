#include "../include/minishell.h"

//calls the a propreate function to execute


int	execute(t_mini *mini)
{
	char	**argv;
	t_token	*tok;
	t_token	*command;
	int save_fd[2];

	tok = mini->tokens;
	while (tok)
	{   
		command = tok;
		argv = convert_argv(command);
		tok = tok->next;
		while (tok && tok->type == ARG)
			tok = tok->next;
		//if (tok->type != ARG)
			call_pipe_redirect(mini, command, tok);
		if (command->type == BUILTIN)
			mini->execute_code = execute_builtin(argv, command->str, mini);
		else if (command->type == CMD)
			mini->execute_code = call_cmd(argv);
		else if (command->type == HEREDOC)
			here_doc_input(*argv, save_fd);
		agrv_free(argv);
	}
	return (0);
}