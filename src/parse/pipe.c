/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasarud <abasarud@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:15:45 by abasarud          #+#    #+#             */
/*   Updated: 2023/04/12 13:16:24 by abasarud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	create_pipe(t_mini *mini)
{
	int		fd[2];
	int		status;

	status = pipe(fd);
	if (status < 0)
	{
		mini->pipe_read = -1;
		mini->pipe_write = -1;
		return (0);
	}
	mini->pipe_read = fd[0];
	mini->pipe_write = fd[1];
	return (1);
}
