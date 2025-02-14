/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kearmand <kearmand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 12:58:14 by kearmand          #+#    #+#             */
/*   Updated: 2025/02/14 18:11:44 by kearmand         ###   ########.fr       */
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

int	redirect_infile(t_data *data)
{
	int fd;

	fd = open(data->infile, O_RDONLY);
	if (fd == -1)
	{
		perror(data->infile);
		exit(1);// a gerer differe;et apres
	}
	int test = dup2(fd, 0);
	if (test == -1)
	{
		write(2, "Error: Dup2 failed\n", 19);
		exit(1);
	}
	close(fd);
}

int	redirect_outfile(t_data *data)
{
	int fd;

	fd = open(data->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		write(2, "Error: Open failed\n", 19);
		exit(1);
	}
	int test = dup2(fd, 1);
	if (test == -1)
	{
		write(2, "Error: Dup2 failed\n", 19);
		exit(1);
	}
	close(fd);
} 

void	redirect_pipe(t_data *data, int i)
{
	if (i == 0 && redirect_infile(data) == 1)
		return(1);
	else if (-1 == dup2(data->pipe[i - 1][0], 0))
	{
		perror("dup2");
		return(1);
	}
	if (i == data->cmd_nb - 1 && redirect_outfile(data) == 1)
		return(1);
	else if (-1 == dup2(data->pipe[i][1], 1))
	{
		perror("dup2");
		return(1);
	}
	return(0);
}
