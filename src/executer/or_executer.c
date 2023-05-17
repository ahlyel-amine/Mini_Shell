/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   or_executer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 19:06:00 by aahlyel           #+#    #+#             */
/*   Updated: 2023/05/16 20:11:14 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	or_executer(t_cmd *cmd, int infile, int outfile, int fds[3])
{
	int	ret;

	if (((t_and *)cmd)->left && ((t_and *)cmd)->right)
	{
		ret = or_part_executer(((t_or *)cmd)->left, infile, outfile,  fds);
		if (!ret)
			ret = or_part_executer(((t_or *)cmd)->right, infile, outfile,  fds);
	}
	return (ret);
}

int	or_part_executer(t_cmd *cmd, int infile, int outfile, int fds[3])
{
	int	ret;

	if (cmd->type == REDIR)
		ret = redirect_executer(cmd, infile, outfile,  fds);
	else if (cmd->type == EXEC)
		ret = cmd_executer(cmd, infile, outfile,  fds);
	else if (cmd->type == BUILTIN)
		ret = builtin_executer(cmd, infile, outfile,  fds);
	else if (cmd->type == AND)
		ret = and_executer(cmd, infile, outfile,  fds);
	else if (cmd->type == OR)
		ret = or_executer(cmd, infile, outfile,  fds);
	else if (cmd->type == PIPE)
		ret = pipe_executer(cmd, infile, outfile,  fds);
	return (ret);
}