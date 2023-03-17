/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsa-mora <dsa-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 10:05:41 by dsa-mora          #+#    #+#             */
/*   Updated: 2023/03/17 11:49:54 by dsa-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_list	*ft_set_input(char **av, int ac, char **paths)
{
	int		i;
	t_list	*input;

	input = ft_lstnew(av[2], ft_check_path(av[2], paths));
	i = 2;
	while (av[++i] && i < (ac - 1))
		ft_lstadd_back(&input, ft_lstnew(av[i], ft_check_path(av[i], paths)));
	return (input);
}

void	ft_child(t_list *input, int fd_out, char **env)
{
	close(input->fd[0]);
	if (!input->next)
	{
		dup2(fd_out, 1);
		close(fd_out);
	}
	else
	{
		dup2(input->fd[1], 1);
		close(input->fd[1]);
	}
	if (execve(input->path, input->av, env) == -1)
		perror("Command not found");
}

// void	free_and_close(t_list *input)
// {
// 	t_list	*temp;

// 	input = temp;
// 	while (input)
// 	{
// 		wait(NULL);
// 		input = input->next;
// 	}
// 	input = temp;
// 	close(info.fd_in);
// 	close(info.fd_out);
// 	if (info.flag)
// 		unlink(".temp");
// 	ft_free_all(input, info.paths);
// }

int main(int ac, char **av, char **env)
{
	t_list	*input;
	t_list	*temp;
	t_info	info;

	info.fd_in = open(av[1], O_RDWR);
	info.flag = 0;
	if (info.fd_in == -1)
	{
		info.fd_in = open(".temp", O_RDWR | O_CREAT, 0644);
		info.flag = 6;
		perror(av[1]);
	}
	info.fd_out = open(av[ac - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (info.fd_out == -1)
		perror("");
	info.paths = ft_get_path(env);
	input = ft_set_input(av, ac, info.paths);
	temp = input;
	while (input)
	{
		if (!input->prev)
			dup2(info.fd_in, 0);
		else
		{
			dup2(input->prev->fd[0], 0);
			close(input->prev->fd[0]);
		}
		info.pid = fork();
		if (info.pid == 0)
		{
			close(input->fd[0]);
			if (!input->next)
			{
				dup2(info.fd_out, 1);
				close(info.fd_out);
			}
			else
			{
				dup2(input->fd[1], 1);
				close(input->fd[1]);
			}
			execve(input->path, input->av, env);
		}
			//ft_child(input, info.fd_out, env);
		if (!input->prev)
			close(0);
		close(input->fd[1]);
		input = input->next;
	}
	input = temp;
	while (input)
	{
		wait(NULL);
		input = input->next;
	}
	input = temp;
	ft_free_all(input, info.paths);
	if (info.flag)
		unlink(".temp");
	close(info.fd_in);
	close(info.fd_out);
}

// void	ft_print_list(t_list *input)
// {
// 	while (input)
// 	{
// 		printf("cmd: %s\n", input->cmd);
// 		printf("path: %s\n", input->path);
// 		printf("av[0]: %s\n", input->av[0]);
// 		printf("av[1]: %s\n", input->av[1]);
// 		printf("fd in[1] %i and fd out[0] %i\n", input->fd[1], input->fd[0]);
// 		input = input->next;
// 	}
// }