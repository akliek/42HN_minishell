/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akliek <akliek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 13:44:54 by akliek            #+#    #+#             */
/*   Updated: 2021/06/25 17:36:11 by akliek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	res;

	if (!src || !dst)
		return (0);
	res = 0;
	while (src[res])
		res++;
	if (dstsize == 0)
		return (res);
	while (*src && --dstsize)
		*dst++ = *src++;
	*dst = '\0';
	return (res);
}
