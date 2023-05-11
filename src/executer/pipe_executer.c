/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_executer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 19:05:58 by aahlyel           #+#    #+#             */
/*   Updated: 2023/05/10 23:58:13 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	pipe_executer(t_cmd *cmd, int infile, int outfile)
{
	int	ret;
	int	fd[2];
	pipe(fd);
	ret = pipe_part_executer(((t_pipe *)cmd)->left, infile, fd[1]);
	close(fd[1]);
	if (ret)
		ret = pipe_part_executer(((t_pipe *)cmd)->right, fd[0], outfile);
	close(fd[0]);
	return (ret);
}

int	pipe_part_executer(t_cmd *cmd, int infile, int outfile)
{
	int	ret;

	if (cmd->type == REDIR)
		ret = redirect_executer(cmd, infile, outfile);
	else if (cmd->type == EXEC)
		ret = cmd_executer(cmd, infile, outfile);
	else if (cmd->type == BUILTIN)
		ret = builtin_executer(cmd, infile, outfile);
	else if (cmd->type == AND)
		ret = and_executer(cmd, infile, outfile);
	else if (cmd->type == OR)
		ret = or_executer(cmd, infile, outfile);
	else if (cmd->type == PIPE)
		ret = pipe_executer(cmd, infile, outfile);
	return (ret);
}