/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsa-mora <dsa-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 17:16:16 by dsa-mora          #+#    #+#             */
/*   Updated: 2023/03/01 13:35:28 by dsa-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

//Esta funcao cria um nó
t_list	*ft_lstnew(char *file, char *cmd, char *path)
{
	t_list	*new;


	new = (t_list *)ft_calloc(sizeof(t_list), 1);
	if (!new)
		return (NULL);
	new->file = file;
	new->av = ft_split(cmd, ' ');
	new->cmd = new->av[0];
	if (pipe(new->fd) == -1)
		printf("Error\n");
	new->path = path;
	return (new);
}

//Esta funcao retorna o ultimo elemento de uma linked list
t_list	*ft_lstlast(t_list *lst)
{
	while (lst)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

//Esta funcao acrescenta um ultimo elemento na linked list
//Ou seja, coloca o last->next a apontar para o new
void	ft_lstadd_back(t_list **lst, t_list *new)
{
	if (lst)
	{
		if (*lst)
		{
			new->prev = ft_lstlast(*lst);
			ft_lstlast(*lst)->next = new;
		}
		else
			*lst = new;
	}
}

//Esta funcao retorna o content de um dado 
//indice de um elemento da linked list
char	*ft_get_cmd(int index, t_list *lst)
{
	int	i;

	i = 0;
	while (i < index)
	{
		i++;
		lst = lst->next;
	}
	return (lst->cmd);
}
