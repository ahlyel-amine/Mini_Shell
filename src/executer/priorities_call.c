/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   priorities_call.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 19:53:34 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/17 19:26:01 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	exec_call(t_lsttoken *front, t_lsttoken *back, t_components comp)
{
	char		*cmd;
	t_arguments	*arg;
	int			ret;

	cmd = get_command_name(&front, back);
	if (cmd)
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
		while (front->t_.type == E_SPACE)
			front = front->next;
		arg = get_cmd(front, back);
		ret = builtin_executer(arg, cmd, comp.outfile);
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
		return exec_call(front, back, comp);
	return (-1);
}

int	redirection(t_lsttoken *front, t_lsttoken *back, t_components comp)
{
	t_lsttoken		*head;
	int				in;
	t_components	tmp;

	in = 0;
	head = front;
	while (head)
	{
		if (head->t_.type == E_OUTRED || head->t_.type == E_INRED || \
		head->t_.type == E_APPEND || head->t_.type == E_HEREDOC)
		{
			in = 1;
			tmp = get_red(head, comp);
			if (tmp.infile == -1 && tmp.outfile == -1 && tmp.is_pipe == 0 && !tmp.fd)
				return (0);
			head->t_.type = E_EMPTY;			
			redirection(front, back, tmp);
			break ;
		}
		if (head == back)
			break ;
		head = head->next;
	}
	if (!in)
		return subsh(front, back, comp);
	return (-1);
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
			break;
		}
		prev = head;
		if (head == back)
			break ;
		head = head->next;
	}
	if (!in)
		return redirection(front, back, comp);
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

int	operator(t_lsttoken *front, t_lsttoken *back, t_components comp)
{
	t_lsttoken	*head;
	t_lsttoken	*prev;
	int			in;

	in = 0;
	head = front;
	prev = front;
	while (head)
	{
		if ((head->t_.type == E_AND || head->t_.type == E_OR) && last_operaotr(head->next, back))
		{
			in = 1;
			operator(front, prev, comp);
			if ((glo_exit == 0 && head->t_.type == E_AND) || (glo_exit != 0 && head->t_.type == E_OR))
				operator(head->next, back, comp);
			break ;
		}
		prev = head;
		if (head == back)
			break ;
		head = head->next;
	}
	if (!in)
		return pipe_(front, back, comp);
	return (-1);
}
