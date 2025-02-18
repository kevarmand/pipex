/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kearmand <kearmand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 16:05:21 by kearmand          #+#    #+#             */
/*   Updated: 2025/02/18 14:20:25 by kearmand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	here_doc_infile(t_data *data)
{
	char	*line;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
		return (perror("pipe"), 1);
	while (1)
	{
		line = get_next_line(0);
		if (line == NULL || ft_strncmp(line, data->infile,
				ft_strlen(data->infile)) == 0)
			break ;
		write(pipefd[1], line, ft_strlen(line));
	}
	close(pipefd[1]);
	dup2(pipefd[0], 0);
	close(pipefd[0]);
	return (0);
}

int	here_doc_outfile(t_data *data)
{
	int	fd;

	if (-1 != access(data->outfile, F_OK) && -1 == access(data->outfile, W_OK))
		return (error_access_file(data, data->outfile));
	fd = open(data->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (error_open(data, data->outfile));
	if (dup2(fd, 1) == -1)
	{
		close(fd);
		perror("dup2");
		return (1);
	}
	close(fd);
	return (0);
}
