/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_executer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 19:06:06 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/13 00:00:53 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	and_executer(t_cmd *cmd, int infile, int outfile, int *fd)
{
	int	ret;

	ret = 0;
	if (((t_and *)cmd)->left && ((t_and *)cmd)->right)
	{
		ret = and_part_executer(((t_and *)cmd)->left, infile, outfile, fd);
		if (ret)
			ret = and_part_executer(((t_and *)cmd)->right, infile, outfile, fd);
	}
	return (ret);
}

int	and_part_executer(t_cmd *cmd, int infile, int outfile, int *fd)
{
	int	ret;

	if (cmd->type == REDIR)
		ret = redirect_executer(cmd, infile, outfile, fd);
	else if (cmd->type == EXEC)
		ret = cmd_executer(cmd, infile, outfile, fd);
	else if (cmd->type == BUILTIN)
		ret = builtin_executer(cmd, infile, outfile, fd);
	else if (cmd->type == AND)
		ret = and_executer(cmd, infile, outfile, fd);
	else if (cmd->type == OR)
		ret = or_executer(cmd, infile, outfile, fd);
	else if (cmd->type == PIPE)
		ret = pipe_executer(cmd, infile, outfile, fd);
	return (ret);
}
