/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_executer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 19:06:02 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/14 23:24:51 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

typedef struct s_2_int
{
	int	infile;
	int	outfile;
}	t_2_int;

static char	*get_path(char *cmd)
{
	char	**path;
	char	*cmd_path;
	char	*tmp_to_free;
	int		i;

	i = 0;
	if (cmd == NULL)
		return (NULL);
	if (!*cmd)
		return (pr_custom_err(ERR_CMD, cmd, cmd), NULL);
	if (!access(cmd, F_OK | X_OK))
		return (ft_strdup(cmd));
	path = (char **)set__get_option_variables(0, GET | GET_PATH);
	while (path && path[i])
	{
		tmp_to_free = ft_strjoin(path[i], "/");
		tmp_to_free = ft_strjoin_free(tmp_to_free, ft_strdup(cmd));
		if (!access(tmp_to_free, F_OK | X_OK))
			return (tmp_to_free);
		free(tmp_to_free);
		i++;
	}
	return (pr_custom_err(ERR_CMD, cmd, cmd), NULL);
}

static char	**get_dstr(t_cmd *cmd)
{
	char		**exec;
	t_arguments	*nl;

	nl = NULL;
	var_expand(((t_execcmd *)cmd)->cmd);
	var_expand(((t_execcmd *)cmd)->options);
	wild_cards(&((t_execcmd *)cmd)->cmd);
	wild_cards(&((t_execcmd *)cmd)->options);
	args_join(&((t_execcmd *)cmd)->cmd);
	args_join(&((t_execcmd *)cmd)->options);
	args_move_down(&((t_execcmd *)cmd)->cmd, &nl);
	nl = NULL;
	args_move_down(&((t_execcmd *)cmd)->options, &nl);
	args_join_down(&((t_execcmd *)cmd)->options);
	exec = args_to_cmd_dstr(((t_execcmd *)cmd)->options, \
	args_to_str(((t_execcmd *)cmd)->cmd));
	return (exec);
}

char	**child_vars(void)
{
	char	**backup_env;
	t_hold	*env;
	t_list	*lst;
	int		size;
	int		iter;

	is_sig = 0;
	env = set__get_option_variables(0, GET | GET_ENV);
	lst = env->lst;
	size = env->size;
	backup_env = ft_calloc(sizeof(char *), (size + 1));
	iter = 0;
	while (size--)
	{
		backup_env[iter] = ft_strdup(lst->content);
		lst = lst->next;
		iter++;
	}
	return (backup_env);
}

static void	child(char **exec, char *path, t_2_int a, int *fd)
{
	char	**backup_env;

	backup_env = child_vars();
	if (a.infile != STDIN_FILENO)
	{
		dup2(a.infile, STDIN_FILENO);
		if (fd == NULL)
			close(a.infile);
	}
	if (a.outfile != STDOUT_FILENO)
	{
		dup2(a.outfile, STDOUT_FILENO);
		if (fd == NULL)
			close(a.outfile);
	}
	if (fd != NULL)
	{
		close(fd[0]);
		close(fd[1]);
	}
	execve(path, exec, backup_env);
	ft_putendl_fd(ERR_EXVE, 2);
	exit(errno);
}

int	cmd_executer(t_cmd *cmd, int infile, int outfile, int *fd)
{
	int		pid;
	char	**exec;
	char	*path;
	int		status;

	exec = get_dstr(cmd);
	if (!exec)
		return (perror(""), 0);
	path = get_path(exec[0]);
	if (!path)
		return (glo_exit = 127, free(exec), 0);
	pid = fork();
	if (pid == -1)
		return (perror(SHELL_NAME), 0);
	if (!pid)
		child(exec, path, (t_2_int){infile, outfile}, fd);
	free(exec[0]);
	free(exec);
	if (fd != NULL)
		return (free(path), pid);
	if (waitpid(pid, &status, 0) == -1)
		return (free(path), 0);
	if (cmd_sig_check(path, status))
		return (0x1);
	return (free(path), 0);
}
