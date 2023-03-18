/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parents.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsa-mora <dsa-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 12:41:04 by dsa-mora          #+#    #+#             */
/*   Updated: 2023/03/18 14:01:22 by dsa-mora         ###   ########.fr       */
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
	if (!*cmd)
		write(2, "Permission denied\n", 18);
	else
	{
		write(2, "command not found: ", 19);
		while (*cmd)
		{
			write(2, cmd, 1);
			cmd++;
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
		if (input->next)
			error_handle(av_curr);
		input = data()->first;
		while (input)
		{
			close(input->fd[0]);
			close(input->fd[1]);
			input = input->next;
		}
		ft_free_all(data()->first, data()->paths);
		exit(127);
	}
}

//The 127 error code indicates “command not found”. 
//This occurs when any given command within your 
//Bash script or on Bash command line is not found 
//in any of the paths defined by PATH system environment variable.