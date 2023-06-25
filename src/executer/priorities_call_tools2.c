/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   priorities_call_tools2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 23:52:30 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/25 14:20:43 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*get_cmd_name__(char *word, int start, int end)
{
	t_arguments	*arg;

	word = ft_substr(word + start, 0, end);
	if (!word)
		return (NULL);
	arg = get_argument(word, 0, 1);
	free(word);
	transform_args(&arg);
	word = args_to_str(arg);
	return (arguments_destructor(&arg), word);
}

char	*get_command_name(t_lsttoken **front, t_lsttoken *back)
{
	t_lsttoken	*head;
	int			start;
	int			end;
	char		*word;

	start = 0;
	end = 0;
	head = skip_tokens(*front, back, &start, &end);
	if (!head)
		return (NULL);
	word = head->t_.line;
	head = head->next;
	while (head)
	{
		if (!(head->t_.type & (E_STR | E_QUOTE | E_DQUOTE)))
			break ;
		else
			end += head->t_.len;
		if (head == back)
			break ;
		head = head->next;
	}
	*front = head;
	return (get_cmd_name__(word, start, end));
}

void	fd_er(int type, char *fd_err)
{
	if (type != E_HEREDOC)
	{
		ft_putstr_fd(SHELL_NAME, 2);
		ft_putstr_fd(fd_err, 2);
		perror(" ");
	}
}

void	set_fd(char *delim, t_lsttoken *r, t_components *comp)
{
	if (r->t_.type & (E_INRED | E_IOUTRED))
	{
		comp->infile = open(delim, O_CREAT | O_RDONLY, 0644);
		comp->close_red = comp->infile;
	}
	if (r->t_.type == E_INRED)
	{
		comp->infile = open(delim, O_RDONLY);
		comp->close_red = comp->infile;
	}
	else if (r->t_.type == E_APPEND)
	{
		comp->outfile = open(delim, O_CREAT | O_APPEND | O_WRONLY, 0644);
		comp->close_red = comp->outfile;
	}
	else if (r->t_.type == E_OUTRED)
	{
		comp->outfile = open(delim, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		comp->close_red = comp->outfile;
	}
}

t_components	get_red(t_lsttoken *r, t_components comp, int *in)
{
	int		q;
	char	*delim;

	*in = 1;
	if (r->t_.type == E_HEREDOC)
	{
		delim = skip_q_hrdc_delim(r->t_.down->t_.line + r->t_.down->t_.start, \
		r->t_.down->t_.line + r->t_.down->t_.start + r->t_.down->t_.len, &q);
		comp.infile = read_heredocs(delim, q);
		comp.close_red = comp.infile;
	}
	else
	{
		delim = get_filename(r->t_.down->t_.line + r->t_.down->t_.start, \
		r->t_.down->t_.line + r->t_.down->t_.start + r->t_.down->t_.len);
		if (!delim)
			return ((t_components){-1, -1, -1, -1, 0, NULL});
		set_fd(delim, r, &comp);
	}
	if (comp.infile < 0 || comp.outfile < 0)
		return (fd_er(r->t_.type, delim), free(delim), \
		(t_components){-1, -1, -1, -1, 0, NULL});
	return (free(delim), comp);
}
