/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasarud <abasarud@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:15:41 by abasarud          #+#    #+#             */
/*   Updated: 2023/05/18 17:04:24 by abasarud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"
#include <histedit.h>
#include <string.h>

char** split_string(const char* string) {
    int max_tokens = 100; // Maximum number of tokens
    int token_count = 0; // Current token count
    char** tokens = malloc(max_tokens * sizeof(char*)); // Array to store tokens
    char* current_word = NULL; // Current token being processed
    int in_quotes = 0; // Flag to indicate if within quotes
    char quote_type = '\0'; // Single or double quote

    if (!tokens) {
        fprintf(stderr, "Memory allocation failed.\n");
        return NULL;
    }

    // Tokenize the string
    while (*string) {
        if ((*string == ' ' && !in_quotes) || *string == '"' || *string == '\'') {
            if (current_word) {
                tokens[token_count++] = current_word;
                current_word = NULL;

                // Resize the tokens array if necessary
                if (token_count >= max_tokens) {
                    max_tokens *= 2;
                    tokens = realloc(tokens, max_tokens * sizeof(char*));
                    if (!tokens) {
                        fprintf(stderr, "Memory reallocation failed.\n");
                        free(current_word);
                        return NULL;
                    }
                }
            }

            if (*string == '"' || *string == '\'') {
                if (in_quotes && quote_type == *string) {
                    in_quotes = 0;
                    quote_type = '\0';
                }
                else if (!in_quotes) {
                    in_quotes = 1;
                    quote_type = *string;
                }
            }
        }
        else {
            if (!current_word) {
                // Allocate memory for the current token
                current_word = malloc(strlen(string) + 1);
                if (!current_word) {
                    fprintf(stderr, "Memory allocation failed.\n");
                    free(tokens);
                    return NULL;
                }
                strcpy(current_word, "");
            }
            size_t length = strlen(current_word);
            current_word = realloc(current_word, (length + 2) * sizeof(char));
            current_word[length] = *string;
            current_word[length + 1] = '\0';
        }

        string++;
    }
    if (current_word) {
        tokens[token_count++] = current_word;
    }
    tokens = realloc(tokens, token_count * sizeof(char*));

    return tokens;
    free(tokens);
}
void free_tokens(char** tokens, int tokenCount) {
    for (int i = 0; i < tokenCount; i++) {
        free(tokens[i]);
    }
    //free(tokens);
}

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
	while (*buff == '\t' || *buff == ' ' )
		buff++;
	if (*buff == '\0')
		exit(0);
}
char* add_spaces_around_pipe(const char* s)
{
    size_t len = ft_strlen(s);
    char* result = malloc(sizeof(char) * (len * 2 + 1));
    if (!result) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        if (s[i] == '|' && ((i > 0 || s[i-1] != ' ') || (i < len - 1 || s[i+1] != ' '))) {
            result[j++] = ' ';
            result[j++] = '|';
            result[j++] = ' ';
        } else {
            result[j++] = s[i];
        }
    }
    result[j] = '\0';

    return result;
}

void exit_status()
{
char decimal_exit_status[20];

    snprintf(decimal_exit_status, sizeof(decimal_exit_status), "%d", g_exit_num);
    char command[256];
    snprintf(command, sizeof(command), "expr %s", decimal_exit_status);
}

void	parse(t_mini *mini, char *buff)
{
	char	**split;
	int		i;
	t_token	*head = NULL;
	char	*cpy = NULL;

	split = NULL;
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
