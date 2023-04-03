#include "../include/minishell.h"
#include "../libft/libft.h"

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

int	for_env(char *token)
{
	if (strstr(token, "="))
	{
		return (ENV);
		printf("in able env\n");
	}
	return (0);
}

char	*ft_delete_quote(char *data)
{
	char	*new;
	
	new = ft_strdup(data);
	new = strremove(new, "\"");
	new = strremove(new, "\'");
	return (new);
}

int	ft_single_detect_quote(char *data)
{
	char	*new;
	
	new = data;
	while (*new != '\0')
	{
		if (*new == '\'' || *new != '\"')
		{
			for (int i = 0; i <= 4; i++)
    		{
    			int count = 1;
        		for (int j = i + 1; new[j] != '\0'; j++)
        		{
        			if (new[i] == new[j])
            		{
            			count++;
                		new[j] = -1;
            		}
        		}
			if (count > 1 && new[i] != -1 && new[i] == '\"' && !ft_detect_dollar(new))
       return (1);
		if (count > 1 && new[i] != -1 && new[i] == '\'')
        return (1);

			}
		}
		else
			return (0);
	new++;
	}
	return (0);
}

int	ft_detect_quote(char *data)
{
	char *arg_letters = data;
 	for (int i = 0, j = ft_strlen(arg_letters); i < j; i++)
   {
      for (int k = i+1; k < j; k++)
      {
         if (arg_letters[i] == arg_letters[k])
         {
			 if (arg_letters[i] == '\'' || arg_letters[i] == '\"')
            return (1);
         }

      }
   }
   return (0);
}

int	ft_double_detect_quote(char *data)
{
	char *arg_letters = data;
 	for (int i = 0, j = ft_strlen(arg_letters); i < j; i++)
   {
      for (int k = i+1; k < j; k++)
      {
         if (arg_letters[i] == arg_letters[k])
         {
			 if (arg_letters[i] == '\"')
            return (1);
         }

      }
   }
   return (0);
}

//to get the token types from input
int	token_type(t_mini *mini, char *token)
{
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

//create new token list
t_token	*new_token(t_mini *mini, char *data)
{
	t_token	*res;
	char *new;

	res = (t_token *)malloc(sizeof(t_token));
	if (ft_detect_quote(data))
	{
		new = ft_strdup(data);
		res->str = ft_strdup(new);
		res->type = ARG;
		res->prev = 0;
		res->next = 0;
	}
	else
	{
	res->str = ft_strdup(data);
	res->type = token_type(mini, data);
	res->prev = 0;
	res->next = 0;
	}
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
