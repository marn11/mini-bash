/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 18:26:36 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/07/09 15:46:32 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_value(char *ptr, int end, t_exp **exp)
{
	char	*ptr2;
	t_exp	*env;

	env = *exp;
	ptr2 = ft_substr(ptr, 0, end);
	if (!ptr2)
		return (NULL);
	while (env)
	{
		if (!ft_strcmp(env->key, ptr2))
		{
			free(ptr2);
			return (env->value);
		}
		env = env->next;
	}
	free(ptr2);
	return (NULL);
}

int	get_key(char *ptr)
{
	int	i;

	i = 0;
	while (ft_isalpha_num(ptr[i]))
		i++;
	return (i);
}
