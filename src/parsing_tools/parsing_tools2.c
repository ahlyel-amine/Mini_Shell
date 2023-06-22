/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:40:17 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/21 17:49:11 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	close_parenthise(char *line)
{
	int		i;
	int		open;
	int		close;
	t_var	var;

	i = 0;
	ft_memset(&var, 0, sizeof(t_var));
	open = 1;
	close = 0;
	if (line[skip_spaces_front(line)] == ')')
		return (-1);
	while (line[i])
	{
		check_out_of_quotes(line[i], &var);
		if (line[i] == '(' && !var.dquote && !var.quote)
			open++;
		else if (line[i] == ')' && !var.dquote && !var.quote)
			close++;
		i++;
		if (close == open)
			break ;
	}
	if (open != close)
		return (-1);
	return (i);
}

void	check_out_of_quotes(char c, t_var *var)
{
	if (c == '\"' && !(var->quote))
			(var->dquote) = !(var->dquote);
	if (c == '\'' && !(var->dquote))
		(var->quote) = !(var->quote);
}

int	skip_spaces_front(char *line)
{
	int	i;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	return (i);
}

void	pr_custom_err(char *error, void *ptr, char *custom)
{
	char	*msg;

	if (!strncmp(error, ERR_O_SNTX, ft_strlen(ERR_O_SNTX)))
		g_glb.exit_val = 258;
	msg = ft_strjoin(error, custom);
	ft_putstr_fd(msg, 2);
	ft_putchar_fd('\n', 2);
	free(msg);
	free (ptr);
}

void	panic(int type)
{
	g_glb.exit_val = 258;
	if (type != -1)
	{
		ft_putstr_fd(ERR_SNTX, STDERR_FILENO);
		if (type == E_AND)
			ft_putstr_fd("`&'\n", STDERR_FILENO);
		else if (type == E_OR || type == E_PIPE)
			ft_putstr_fd("`|'\n", STDERR_FILENO);
		else if (type == 5)
			ft_putstr_fd("`newline'\n", STDERR_FILENO);
		else if (type == E_INRED)
			ft_putstr_fd("`<'\n", STDERR_FILENO);
		else if (type == E_OUTRED)
			ft_putstr_fd("`>'\n", STDERR_FILENO);
		else if (type == E_APPEND)
			ft_putstr_fd("`>>'\n", STDERR_FILENO);
		else if (type == E_HEREDOC)
			ft_putstr_fd("`<<'\n", STDERR_FILENO);
	}
	else
		ft_putstr_fd(ERR_O_SNTX, STDERR_FILENO);
}
