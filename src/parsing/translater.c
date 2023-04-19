/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translater.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 02:51:48 by aahlyel           #+#    #+#             */
/*   Updated: 2023/04/19 02:59:59 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_for_args(char	*word)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(word);
	if (ft_strnstr(word, "&&", len))
	{
		
	}
	while (word[i])
}

int	words_to_args(char **words)
{
	int	i;

	i = 0;
	while (words[i])
	{
		if (*words[i] == "\'" || *words[i] == "\"")
		{
			i++;
			continue ;
		}
		check_for_args(words[i]);
		i++;
	}
}