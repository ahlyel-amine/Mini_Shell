/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 15:27:13 by aahlyel           #+#    #+#             */
/*   Updated: 2023/04/21 05:19:24 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_operator_call(t_arg *arg, char *word)
{
	if (!ft_strncmp(word[i], S_CMDAND, ft_strlen(S_CMDAND) + 1))
			return (new_arg(&arg, word[i], T_OPERATOR), 1);
	else if (!ft_strncmp(word[i], S_CMDOR, ft_strlen(S_CMDOR) + 1))
		return (new_arg(&arg, word[i], T_OPERATOR), 1);
	else if (!ft_strncmp(word[i], S_CMDPIPE, ft_strlen(S_CMDPIPE) + 1))
		return (new_arg(&arg, word[i], T_OPERATOR), 1);
	return (0);
}

int	check_biltn_call(t_arg *arg, char *word)
{
	if (!ft_strncmp(word[i], S_ENV, ft_strlen(S_ENV) + 1))
			return (new_arg(&arg, word[i], T_BILTN), 1);
	else if (!ft_strncmp(word[i], S_UNSET, ft_strlen(S_UNSET) + 1))
		return (new_arg(&arg, word[i], T_BILTN), 1);
	else if (!ft_strncmp(word[i], S_ECHO, ft_strlen(S_ECHO) + 1))
		return (new_arg(&arg, word[i], T_BILTN), 1);
	else if (!ft_strncmp(word[i], S_PWD, ft_strlen(S_PWD) + 1))
		return (new_arg(&arg, word[i], T_BILTN), 1);
	else if (!ft_strncmp(word[i], S_EXP, ft_strlen(S_EXP) + 1))
		return (new_arg(&arg, word[i], T_BILTN), 1);
	return (0);
}

// void	check_wordcmd_call(t_arg *arg, char *word)
// {
// 	if ()
// }

void	tokenizer(char **words)
{
	t_arg	*arg;
	int	i;

	arg = malloc(sizeof(t_arg));
	if (!arg)
		return ;
	i = 0;
	while (words[i])
	{
		if (check_operator_call(arg, word[i]))
			;
		else if (check_biltn_call(arg, word[i]))
			;
		else
			check_wordcmd_call(arg, word[i]);
		i++;
	}
}
