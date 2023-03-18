/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parents.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsa-mora <dsa-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 12:41:04 by dsa-mora          #+#    #+#             */
/*   Updated: 2023/03/18 18:36:06 by dsa-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_pre_father(t_list *input)
{
	(data()->i)++;
	if (!input->prev)
		dup2(data()->fd_in, 0);
	else
	{
		dup2(input->prev->fd[0], 0);
		close(input->prev->fd[0]);
	}
}

void	error_handle(char *cmd)
{
	int	i;

	i = 0;
	if (!cmd[i] || !cmd)
		write(2, "Permission denied\n", 18);
	else
	{
		write(2, "command not found: ", 19);
		while (cmd[i])
		{
			write(2, &(cmd[i]), 1);
			i++;
		}
		write(2, "\n", 1);
	}
}

void	ft_child(t_list *input, char *av_curr, char **env)
{
	if (!input->next)
	{
		dup2(data()->fd_out, 1);
		close(data()->fd_out);
	}
	else
		dup2(input->fd[1], 1);
	close(input->fd[0]);
	close(input->fd[1]);
	if (execve(input->path, input->av, env) == -1)
	{
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
		error_handle(av_curr);
		ft_free_all(data()->first, data()->paths);
		exit(1);
	}
}

void	ft_pos_father(t_list *input)
{
	close(0);
	close(input->fd[1]);
	if (!input->next)
		close(input->fd[0]);
}

//The 127 error code indicates “command not found”. 
//This occurs when any given command within your 
//Bash script or on Bash command line is not found 
//in any of the paths defined by PATH system environment variable.