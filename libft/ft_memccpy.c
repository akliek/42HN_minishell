/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akliek <akliek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 13:44:14 by akliek            #+#    #+#             */
/*   Updated: 2021/07/12 17:49:53 by akliek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t	i;
	char	*dst_new;
	char	*src_new;

	i = 0;
	dst_new = (char *)dst;
	src_new = (char *)src;
	while (i < n)
	{
		dst_new[i] = src_new[i];
		if ((unsigned char)src_new[i] == (unsigned char)c)
			return (&dst_new[i + 1]);
		i++;
	}
	return (NULL);
}
