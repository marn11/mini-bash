/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 22:04:20 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/07/17 09:04:42 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_pointers(char *read_me, char *delim, int *td, t_list *temp)
{
	free(read_me);
	free(delim);
	close(td[1]);
	close(td[0]);
	temp->infile = td[0];
}

char	*rm_quotes(char *s1, int *bool, int i)
{
	char	*copy;
	char	quote_type;

	copy = malloc(ft_strlen(s1) + 1);
	if (!s1 || !copy)
		return (NULL);
	while (*s1)
	{
		if (*s1 == '\'' || *s1 == '"')
		{
			quote_type = *s1++;
			if (quote_type == '\'')
				*bool = 1;
			else if (quote_type == '"')
				*bool = 2;
			while (*s1 && *s1 != quote_type)
				copy[i++] = *s1++;
			if (*s1)
				s1++;
		}
		else
			copy[i++] = *s1++;
	}
	copy[i] = '\0';
	return (copy);
}

void	find_delimiter(t_list *temp, t_exp **exp, int i)
{
	char		*read_me;
	int			bool;
	char		*delim;
	int			td[2];
	int			fd;

	if (pipe(td) == -1)
		perror("file descriptor error\n");
	bool = 0;
	fd = dup(0);
	delim = rm_quotes((temp->option[i + 1]), &bool, 0);
	signal(SIGINT, signal_handler_heredoc);
	read_me = readline("> ");
	while (read_me)
	{
		if (!bool && ft_strcmp(delim, read_me))
			expanding_heredoc(&read_me, exp);
		if (!ft_strcmp(delim, read_me))
			break ;
		ft_putendl_fd(read_me, td[1]);
		read_me = readline("> ");
	}
	dup2(fd, 0);
	close(fd);
	free_pointers(read_me, delim, td, temp);
}

void	handle_heredoc(t_list **list, t_exp **exp)
{
	t_list		*temp;
	int			i;

	temp = *list;
	if (temp)
		temp->infile = 0;
	while (temp)
	{
		i = 0;
		while (temp->option[i])
		{
			if (!ft_strcmp(temp->option[i], "<<"))
				find_delimiter(temp, exp, i);
			i++;
		}
		temp = temp->next;
	}
	if (g_sig == 1)
		(*exp)->status = 1;
}
