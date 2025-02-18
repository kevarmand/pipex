/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kearmand <kearmand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 12:58:14 by kearmand          #+#    #+#             */
/*   Updated: 2025/02/18 13:15:57 by kearmand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*****
 *  infile   ------ cmd0 ---- pipe 0[1]
 * pipe 0[0] ------ cmd1 ---- pipe 1[1]
 * pipe 1[0] ------ cmd2 ---- pipe 2[1]
 * pipe 2[0] ------ cmd3 ---- pipe 3[1]
 * 
 * pipe i-1[0] ---- cmd_i --- pipe i[1]
 * 
 * pipe nb-1[0] --- cmd_nb -- outfile
 * 
 * 				pipe_i[0] lecture
 * 				pipe_i[1] ecriture
 * 
 * redirect all the pipe
 */

int	redirect_outfile(t_data *data)
{
	int	fd;

	if (data->here_doc == 1)
		return (here_doc_outfile(data));
	if (-1 != access(data->outfile, F_OK) && -1 == access(data->outfile, W_OK))
		return (error_access_file(data, data->outfile));
	fd = open(data->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
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

int	redirect_infile(t_data *data)
{
	int	fd;

	if (data->here_doc == 1)
		return (0);
	if (-1 == access(data->infile, R_OK))
		return (error_access_file(data, data->infile));
	fd = open(data->infile, O_RDONLY);
	if (fd == -1)
		return (error_open(data, data->infile));
	if (dup2(fd, 0) == -1)
	{
		close(fd);
		perror("dup2");
		return (1);
	}
	close(fd);
	return (0);
}

int	redirect_pipe(t_data *data, int i)
{
	if (i == 0)
	{
		if (redirect_infile(data) == 1)
			return (1);
	}
	else if (-1 == dup2(data->pipe[i - 1][0], 0))
	{
		perror("dup2");
		return (1);
	}
	if (i == data->cmd_nb - 1)
	{
		if (redirect_outfile(data) == 1)
			return (1);
	}
	else if (-1 == dup2(data->pipe[i][1], 1))
	{
		perror("dup2");
		return (1);
	}
	return (0);
}
