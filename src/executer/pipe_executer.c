/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_executer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 19:05:58 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/06 09:54:45 by aahlyel          ###   ########.fr       */
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
	int i;

	i = 0;
	while (*list)
	{
		i++;
		tmp = *list;
		printf("%dth-cmd pid [%d]\n", i, (*list)->pid);
		if (waitpid((*list)->pid, NULL, 0) == -1)
			perror("waitpid failed");
		printf("has been waited successfully\n\n");
		*list = (*list)->next;
		free(tmp);
	}
}

int	pipe_executer(t_cmd *cmd, int infile, int outfile, int is_pipe)
{
	int	ret;
	int	fd[2];
	t_pid	*pids;

	pids = NULL;
	pipe(fd);
	ret = pipe_part_executer(((t_pipe *)cmd)->left, infile, fd[1], 1);
	close(fd[1]);
	new_pid(&pids, ret);
	ret = pipe_part_executer(((t_pipe *)cmd)->right, fd[0], outfile, 1);
	new_pid(&pids, ret);
	close(fd[0]);
	if (((t_pipe *)cmd)->right->type != PIPE)
	{
		new_pid(&pids, ret);
		wait_pipes(&pids);
	}
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

