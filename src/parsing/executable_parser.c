/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable_parser.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 19:44:04 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/10 14:25:30 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_cmd	*executable_parser(char *line)
{
	t_cmd	*cmd;
	int		i;
	int		j;
	int		has_option;
t_var var;
	if (!line)
		return (NULL);
	ft_memset(&var, 0, sizeof(t_var));
	i = 0;

	while (line[i])
	{
		check_out_of_quotes(line[i], &var);
		if (!var.quote && !var.dquote && line[i] == ')' || line[i] == '(')
			return (panic_recursive(ERR_UNCLSDP, &line), NULL);
		i++;
	}
	i = 0;
	j = 0;
	has_option = 0;
	cmd = NULL;
	if (!*line)
		return (free(line), NULL);
	while (ft_isspace(line[i]))
		i++;
	while (line[i + j] && !ft_isspace(line[i + j]))
		j++;
	cmd = get_token_builtins(ft_strdup(line + i), j);
	if (!cmd)
		cmd = get_token_cmd(ft_strdup(line + i), j);
	free (line);
	return (cmd);
}