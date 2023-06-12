/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_executer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 19:05:58 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/12 23:59:37 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	wait_pipe(int pid)
{
	waitpid(pid, NULL, 0);
	while (wait(NULL) != -1)
		;
}

int	pipe_executer(t_cmd *cmd, int infile, int outfile, int *fd)
{
	int	ret;
	int	fds[2];
	int	fds_info[3];

	pipe(fds);
	if (fd && fd[2] == 1)
		close(fd[0]);
	fds_info[0] = fds[0];
	fds_info[1] = fds[1];
	fds_info[2] = 0;
	ret = pipe_part_executer(((t_pipe *)cmd)->left, infile, fds[1], fds_info);
	close(fds[1]);
	fds_info[2] = 1;
	ret = pipe_part_executer(((t_pipe *)cmd)->right, fds[0], outfile, fds_info);
	close(fds[0]);
	if (!((t_pipe *)cmd)->right || ((t_pipe *)cmd)->right->type != PIPE)
		wait_pipe(ret);
	return (ret);
}

int	pipe_part_executer(t_cmd *cmd, int infile, int outfile, int *fd)
{
	int	ret;

	ret = 0;
	if (cmd && cmd->type == REDIR)
		ret = redirect_executer(cmd, infile, outfile, fd);
	else if (cmd && cmd->type == EXEC)
		ret = cmd_executer(cmd, infile, outfile, fd);
	else if (cmd && cmd->type == BUILTIN)
		ret = builtin_executer(cmd, infile, outfile, fd);
	else if (cmd && cmd->type == AND)
		ret = and_executer(cmd, infile, outfile, fd);
	else if (cmd && cmd->type == OR)
		ret = or_executer(cmd, infile, outfile, fd);
	else if (cmd && cmd->type == PIPE)
		ret = pipe_executer(cmd, infile, outfile, fd);
	return (ret);
}
