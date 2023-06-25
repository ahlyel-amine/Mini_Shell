/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_executer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 15:50:28 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/25 15:52:15 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	cmd_executers(char *path, char **cmd, t_components comp)
{
	int	status;
	int	pid;

	if (!path || !cmd)
		return (free(path), sp_free(cmd), 0);
	pid = fork();
	sig_exec_init();
	if (pid == -1)
		return (perror(FORK_ERR), close_all_faill(comp), \
		free(path), sp_free(cmd), -1);
	if (!pid)
		child(cmd, path, comp);
	if (comp.is_pipe != 0)
		return (free(path), sp_free(cmd), pid);
	if (waitpid(pid, &status, 0) == -1)
		return (free(path), sp_free(cmd), 0);
	cmd_sig_check(status);
	return (sp_free(cmd), free(path), 0);
}

void	child(char **exec, char *path, t_components comp)
{
	char	**backup_env;

	backup_env = child_vars();
	if (comp.infile != STDIN_FILENO)
	{
		dup2(comp.infile, STDIN_FILENO);
		if (comp.is_pipe == 0)
			close(comp.infile);
	}
	if (comp.outfile != STDOUT_FILENO)
	{
		dup2(comp.outfile, STDOUT_FILENO);
		if (comp.is_pipe == 0)
			close(comp.outfile);
	}
	if (comp.is_pipe != 0)
	{
		close(comp.fd[0]);
		close(comp.fd[1]);
	}
	execve(path, exec, backup_env);
	perror("minishell: ");
	child_exit();
}
