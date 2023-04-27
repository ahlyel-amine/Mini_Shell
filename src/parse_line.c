/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 02:53:32 by aahlyel           #+#    #+#             */
/*   Updated: 2023/04/27 20:14:27 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	redirection_free(t_cmd *cmd)
{
	if (cmd->type == REDIR)
		redir_destructor(cmd);
	else if (cmd->type == EXEC)
		execcmd_destructor(cmd);
	else if (cmd->type == ASSIGNEMENT)
		assignement_destructor(cmd);
	else if (cmd->type == INVALID)
		invalid_destructor(cmd);
}

void	operatores_free(t_cmd *cmd)
{
	if (cmd->type == AND)
	{
		operatores_free(((t_and *)cmd)->left);
		operatores_free(((t_and *)cmd)->right);
		and_destructor(cmd);
	}
	else if (cmd->type == OR)
	{
		operatores_free(((t_or *)cmd)->left);
		operatores_free(((t_or *)cmd)->right);
		or_destructor(cmd);
	}
	else if (cmd->type == PIPE)
	{
		operatores_free(((t_pipe *)cmd)->left);
		operatores_free(((t_pipe *)cmd)->right);
		pipe_destructor(cmd);
	}
	else
		redirection_free(cmd);
}

char	*parse_line(char *line)
{
	t_cmd	*cmd;
	// t_cmd	*left;
	// t_cmd	*right;

	cmd = NULL;
	complete_line(&line);
	if (line)
		cmd = tokenize_line(line);
	operatores_free(cmd);
	return (line);
}
