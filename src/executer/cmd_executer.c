/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_executer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 19:06:02 by aahlyel           #+#    #+#             */
/*   Updated: 2023/05/13 18:42:03 by aahlyel          ###   ########.fr       */
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

int	cmd_executer(t_cmd *cmd, int infile, int outfile)
{
	int		pid;
	char	**exec;
	char	*path;
	char	**envp;
    int		status;

	((t_execcmd *)cmd)->cmd = wild_cards(((t_execcmd *)cmd)->cmd, NULL);
	((t_execcmd *)cmd)->options = wild_cards(((t_execcmd *)cmd)->options, NULL);
	exec = arguments_list_to_dstr(((t_execcmd *)cmd)->options);
	exec = ft_joindstrs(str_to_double(arguments_to_str(((t_execcmd *)cmd)->cmd)), \
	exec);
	if (exec)
	path = get_path(exec[0]);
	// envp = (char **)set__get_option_variables(0, GET | GET_ENV); //need envp char ** aaaa weld nass
	if (!path)
		return (pr_custom_err(ERR_CMD, NULL, exec[0]), 0);
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

	free(exec[0]);
	free(exec);
	if (wait(&status) == -1)
	{
	printf("HEY\n");
        perror("waitpid failed");
        return (free(path) , 0);
    }
    if (WIFEXITED(status))
	{
       status = WEXITSTATUS(status);
		if (!status)
			return (free(path) , 1);
    }

	return (free(path) , 0);
}
