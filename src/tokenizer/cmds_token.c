/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:31:37 by aahlyel           #+#    #+#             */
/*   Updated: 2023/05/12 20:10:33 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_cmd	*get_token_cmd(char *line, int j)
{
	t_arguments	*args;
	char		*tmp;
	t_cmd		*cmd;
	int			i;
	t_var		var;

	i = 0;
	if (!*line)
		return (NULL);
	set_zero_var(&var);
	while (line[i])
	{
		check_out_of_quotes(line[i], &var);
		if (!var.quote && !var.dquote && ft_isspace(line[i]))
			break ;
		i++;
	}
	tmp = ft_substr(line, 0, i);
	args = get_argument(tmp, 0, 0, 0);
	free (tmp);
	i += skip_spaces_front(line + i);
	if (line[i])
		args->next = get_argument(line + i, 0, 0, 0);
	cmd = execcmd_constructor(args);
	return (free(line), /*free(cmd_line),*/ cmd);
}
