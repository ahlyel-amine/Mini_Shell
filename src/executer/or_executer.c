/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   or_executer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 19:06:00 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/13 01:20:12 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	or_part_executer(t_cmd *cmd, int infile, int outfile, int *fd)
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

int	or_executer(t_cmd *cmd, int infile, int outfile, int *fd)
{
	int	ret;

	if (((t_and *)cmd)->left && ((t_and *)cmd)->right)
	{
		ret = or_part_executer(((t_or *)cmd)->left, infile, outfile, fd);
		if (!ret)
			ret = or_part_executer(((t_or *)cmd)->right, infile, outfile, fd);
	}
	return (ret);
}

