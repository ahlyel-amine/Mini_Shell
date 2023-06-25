/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_call_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 15:34:10 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/25 15:34:26 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
