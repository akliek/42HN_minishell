/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akliek <akliek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 13:45:03 by akliek            #+#    #+#             */
/*   Updated: 2021/07/05 18:27:13 by akliek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needl, size_t len)
{
	size_t	i;
	size_t	j;

	if (!*needl)
		return ((char *)haystack);
	while (*haystack && len)
	{
		i = 0;
		j = len;
		while (haystack[i] && needl[i] && haystack[i] == needl[i] && j--)
			i++;
		if (needl[i] == '\0')
			return ((char *)haystack);
		len--;
		haystack++;
	}
	return (NULL);
}
