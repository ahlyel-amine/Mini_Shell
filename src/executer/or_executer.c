/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   or_executer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 19:06:00 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/06 09:36:06 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	or_executer(t_cmd *cmd, int infile, int outfile, int is_pipe)
{
	int	ret;

	if (((t_and *)cmd)->left && ((t_and *)cmd)->right)
	{
		ret = or_part_executer(((t_or *)cmd)->left, infile, outfile, is_pipe);
		if (!ret)
			ret = or_part_executer(((t_or *)cmd)->right, infile, outfile, is_pipe);
	}
	return (ret);
}

int	or_part_executer(t_cmd *cmd, int infile, int outfile, int is_pipe)
{
	int	ret;

	if (cmd->type == REDIR)
		ret = redirect_executer(cmd, infile, outfile, is_pipe);
	else if (cmd->type == EXEC)
		ret = cmd_executer(cmd, infile, outfile, is_pipe);
	else if (cmd->type == BUILTIN)
		ret = builtin_executer(cmd, infile, outfile, is_pipe);
	else if (cmd->type == AND)
		ret = and_executer(cmd, infile, outfile, is_pipe);
	else if (cmd->type == OR)
		ret = or_executer(cmd, infile, outfile, is_pipe);
	else if (cmd->type == PIPE)
		ret = pipe_executer(cmd, infile, outfile, is_pipe);
	return (ret);
}