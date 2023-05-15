/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_executer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 19:05:58 by aahlyel           #+#    #+#             */
/*   Updated: 2023/05/15 16:07:55 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	pipe_executer(t_cmd *cmd, int infile, int outfile, int is_pipe)
{
	int	ret;
	int	fd[2];

	is_pipe = 1;
	pipe(fd);
	ret = pipe_part_executer(((t_pipe *)cmd)->left, infile, fd[1], is_pipe);
	close(fd[1]);
	if (((t_pipe *)cmd)->right->type != PIPE)
		is_pipe = 0;
	ret = pipe_part_executer(((t_pipe *)cmd)->right, fd[0], outfile, is_pipe);
	while (wait(NULL) != -1)
		puts("waiting...");
	close(fd[0]);
	return (ret);
}

int	pipe_part_executer(t_cmd *cmd, int infile, int outfile, int is_pipe)
{
	int	ret;

	ret = 0;
	if (cmd && cmd->type == REDIR)
		ret = redirect_executer(cmd, infile, outfile, is_pipe);
	else if (cmd && cmd->type == EXEC)
		ret = cmd_executer(cmd, infile, outfile, is_pipe);
	else if (cmd && cmd->type == BUILTIN)
		ret = builtin_executer(cmd, infile, outfile, is_pipe);
	else if (cmd && cmd->type == AND)
		ret = and_executer(cmd, infile, outfile, is_pipe);
	else if (cmd && cmd->type == OR)
		ret = or_executer(cmd, infile, outfile, is_pipe);
	else if (cmd && cmd->type == PIPE)
		ret = pipe_executer(cmd, infile, outfile, is_pipe);
	return (ret);
}