/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_executer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 19:06:02 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/07 14:23:18 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_path(char *cmd)
{
	char	**path;
	char	*cmd_path;
	char	*tmp_to_free;
	int		i;

	i = 0;
	if (cmd == NULL)
		return (NULL);
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
	return (NULL);
}

char	**arguments_list_to_dstr(t_arguments *args)
{
	t_arguments	*tmp;
	char		**dstr;
	int			len;

	len = 0;
	tmp = args;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	dstr = malloc(sizeof(char *) * (len + 1));
	if (!dstr)
		return (NULL);
	len = 0;
	while (args)
	{
		dstr[len++] = args->str;
		args = args->next;
	}
	dstr[len] = NULL;
	return (dstr);
}

char	**str_to_double(char *str)
{
	char	**dstr;

	dstr = malloc(sizeof(char *) * 2);
	if (!dstr)
		return (NULL);
	dstr[0] = str;
	dstr[1] = NULL;
	return (dstr);
}
char	**get_dstr(t_cmd *cmd)
{
	char	**exec;
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
	exec = args_to_cmd_dstr(((t_execcmd *)cmd)->options, \
	args_to_str(((t_execcmd *)cmd)->cmd));
	return (exec);
}

void	child(char **exec, char *path, int infile, int outfile, int *fd)
{
	char	**backup_env;
	t_hold	*env;
	t_list	*lst;
	int		size;
	int		iter;

	is_sig = 0;
	env = set__get_option_variables(0, GET | GET_ENV);
	lst = env->lst;
	backup_env = ft_calloc(sizeof(char *), (env->size + 1));
	size = env->size;
	iter = 0;
	while (size--)
	{
		backup_env[iter] = ft_strdup(lst->content);
		lst = lst->next;
		iter++;
	}
	if (infile != STDIN_FILENO)
	{
		dup2(infile, STDIN_FILENO);
		if (fd == NULL)
			close(infile);
	}
	if (outfile != STDOUT_FILENO)
	{
		dup2(outfile, STDOUT_FILENO);
		if (fd == NULL)
			close(outfile);
	}
	if (fd != NULL)
	{

		close(fd[0]);
		close(fd[1]);
	}
	execve(path, exec, backup_env);
	ft_putendl_fd("execve faillure", 2);
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
		return (pr_custom_err(ERR_CMD, exec[0], exec[0]), glo_exit = 127, free(exec), 0);
	pid = fork();
	if (pid == -1)
		return (perror("fork failed"), 0);
	if (!pid)
		child(exec, path, infile, outfile, fd);
	free(exec[0]);
	free(exec);
	if (fd != NULL)
		return (free(path), pid);
	if (waitpid(pid, &status, 0) == -1)
		return (free(path) , 0);
	if (WIFEXITED(status))
	{
		status = WEXITSTATUS(status);
		glo_exit = status;
		if (!status)
			return (free(path) , 1);
	}
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			is_sig = 1;
		else if (WTERMSIG(status) == SIGQUIT)
			is_sig = 2;
	}
	if (is_sig == 1)
		write(2, "\n", 1);
	else if (is_sig == 2)
		ft_putendl_fd("Quit: (core dumped)", STDERR_FILENO);
	return (free(path), 0);
}