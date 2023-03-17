/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsa-mora <dsa-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 10:10:34 by dsa-mora          #+#    #+#             */
/*   Updated: 2023/03/17 11:12:29 by dsa-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_list(t_list **lst)
{
	t_list	*temp;
	int		i;

	while (*lst)
	{
		i = -1;
		temp = (*lst)->next;
		while ((*lst)->av[++i] != NULL)
			free((*lst)->av[i]);
		free((*lst)->av);
		free((*lst)->path);
		free(*lst);
		*lst = temp;
	}
}

void	ft_free_all(t_list *input, char **paths)
{
	int	i;

	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	ft_free_list(&input);
}

void	ft_free_rest(char **first_command)
{
	int	i;

	i = 0;
	if (!first_command[i])
		return ;
	while (first_command[++i])
		free(first_command[i]);
}

void	ft_free_first_command(char **first_command)
{
	free(first_command[0]);
	free(first_command);
}
