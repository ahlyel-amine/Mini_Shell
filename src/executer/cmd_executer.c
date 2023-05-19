/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_executer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 19:06:02 by aahlyel           #+#    #+#             */
/*   Updated: 2023/05/19 11:53:45 by aahlyel          ###   ########.fr       */
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

int	cmd_executer(t_cmd *cmd, int infile, int outfile, int fds[3])
{
	int		pid;
	char	**exec;
	char	*path;
	char	**envp;
    int		status;
	static int call;
	call++;
			
	var_expand(((t_execcmd *)cmd)->cmd);
	var_expand(((t_execcmd *)cmd)->options);
	((t_execcmd *)cmd)->cmd = wild_cards(((t_execcmd *)cmd)->cmd, NULL);
	((t_execcmd *)cmd)->options = wild_cards(((t_execcmd *)cmd)->options, NULL);
	exec = arguments_list_to_dstr(((t_execcmd *)cmd)->options);
	exec = ft_joindstrs(str_to_double(arguments_to_str(((t_execcmd *)cmd)->cmd)), \
	exec);
	if (exec)
	path = get_path(exec[0]);
	if (!path)
	{
		pr_custom_err(ERR_CMD, exec[0], exec[0]);
		free(exec);
		return (0);
	}
	pid = fork();
	if (pid == -1) {
    	perror("fork failed");
    	return (0);
    }
	if (!pid)
	{
		if (infile != STDIN_FILENO)
		{
			dup2(infile, STDIN_FILENO);
			close(infile);
		}
		else
			close(fds[1]);
		// if (call == 2)
		// 	while (1)
		// 		;
		if (outfile != STDOUT_FILENO)
		{
			dup2(outfile, STDOUT_FILENO);
			close(outfile);
		}
		else
			close(fds[0]);
		execve(path, exec, NULL);
		exit(EXIT_FAILURE);
	}
	free(exec[0]);
	free(exec);
	// if (fds)
		return (free(path), pid);
	// else
	// {
		printf("last cmd pid[%d]\n", pid);
		if (waitpid(pid, &status, 0) == -1)
		{
			perror("waitpid failed");
			return (free(path) , 0);
		}
		if (WIFEXITED(status))
		{
			status = WEXITSTATUS(status);
			if (!status)
			{
		printf("has been waited successfully\n");
				return (free(path) , 1);
			}
		}
	// }
	return (free(path) , 0);
}
