/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 02:48:25 by aahlyel           #+#    #+#             */
/*   Updated: 2023/02/19 18:42:49 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	ls;

	ls = ft_strlen(src);
	if (dstsize == 0)
		return (ls);
	while (*src && --dstsize)
		*(dst++) = *(src++);
	*dst = '\0';
	return (ls);
}
