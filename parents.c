/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parents.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsa-mora <dsa-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 12:41:04 by dsa-mora          #+#    #+#             */
/*   Updated: 2023/03/18 13:06:27 by dsa-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_pre_father(t_list *input)
{
	if (!input->prev)
		dup2(data()->fd_in, 0);
	else
	{
		dup2(input->prev->fd[0], 0);
		close(input->prev->fd[0]);
	}
}

void	ft_child(t_list *input, int fd_out, char **env)
{
	if (!input->next)
	{
		dup2(fd_out, 1);
		close(fd_out);
	}
	else
		dup2(input->fd[1], 1);
	close(input->fd[0]);
	close(input->fd[1]);
	if (execve(input->path, input->av, env) == -1)
		perror("Command not found");
	close(data()->fd_in);
	close(0);
	close(1);
	input = data()->first;
	while (input)
	{
		close(input->fd[0]);
		close(input->fd[1]);
		input = input->next;
	}
	ft_free_all(data()->first, data()->paths);
	exit(1);
}
