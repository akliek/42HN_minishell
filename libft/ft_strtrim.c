/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akliek <akliek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 13:45:08 by akliek            #+#    #+#             */
/*   Updated: 2021/06/25 13:08:16 by akliek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_trim(char c, char const *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*res;
	int		i;
	int		j;
	int		k;

	if (!s1 || !set)
		return (NULL);
	i = ft_strlen(s1) - 1;
	j = 0;
	k = 0;
	while (s1[j] && is_trim(s1[j], set))
		j++;
	while (i > j && is_trim(s1[i], set))
		i--;
	res = (char *)malloc((i - j + 2) * sizeof(char));
	if (!res)
		return (NULL);
	while (j <= i)
		res[k++] = s1[j++];
	res[k] = '\0';
	return (res);
}
