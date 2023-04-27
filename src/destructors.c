/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destructors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 19:06:01 by aahlyel           #+#    #+#             */
/*   Updated: 2023/04/27 19:42:05 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


void	pipe_destructor(t_cmd *structor)
{
	t_pipe	*pipe;

	pipe = (t_pipe *)structor;
	free (pipe);
}
void	execcmd_destructor(t_cmd *structor)
{
	t_execcmd	*cmd;
	int			i;

	i = 0;
	cmd = (t_execcmd *)structor;
	while (cmd->cmd[i])
		free (cmd->cmd[i++]);
	free (cmd->cmd);
	free (cmd);
}

void	redir_destructor(t_cmd *structor)
{
	t_redir	*redir;

	redir = (t_redir *)structor;
	if (redir->cmd != NULL)
		execcmd_destructor(redir->cmd);
	free (redir);
}

void	and_destructor(t_cmd *structor)
{
	t_and	*and;

	and = (t_and *)structor;
	free (and);
}

void	or_destructor(t_cmd *structor)
{
	t_or	*or;

	or = (t_or *)structor;
	free (or);
}

void	invalid_destructor(t_cmd *structor)
{
	t_invalid	*invalid;
	
	invalid = (t_invalid *)structor;
	free (invalid->str);
	free (invalid);
}

void	builtin_destructor(t_cmd *structor)
{
	t_builtin	*builtin;

	builtin = (t_builtin *)structor;
	free (builtin->cmd);
	free (builtin->builtin);
	free (builtin);
}

void	assignement_destructor(t_cmd *structor)
{
	t_assignement	*assignement;

	assignement = (t_assignement *)structor;
	free (assignement->key);
	free (assignement->value);
	free (assignement);
}