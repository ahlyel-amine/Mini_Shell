/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   priorities_call.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 19:53:34 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/19 19:47:53 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_option(char *line, char *endline)
{
	int	i;

	i = 0;
	if (line[i] == '\'' || line[i] == '\"')
		i++;
	if (line[i] == '-')
		i++;
	else
		return (0);
	while (line[i] == 'n' && line + i != endline)
		i++;
	if (line + i == endline || ((line[i] == '\'' || line[i] == '\"') && \
	line + i + 1 == endline))
		return (1);
	return (0);
}

t_lsttoken	*skip_echo_option(t_lsttoken *front, t_lsttoken *back,
		int *has_option)
{
	*has_option = 0;
	while (front)
	{
		if (front->t_.type & (E_STR | E_QUOTE | E_DQUOTE))
		{
			if (!is_option(front->t_.line + front->t_.start, front->t_.line \
			+ front->t_.start + front->t_.len))
				break ;
			else
			{
				if (front && front->next && front->next->t_.type != E_SPACE)
					break ;
				*has_option = 1;
				front = front->next;
				while (front && front->t_.type == E_SPACE)
					front = front->next;
				if (front == back)
					break ;
				continue ;
			}
		}
		break ;
	}
	return (front);
}

t_lsttoken	*skip_space_front_token(t_lsttoken *front)
{
	while (front && front->t_.type == E_SPACE)
		front = front->next;
	return (front);
}

static int	exec_call(t_lsttoken *front, t_lsttoken *back, t_components comp)
{
	char		*cmd;
	t_arguments	*arg;
	int			ret;

	cmd = get_command_name(&front, back);
	if (!cmd)
		return (g_glb.exit_val = 0, 1);
	ret = is_builtin(cmd);
	if (!ret)
	{
		arg = get_cmd(front, back);
		transform_args(&arg);
		ret = cmd_executers(get_path(cmd), args_to_cmd_dstr(arg, cmd), comp);
		return (arguments_destructor(&arg), ret);
	}
	else if (ret == 1)
	{
		front = skip_space_front_token(front);
		if (!ft_strncmp(cmd, "echo", 5))
			front = skip_echo_option(front, back, &ret);
		arg = get_cmd(front, back);
		ret = builtin_executer(arg, cmd, comp.outfile, ret);
		return (arguments_destructor(&arg), free(cmd), ret);
	}
	return (-1);
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
		return (exec_call(front, back, comp));
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
			in = 1;
			t = get_red(head, comp);
			if (t.infile == -1 && t.outfile == -1 && t.is_pipe == 0 && !t.fd)
				return (0);
			head->t_.type = E_EMPTY;
			redirection(front, back, t);
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

int	last_operaotr(t_lsttoken *front, t_lsttoken *back)
{
	t_lsttoken	*head;

	head = front;
	while (head)
	{
		if ((head->t_.type == E_AND || head->t_.type == E_OR))
			return (0);
		if (head == back)
			break ;
		head = head->next;
	}
	return (1);
}

void	init_2ptr(t_lsttoken **head, t_lsttoken **prev, t_lsttoken *front)
{
	*head = front;
	*prev = front;
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
