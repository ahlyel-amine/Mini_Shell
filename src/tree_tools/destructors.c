/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destructors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 19:06:01 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/13 14:12:19 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	pipe_destructor(t_cmd *structor)
{
	t_pipe	*pipe;

	pipe = (t_pipe *)structor;
	free(pipe);
}

void	execcmd_destructor(t_cmd *structor)
{
	t_arguments	*args;
	t_arguments	*tmp;
	t_execcmd	*cmd;

	cmd = (t_execcmd *)structor;
	arguments_destructor(&cmd->cmd);
	arguments_destructor(&cmd->options);
	free(cmd);
}

static void	call_subcmd_destructor(t_cmd *cmd)
{
	if (cmd->type == EXEC)
		execcmd_destructor(cmd);
	else if (cmd->type == BUILTIN)
		builtin_destructor(cmd);
	else if (cmd->type == INVALID)
		invalid_destructor(cmd);
	else if (cmd->type == REDIR)
		redir_destructor(cmd);
	else if (cmd->type == AND)
		free_line(cmd);
	else if (cmd->type == OR)
		free_line(cmd);
	else if (cmd->type == PIPE)
		free_line(cmd);
}

void	redir_destructor(t_cmd *structor)
{
	t_redir		*redir;
	t_arguments	*args;
	t_arguments	*tmp;

	redir = (t_redir *)structor;
	if (redir->cmd)
		call_subcmd_destructor(redir->cmd);
	args = redir->red.file_name;
	while (args)
	{
		tmp = args;
		args = args->next;
		free(tmp->str);
		free(tmp);
	}
	free(redir);
}
