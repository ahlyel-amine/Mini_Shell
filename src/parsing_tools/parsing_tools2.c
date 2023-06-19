/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:40:17 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/19 10:54:57 by aahlyel          ###   ########.fr       */
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

	msg = ft_strjoin(error, custom);
	ft_putstr_fd(msg, 2);
	ft_putchar_fd('\n', 2);
	free(msg);
	free (ptr);
}

void	panic_recursive(char *error, char **ptr)
{
	ft_putstr_fd(error, STDERR_FILENO);
	// free (*ptr);
	// *ptr = NULL;
}

char	**ft_dstrdup(char **ds1)
{
	char	**words;
	int		ds1_len;
	int		j;

	ds1_len = ft_double_strlen(ds1);
	j = -1;
	words = malloc(sizeof(char *) * (ds1_len + 1));
	if (!words)
		return (NULL);
	while (ds1[++j])
		words[j] = ds1[j];
	words[j] = NULL;
	return (words);
}