/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 17:13:32 by aahlyel           #+#    #+#             */
/*   Updated: 2023/04/30 19:47:42 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strdup(const char *s1)
{
	char	*dst;
	int		count;

	count = -1;
	while (ft_isspace(*(char *)(s1)))
		s1++;
	dst = (char *)ft_calloc((ft_strlen(s1) + 1), sizeof(char));
	if (!dst)
		return (NULL);
	while (*(char *)(s1 + ++count))
		*(dst + count) = *(char *)(s1 + count);
	return (dst);
}
