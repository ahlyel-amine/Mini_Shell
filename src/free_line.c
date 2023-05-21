/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 08:35:28 by aahlyel           #+#    #+#             */
/*   Updated: 2023/05/21 22:25:45 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	free_rest_of_line(t_cmd *cmd)
{
	if (cmd->type == REDIR)
		redir_destructor(cmd);
	else if (cmd->type == EXEC)
		execcmd_destructor(cmd);
	else if (cmd->type == BUILTIN)
		builtin_destructor(cmd);
	else if (cmd->type == ASSIGNEMENT)
		assignement_destructor(cmd);
	else if (cmd->type == INVALID)
		invalid_destructor(cmd);
}

void	free_line(t_cmd *cmd)
{
	if (cmd->type == AND)
	{
		if (((t_and *)cmd)->left)
			free_line(((t_and *)cmd)->left);
		if (((t_and *)cmd)->right)
			free_line(((t_and *)cmd)->right);
		and_destructor(cmd);
	}
	else if (cmd->type == OR)
	{
		if (((t_or *)cmd)->left)
			free_line(((t_or *)cmd)->left);
		if (((t_or *)cmd)->right)
			free_line(((t_or *)cmd)->right);
		or_destructor(cmd);
	}
	else if (cmd->type == PIPE)
	{
		if (((t_pipe *)cmd)->left)
			free_line(((t_pipe *)cmd)->left);
		if (((t_pipe *)cmd)->right)
			free_line(((t_pipe *)cmd)->right);
		pipe_destructor(cmd);
	}
	else
		free_rest_of_line(cmd);
}
