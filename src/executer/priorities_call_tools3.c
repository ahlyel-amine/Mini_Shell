/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   priorities_call_tools3.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 23:52:33 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/22 14:10:10 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	set_return_err(char *cmd)
{
	int	i;

	i = 0;
	g_glb.exit_val = 127;
	while (cmd[i])
	{
		if (cmd[i] == '/')
		{
			if (!access(cmd, F_OK))
				return (g_glb.exit_val = 126, \
				pr_custom_err(ERR_PERMISSION, cmd, cmd));
			return (pr_custom_err(ERR_FILE, cmd, cmd));
		}
		i++;
	}
	return (pr_custom_err(ERR_CMD, cmd, cmd));
}

char	*get_path(char *cmd)
{
	char	**path;
	char	*tmp_to_free;
	int		i;

	i = 0;
	path = NULL;
	if (cmd == NULL)
		return (NULL);
	if (!*cmd)
		return (pr_custom_err(ERR_CMD, NULL, cmd), NULL);
	if (has_slash(cmd))
		return (is_dir(cmd));
	tmp_to_free = get_owd("PATH=");
	if (tmp_to_free)
		path = ft_split(tmp_to_free, ':');
	while (path && path[i])
	{
		tmp_to_free = ft_strjoin(path[i], "/");
		tmp_to_free = ft_strjoin_free(tmp_to_free, ft_strdup(cmd));
		if (!access(tmp_to_free, F_OK | X_OK))
			return (sp_free(path), free(cmd), tmp_to_free);
		free(tmp_to_free);
		i++;
	}
	return (sp_free(path), set_return_err(cmd), NULL);
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

int	cmd_executers(char *path, char **cmd, t_components comp)
{
	int	status;
	int	pid;
	printf("%p\n", cmd[0]);
	if (!path || !cmd)
	{
		if (cmd)
			return (sp_free(cmd), free(path), 0);
		return (free(cmd), free(path), 0);
	}	
	pid = fork();
	sig_exec_init();
	if (pid == -1)
		return (perror(FORK_ERR), free(path), free(cmd), -1);
	if (!pid)
		child(cmd, path, comp);
	if (comp.is_pipe != 0)
		return (free(path), free(cmd), pid);
	if (waitpid(pid, &status, 0) == -1)
		return (free(path), free(cmd), 0);
	cmd_sig_check(status);
	return (free(cmd), free(path), 0);
}

t_lsttoken	*skip_tokens(t_lsttoken *head, t_lsttoken *back, int *start, \
int *end)
{
	while (head && (head->t_.type & (E_EMPTY | E_SPACE)))
	{
		if (head == back)
			break ;
		head = head->next;
	}
	if (!head || (head->t_.type & (E_EMPTY | E_SPACE)))
		return (NULL);
	*start = head->t_.start;
	*end = head->t_.len;
	return (head);
}
