/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_executer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 19:05:58 by aahlyel           #+#    #+#             */
/*   Updated: 2023/05/16 20:13:52 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
typedef struct s_pid_pipe
{
	int	pid;
	struct s_pid_pipe	*next;
}	t_pid_pipe;
void	new_pid(t_pid_pipe **list, int pid)
{
	t_pid_pipe	*new;
	t_pid_pipe	*tmp;
			printf("new_pid : %d\n", pid);
	new = malloc(sizeof(t_pid_pipe));
	if (!new)
		return ;
	new->pid = pid;
	new->next = NULL;
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
void	wait_pipes(t_pid_pipe **list)
{
	t_pid_pipe	*tmp;
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

int	pipe_executer(t_cmd *cmd, int infile, int outfile, int fds[3])
{
	int	ret;
	int	fd[2];
	static t_pid_pipe *list;
	t_pid_pipe	*tmp;
	int			staus;
	pipe(fd);
	fds[0] = fd[0];
	fds[1] = fd[1];
	fds[2] = 1;
	ret = pipe_part_executer(((t_pipe *)cmd)->left, infile, fd[1], fds);
	close(fd[1]);
	new_pid(&list, ret);
	ret = pipe_part_executer(((t_pipe *)cmd)->right, fd[0], outfile, fds);
	close(fd[0]);
	if (((t_pipe *)cmd)->right->type != PIPE)
	{
		new_pid(&list, ret);
		wait_pipes(&list);
	}
	return (ret);
}

int	pipe_part_executer(t_cmd *cmd, int infile, int outfile, int fds[3])
{
	int	ret;

	ret = 0;
	if (cmd && cmd->type == REDIR)
		ret = redirect_executer(cmd, infile, outfile,  fds);
	else if (cmd && cmd->type == EXEC)
		ret = cmd_executer(cmd, infile, outfile,  fds);
	else if (cmd && cmd->type == BUILTIN)
		ret = builtin_executer(cmd, infile, outfile,  fds);
	else if (cmd && cmd->type == AND)
		ret = and_executer(cmd, infile, outfile,  fds);
	else if (cmd && cmd->type == OR)
		ret = or_executer(cmd, infile, outfile,  fds);
	else if (cmd && cmd->type == PIPE)
		ret = pipe_executer(cmd, infile, outfile,  fds);
	return (ret);
}