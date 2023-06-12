/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable_parser.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 19:44:04 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/12 20:11:20 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_cmd	*executable_parser(char *line)
{
	t_cmd	*cmd;
	int		i;
	int		j;
	t_var	var;

	i = -1;
	if (!line)
		return (NULL);
	ft_memset(&var, 0, sizeof(t_var));
	while (line[++i])
	{
		check_out_of_quotes(line[i], &var);
		if (!var.quote && !var.dquote && line[i] == ')' || line[i] == '(')
			return (panic_recursive(ERR_UNCLSDP, &line), NULL);
	}
	j = 0;
	i = skip_spaces_front(line);
	if (!*line)
		return (free(line), NULL);
	while (line[i + j] && !ft_isspace(line[i + j]))
		j++;
	cmd = get_token_builtins(ft_strdup(line + i), j);
	if (!cmd)
		cmd = get_token_cmd(ft_strdup(line + i), j);
	return (free (line), cmd);
}
