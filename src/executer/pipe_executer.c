/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_executer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 19:05:58 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/06 14:40:19 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

typedef struct s_pid
{
	int				pid;
	struct s_pid	*next;
}	t_pid;

void	new_pid(t_pid **list, int pid)
{
	t_pid	*new;
	t_pid	*tmp;

	new = malloc(sizeof(t_pid));
	if (!new)
		return ;
	ft_memset(new, 0, sizeof(t_pid));
	new->pid = pid;
	if (!*list)
	{
		*list = new;
		return ;
	}
	tmp = *list;
	while ((*list)->next)
		(*list) = (*list)->next;
	(*list)->next = new;
	*list = tmp;
}

void	wait_pipes(t_pid **list)
{
	t_pid	*tmp;

	while ((*list)->next)
	{
		tmp = *list;
		(*list) = (*list)->next;
		free(tmp);
	}
	if (waitpid((*list)->pid, NULL, 0) == -1)
		return (perror("waitpid failed"));
	free(*list);
	(*list) = NULL;
	while (wait(NULL) != -1)
		;
}

void	take_pipe(int pid, int call_wait)
{
	static t_pid	*pids; 

	if (!call_wait)
		new_pid(&pids, pid);
	else
		wait_pipes(&pids);
}

int	pipe_executer(t_cmd *cmd, int infile, int outfile, int *fd)
{
	int	ret;
	int	fds[2];
	int fds_info[3];

	pipe(fds);
	if (fd && fd[2] == 1)
		close(fd[0]);
	fds_info[0] = fds[0];
	fds_info[1] = fds[1];
	fds_info[2] = 0;
	ret = pipe_part_executer(((t_pipe *)cmd)->left, infile, fds[1], fds_info);
	close(fds[1]);
	take_pipe(ret, 0);
	fds_info[2] = 1;
	ret = pipe_part_executer(((t_pipe *)cmd)->right, fds[0], outfile, fds_info);
	close(fds[0]);
	if (!((t_pipe *)cmd)->right || ((t_pipe *)cmd)->right->type != PIPE){
		take_pipe(ret, 0);
		take_pipe(0, 1);
	}
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

