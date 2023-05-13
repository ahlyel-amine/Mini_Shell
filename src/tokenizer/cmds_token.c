/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:31:37 by aahlyel           #+#    #+#             */
/*   Updated: 2023/05/13 09:42:37 by aahlyel          ###   ########.fr       */
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
		cmd = execcmd_constructor(args, get_argument(line + i, 0, 0, 0));
	else
		cmd = execcmd_constructor(args, NULL);
	return (free(line), /*free(cmd_line),*/ cmd);
}
