/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping_utils4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:57:10 by grebrune          #+#    #+#             */
/*   Updated: 2024/06/12 14:42:28 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	fill_fd(size_t numb, int **fd, t_head *head)
{
	size_t	i;

	i = 0;
	while (i < numb - 1)
	{
		if (pipe(fd[i]) == -1)
		{
			perror("pipe");
			free_pipe(fd, head);
			ft_free_all(head);
			exit (1);
		}
		i++;
	}
	fd[i][1] = 1;
	return (0);
}

void	close_pipe(t_head *head, int **fd)
{
	size_t	i;
	size_t	nbr_cmd;

	i = 0;
	nbr_cmd = cmdlen(head->cmd);
	while (i < nbr_cmd - 1)
	{
		close(fd[i][0]);
		close(fd[i][1]);
		i++;
	}
}

int	redir_with_fd(int fd[2], int **pipe, t_cmd *copy, int x)
{
	if (open_redir(copy, fd))
		return (2);
	if (fd[0] != 0 && copy->prev && !copy->redir)
		fd[0] = pipe[x - 1][0];
	if (fd[1] != 1 && copy->next && !copy->redir)
		fd[1] = pipe[x][1];
	if (fd[0] != 0 && (copy->prev || copy->redir))
	{
		if (dup2(fd[0], STDIN_FILENO) < 0)
			return (perror("dup2"), 2);
	}
	if (fd[1] != 1 && (copy->next || copy->redir))
	{
		if (dup2(fd[1], STDOUT_FILENO) < 0)
			return (perror("dup2"), 2);
	}
	return (0);
}