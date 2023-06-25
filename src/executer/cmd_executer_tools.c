/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_executer_tools.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 15:30:49 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/25 15:51:25 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	child_exit(void)
{
	if (errno == 2)
		exit(127);
	else if (errno == 13 || errno == 20)
		exit(126);
	else if (errno == 130)
		exit(1);
	exit(errno);
}

char	**child_vars(void)
{
	char	**backup_env;
	t_hold	*env;
	t_list	*lst;
	int		size;
	int		iter;

	g_glb.is_sig = 0;
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
	return (pr_custom_err(ERR_CMD, NULL, cmd));
}

void	close_all_faill(t_components comp)
{
	if (comp.is_pipe)
	{
		close(comp.infile);
		close(comp.outfile);
		close(comp.close_red);
		close(comp.stuck);
	}
}

int	wich_call(int ret, t_arguments *exec_cmd, \
t_arguments *arg, t_components comp)
{
	char		*my_cmd;
	t_arguments	*tmp;

	tmp = arg;
	if (!ret)
	{
		my_cmd = args_to_str(exec_cmd);
		ret = cmd_executers(get_path(my_cmd), \
		args_to_cmd_dstr(arg, my_cmd), comp);
		free(my_cmd);
		return (arguments_destructor(&exec_cmd), \
		arguments_destructor(&arg), ret);
	}
	else
	{
		if (ret & ECHO)
			tmp = skip_echo_option(arg, &ret);
		ret = builtin(&tmp, comp.outfile, ret);
		return (arguments_destructor(&exec_cmd), \
		arguments_destructor(&arg), ret);
	}
}
