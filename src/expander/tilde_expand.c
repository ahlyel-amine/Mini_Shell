/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 16:45:08 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/06/20 16:22:32 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*tld(char *root, char *is_true, char *is_not)
{
	if (root)
		return (free(is_not), is_true);
	else
		return (free(is_true), is_not);
}

char	*tilde_replace(char *arg)
{
	char	*hm;
	size_t	len;

	len = ft_strlen(arg);
	hm = getenv("HOME");
	if (len == 1)
		return (tld(hm, ft_strdup(hm), ft_strdup("")));
	else if (len > 1 && (*(arg + 1) == '/' || *(arg + 1) == ' '))
		return (tld(hm, ft_strjoin(hm, (arg + 1)), ft_strjoin("", (arg + 1))));
	else if (len > 1 && (*(arg + 1) == '+' || *(arg + 1) == '-'))
	{
		if ((*(arg + 1) == '+' && !*(arg + 2)) || (len >= 2 && \
		*(arg + 1) == '+' && (*(arg + 2) == '/' || *(arg + 2) == 0x20)))
		{
			hm = get_owd("PWD=");
			return (tld(hm, ft_strjoin(hm, (arg + 2)), ft_strdup("")));
		}
		else if ((*(arg + 1) == '-' && !*(arg + 2)) || ((len > 2 && \
		*(arg + 1) == '-' && (*(arg + 2) == '/')) || *(arg + 2) == 0x20))
		{
			hm = get_owd("OLDPWD=");
			return (tld(hm, ft_strjoin(hm, (arg + 2)), ft_strdup("")));
		}
	}
	return (ft_strdup(arg));
}

char	*tilde_expansion(char *arg, unsigned short type, t_arguments *next)
{
	char	*tilde;
	int		len;

	tilde = (arg);
	if (!*tilde || *tilde != '~')
		return (arg);
	else if (*tilde == '~' && !(type & QUOTE) && !(type & DQUOTE))
	{
		len = ft_strlen(arg);
		if ((len == 1 && (!next)) || (next && next->type == IS_SEPARTOR))
		{
			arg = tilde_replace(tilde);
			free(tilde);
		}
		else if (len > 1)
		{
			arg = tilde_replace(tilde);
			free(tilde);
		}
		return (arg);
	}
	return (arg);
}
