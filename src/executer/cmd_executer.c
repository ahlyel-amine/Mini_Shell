/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_executer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 19:06:02 by aahlyel           #+#    #+#             */
/*   Updated: 2023/05/11 01:17:55 by aahlyel          ###   ########.fr       */
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

int	cmd_executer(t_cmd *cmd, int infile, int outfile)
{
	int	pid;
	char	**exec;
	char	*path;
	char	**envp;
    int status;

	exec = ((t_execcmd *)cmd)->cmd;
	if (exec)
	path = get_path(exec[0]);
	envp = (char **)set__get_option_variables(0, GET | GET_ENV);

	pid = fork();
	if ( pid == -1) {
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
		if (outfile != STDOUT_FILENO)
		{
			dup2(outfile, STDOUT_FILENO);
			close(outfile);
		}
		
		execve(path, exec, NULL);
		perror("");
		exit(EXIT_FAILURE);
	}
	if (wait(&status) == -1)
	{
        perror("waitpid failed");
        return (0);
    }
    if (WIFEXITED(status))
	{
       status = WEXITSTATUS(status);
		if (!status)
			return (1);
    }
	return (0);
}
