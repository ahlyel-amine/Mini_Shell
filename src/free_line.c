/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 08:35:28 by aahlyel           #+#    #+#             */
/*   Updated: 2023/04/29 11:11:06 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	free_rest_of_line(t_cmd *cmd)
{
	if (cmd->type == REDIR)
		redir_destructor(cmd);
	else if (cmd->type == EXEC)
		execcmd_destructor(cmd);
	else if (cmd->type == ASSIGNEMENT)
		assignement_destructor(cmd);
	else if (cmd->type == BUILTIN)
		builtin_destructor(cmd);
	else if (cmd->type == INVALID)
		invalid_destructor(cmd);
}

void	free_line(t_cmd *cmd)
{
	if (cmd->type == AND)
	{
		free_line(((t_and *)cmd)->left);
		free_line(((t_and *)cmd)->right);
		and_destructor(cmd);
	}
	else if (cmd->type == OR)
	{
		free_line(((t_or *)cmd)->left);
		free_line(((t_or *)cmd)->right);
		or_destructor(cmd);
	}
	else if (cmd->type == PIPE)
	{
		free_line(((t_pipe *)cmd)->left);
		free_line(((t_pipe *)cmd)->right);
		pipe_destructor(cmd);
	}
	else
		free_rest_of_line(cmd);
}