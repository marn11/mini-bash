/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 22:53:32 by mbenchel          #+#    #+#             */
/*   Updated: 2024/05/13 12:05:57 by mbenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	size_t	i;
	size_t	j;
	char	*c;

	i = 0;
	j = 0;
	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	len = ft_strlen(s1) + ft_strlen(s2);
	c = (char *)malloc(len + 1);
	if (c == NULL)
		return (NULL);
	while (s1[j])
		c[i++] = s1[j++];
	j = 0;
	while (s2[j])
		c[i++] = s2[j++];
	c[i] = '\0';
	return (c);
}
