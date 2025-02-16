/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kearmand <kearmand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 16:05:21 by kearmand          #+#    #+#             */
/*   Updated: 2025/02/16 17:16:28 by kearmand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// int	ft_here_doc_infile(t_data *data)
// {
// 	char	*line;
// 	char	*limiter;
// 	t_list	*lst;
// 	t_list	*tmp;
	
// 	lst = NULL;
// 	limiter = data->infile;
// 	while (1)
// 	{
// 		line = get_next_line(0);
// 		if (line == NULL)
// 			break ;
// 		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
// 		{
// 			free(line);
// 			break ;
// 		}
// 		tmp = ft_lstnew(line);
// 		if (tmp == NULL)
// 		{
// 			ft_lstclear(&lst, free);
// 			return (error_access_file(data, "malloc"));
// 		}
// 		ft_lstadd_back(&lst, tmp);
// 	}
// 	close(1);
// 	while (lst)
// 	{
// 		line = lst->content;
// 		write(0, line, ft_strlen(line));
// 		tmp = lst;
// 		lst = lst->next;
// 		free(tmp->content);
// 		free(tmp);
// 	}
	
// 	close(0);
// 	return (0);
// }
//new implementation with a tmp file
int	ft_here_doc_infile(t_data *data)
{
	char	*line;
	char	*limiter;
	int		fd;
	
	//creation d un pipe suplementaire pour le here_doc
	int pipefd[2];
	if (pipe(pipefd) == -1)
		return (error_access_file(data, "pipe"));
	
	//creation d un child process
	int pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (1);
	}
	if (pid == 0)
	{
		fd = open("/tmp", O_WRONLY | __O_TMPFILE, 0644); //create a tmp file
		if (fd == -1)
			return (error_access_file(data, "open"));
		limiter = data->infile;
		while (1)
		{
			line = get_next_line(0);
			if (line == NULL)
				break ;
			if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
			{
				free(line);
				break ;
			}
			write(fd, line, ft_strlen(line));
			write(fd, "\n", 1);
			free(line);
		}
		printf("fd1 = %d\n", fd);
		int fd2 = open("/tmp", O_RDONLY); //open the tmp file
		if (fd2 == -1)
			return (error_access_file(data, "open"));
		printf("fd2 = %d\n", fd2);
		if (dup2(fd2, 0) == -1) //redirect the tmp file to stdin
			return (error_dup2(data));
		
		close(fd); //si on close le file descriptor, on ne peut plus le lire car il s agit d un tmp file
		close(fd2);
		close(pipefd[0]);
		close(pipefd[1]);
		exit(0);
	}
	else
	{
		close(pipefd[1]);
		if (dup2(pipefd[0], 0) == -1) //redirect the pipe to stdin
			return (error_dup2(data));
		close(pipefd[0]);
	}
	return (0);
}
