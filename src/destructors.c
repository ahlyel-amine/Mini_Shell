/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destructors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 19:06:01 by aahlyel           #+#    #+#             */
/*   Updated: 2023/05/12 20:29:06 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


void	pipe_destructor(t_cmd *structor)
{
	t_pipe	*pipe;
printf("destructor pipe called \n");
	pipe = (t_pipe *)structor;
	free (pipe);
}
void	execcmd_destructor(t_cmd *structor)
{
	t_arguments	*args;
	t_arguments	*tmp;
	t_execcmd	*cmd;

	printf("destructor execcmd called \n");
	cmd = (t_execcmd *)structor;
	args = cmd->arguments;
	tmp = cmd->arguments;
	while (args)
	{
		tmp = args;
		args = args->next;
		free (tmp->str);
		free(tmp);
	}
	free (cmd);
}

void	redir_destructor(t_cmd *structor)
{
	t_redir	*redir;
	t_arguments	*args;
	t_arguments	*tmp;

	printf("destructor redir called \n");
	redir = (t_redir *)structor;
	if (redir->cmd != NULL && redir->cmd->type == EXEC)
		execcmd_destructor(redir->cmd);
	else if (redir->cmd != NULL && redir->cmd->type == BUILTIN)
		builtin_destructor(redir->cmd);
	else if (redir->cmd != NULL && redir->cmd->type == INVALID)
		invalid_destructor(redir->cmd);
	else if (redir->cmd != NULL && redir->cmd->type == REDIR)
		redir_destructor(redir->cmd);
	else if (redir->cmd != NULL && redir->cmd->type == AND)
		free_line(redir->cmd);
	else if (redir->cmd != NULL && redir->cmd->type == OR)
		free_line(redir->cmd);
	else if (redir->cmd != NULL && redir->cmd->type == PIPE)
		free_line(redir->cmd);
	args = redir->red.file_name;
	tmp = redir->red.file_name;
	while (args)
	{
		tmp = args;
		args = args->next;
		free (tmp->str);
		free(tmp);
	}
	free (redir);
}

void	and_destructor(t_cmd *structor)
{
	t_and	*and;
printf("destructor and called \n");
	and = (t_and *)structor;
	free (and);
}

void	or_destructor(t_cmd *structor)
{
	t_or	*or;
printf("destructor or called \n");
	or = (t_or *)structor;
	free (or);
}

void	invalid_destructor(t_cmd *structor)
{
	t_invalid	*invalid;
	printf("destructor invalid called \n ");
	invalid = (t_invalid *)structor;
	free (invalid->str);
	free (invalid);
}

void	builtin_destructor(t_cmd *structor)
{
	t_builtin	*builtin;
	t_arguments	*args;
	t_arguments	*tmp;

	printf("destructor builtin called \n");
	builtin = (t_builtin *)structor;
	args = builtin->arguments;
	tmp = builtin->arguments;
	while (args)
	{
		tmp = args;
		args = args->next;
		free (tmp->str);
		free(tmp);
	}
	free (builtin->builtin);
	free (builtin);
}

void	assignement_destructor(t_cmd *structor)
{
	t_assignement	*assignement;
printf("destructor assignement called \n");
	assignement = (t_assignement *)structor;
	free (assignement->key);
	free (assignement->value);
	free (assignement);
}