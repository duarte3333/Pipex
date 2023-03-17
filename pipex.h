/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsa-mora <dsa-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 17:45:55 by dsa-mora          #+#    #+#             */
/*   Updated: 2023/03/17 18:26:54 by dsa-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <limits.h>
# include <unistd.h>
# include <sys/wait.h>
# include <stdio.h>
# include <fcntl.h>

typedef struct s_list
{
	char			*cmd;
	int				fd[2];
	char			*path;
	char			**av;
	struct s_list	*next;
	struct s_list	*prev;
}				t_list;

typedef struct s_info
{
	int		pid;
	int		fd_in;
	int		fd_out;
	int		flag;
	t_list	*first;
	char	**paths;
}				t_info;



//Checker and parsing
int		ft_atoi(const char *nptr);
int		ft_isdigit(int i);
size_t	ft_strlen(const char *str);
char	**ft_split(char const *str, char charset);
char	*ft_strjoinn(char *s1, char const *s2);
void	*ft_calloc(size_t nelem, size_t elsize);

//Lists auxiliary functions
t_list	*ft_lstnew(char *cmd, char *path);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);

//Path
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_get_path(char **env);
char	*ft_check_path(char *cmd, char **paths);

//Free stuff
void	ft_free_list(t_list **lst);
void	ft_free_all(t_list *input, char **paths);
void	ft_free_rest(char **first_command);
void	ft_free_first_command(char **first_command);

#endif