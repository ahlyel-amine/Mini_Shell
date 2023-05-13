/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_executer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 19:05:58 by aahlyel           #+#    #+#             */
/*   Updated: 2023/05/13 10:10:00 by aahlyel          ###   ########.fr       */
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
	ret = pipe_part_executer(((t_pipe *)cmd)->right, fd[0], outfile);
	close(fd[0]);
	return (ret);
}

int	pipe_part_executer(t_cmd *cmd, int infile, int outfile)
{
	int	ret;

	ret = 0;
	if (cmd && cmd->type == REDIR)
		ret = redirect_executer(cmd, infile, outfile);
	else if (cmd && cmd->type == EXEC)
		ret = cmd_executer(cmd, infile, outfile);
	else if (cmd && cmd->type == BUILTIN)
		ret = builtin_executer(cmd, infile, outfile);
	else if (cmd && cmd->type == AND)
		ret = and_executer(cmd, infile, outfile);
	else if (cmd && cmd->type == OR)
		ret = or_executer(cmd, infile, outfile);
	else if (cmd && cmd->type == PIPE)
		ret = pipe_executer(cmd, infile, outfile);
	return (ret);
}