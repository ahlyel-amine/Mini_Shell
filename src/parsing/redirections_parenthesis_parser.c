/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_parenthesis_parser.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:28:49 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/13 00:37:02 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

typedef struct s_redirect_vars
{
	t_var	var;
	int		i;
	int		pr;
}	t_rv;

static void	skip_parenthesis(char **line, int *i, t_var var, int *quit)
{
	int	k;

	if (((*line)[*i] == '(') && !var.quote && !var.dquote)
	{
		k = close_parenthise(*line + *i + 1);
		if (k == -1)
		{
			*quit = -1;
			panic_recursive(ERR_UNCLSDP, line);
			return ;
		}
		*i += k + 1;
		*quit = 1;
	}
}

static t_cmd	*red_pr_cndts(t_cmd *operator, char **line, \
t_rv a, int *quit)
{
	operator = check_redirect_append(line, a.i, a.var, quit);
	if (*quit != -1 && *quit != 1)
		operator = check_redirect_outred(line, a.i, a.var, quit);
	if (a.pr == 1 && *quit != -1 && *quit != 1)
		operator = check_redirect_herdoc_after(line, a.i, a.var, quit);
	if (a.pr == 1 && *quit != -1 && *quit != 1)
		operator = check_redirect_inred_after(line, a.i, a.var, quit);
	if (a.pr != 1 && *quit != -1 && *quit != 1)
		operator = check_redirect_herdoc(line, a.i, quit);
	if (a.pr != 1 && *quit != -1 && *quit != 1)
		check_redirect_inred(line, a.i, quit);
	return (operator);
}

static int	redirections_parenthesis_loop(char **line, t_var var, t_cmd **operator)
{
	int	i;
	int	quit;
	int	pr;

	pr = 0;
	i = 0;
	while ((*line)[i])
	{
		check_out_of_quotes((*line)[i], &var);
		if (!pr)
		{
			skip_parenthesis(line, &i, var, &pr);
			if (pr == -1)
				return (0);
			else if (pr == 1)
				continue ;
		}
		*operator = red_pr_cndts(*operator, line, (t_rv){var, i, pr}, &quit);
		if (quit == -1)
			return (0);
		else if (quit == 1)
			break ;
		i++;
	}
	return (1);
}

t_cmd	*redirections_parser_has_parenthesis(char *line)
{
	t_cmd	*operator;
	t_var	var;

	if (!line)
		return (NULL);
	ft_memset(&var, 0, sizeof(t_var));
	operator = NULL;
	if (!redirections_parenthesis_loop(&line, var, &operator))
		return (NULL);
	if (!operator && line)
		operator = redirections_parser(remove_unused_parenthesis(line));
	return (operator);
}
