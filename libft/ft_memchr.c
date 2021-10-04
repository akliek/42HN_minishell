/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akliek <akliek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 13:44:16 by akliek            #+#    #+#             */
/*   Updated: 2021/06/23 15:56:37 by akliek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*mem;

	if (n == 0)
		return (NULL);
	mem = (char *)s;
	while (--n && *mem != (char)c)
		mem++;
	if (*mem != (char)c)
		return (NULL);
	return (mem);
}
