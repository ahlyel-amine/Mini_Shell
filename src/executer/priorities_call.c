/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   priorities_call.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 19:53:34 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/23 20:07:20 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_arguments	*get_cmd_arguments(t_arguments *cmd)
{
	t_arguments *arg;
	t_arguments *tmp;

	tmp = cmd;
	if (!cmd)
		return (NULL);
	while (tmp->next)
	{
		if (tmp->type & IS_SEPARTOR)
			break ;
		tmp = tmp->next;
	}
	if (!tmp)
		return (NULL);
	arg = tmp->next;
	tmp->next = NULL;
	return (arg);
}

char	*extend_line(t_lsttoken *front)
{
	size_t		len;

	len = get_lenght(front);
	return (get_line(front, len));
}

int	builtin(t_arguments **args, int outfile, int falg)
{
	int	pid;
	int	status;

	if (!g_glb.is_pipe)
		return (builtin_executer(args, outfile, falg));
	else
	{
		g_glb.is_pipe = 0;
		pid = fork();
		if (pid == -1)
			return (perror("minishell: "), -1);
		if (pid == 0)
		{
			pid = builtin_executer(args, outfile, falg);
			exit (pid);
		}
		waitpid(pid, &status, 0);
		return (cmd_sig_check(status));
	}
}

static int	exec_call(t_lsttoken *front, t_components comp)
{
	t_arguments	*exec_cmd;
	t_arguments	*tmp;
	t_arguments	*arg;
	char		*my_cmd;
	int			ret;

	my_cmd = extend_line(front);
	if (!my_cmd[skip_spaces_front(my_cmd)])
		return (free(my_cmd), 0);
	exec_cmd = get_argument(my_cmd, 0, 1);
	transform_args(&exec_cmd);
	ret = is_builtin(my_cmd);
	arg = get_cmd_arguments(exec_cmd);
	
	tmp = arg;
	if (!ret)
	{
		my_cmd = args_to_str(exec_cmd);
		ret = cmd_executers(get_path(my_cmd), args_to_cmd_dstr(arg, my_cmd), comp);
		free(my_cmd);
		return (arguments_destructor(&exec_cmd), arguments_destructor(&arg), ret);
	}
	else
	{
		if (ret & ECHO)
			tmp = skip_echo_option(arg, &ret);
		// ret = builtin_executer(&tmp, comp.outfile, ret);
		ret = builtin(&tmp, comp.outfile, ret);
		return (arguments_destructor(&exec_cmd), arguments_destructor(&arg),ret);
	}
}

static int	subsh(t_lsttoken *front, t_lsttoken *back, t_components comp)
{
	t_lsttoken	*head;
	int			in;

	in = 0;
	head = front;
	while (head)
	{
		if (head->t_.type == E_SUBSH)
		{
			in = 1;
			subsh_call(head, comp);
			break ;
		}
		if (head == back)
			break ;
		head = head->next;
	}
	if (!in)
		return (exec_call(front, comp));
	return (-1);
}

int	redirection(t_lsttoken *front, t_lsttoken *back, t_components comp)
{
	t_lsttoken		*head;
	int				in;
	t_components	t;

	in = 0;
	head = front;
	while (head)
	{
		if (head->t_.type & (E_OUTRED | E_INRED | E_APPEND | E_HEREDOC))
		{
			t = get_red(head, comp, &in);
			if (t.infile == -1 && t.outfile == -1 && t.is_pipe == 0 && !t.fd)
				return (g_glb.exit_val = 1, 0);
			head->t_.type = E_EMPTY;
			redirection(front, back, t);
			close(t.close_red);
			break ;
		}
		if (head == back)
			break ;
		head = head->next;
	}
	if (!in)
		return (subsh(front, back, comp));
	return (0);
}

int	pipe_(t_lsttoken *front, t_lsttoken *back, t_components comp)
{
	t_lsttoken	*head;
	t_lsttoken	*prev;
	int			in;

	in = 0;
	head = front;
	prev = front;
	while (head)
	{
		if (head->t_.type == E_PIPE)
		{
			in = 1;
			pipe_call((t_2ptr_t_lsttoken){front, back}, head, prev, comp);
			break ;
		}
		prev = head;
		if (head == back)
			break ;
		head = head->next;
	}
	if (!in)
		return (redirection(front, back, comp));
	return (-1);
}

int	operator(t_lsttoken *front, t_lsttoken *back, t_components comp)
{
	t_lsttoken	*head;
	t_lsttoken	*prev;
	int			in;

	in = 0;
	init_2ptr(&head, &prev, front);
	while (head)
	{
		if ((head->t_.type & (E_AND | E_OR)) && last_operaotr(head->next, back)) 
		{
			in = 1;
			operator(front, prev, comp);
			if ((g_glb.exit_val == 0 && head->t_.type & E_AND) || \
			(g_glb.exit_val != 0 && head->t_.type & E_OR))
				operator(head->next, back, comp);
			break ;
		}
		prev = head;
		if (head == back)
			break ;
		head = head->next;
	}
	if (!in)
		return (pipe_(front, back, comp));
	return (0);
}
