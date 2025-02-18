/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kearmand <kearmand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 17:07:20 by kearmand          #+#    #+#             */
/*   Updated: 2025/02/18 14:26:57 by kearmand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	close_pipe_fail(t_data *data, int i);

/****
 * Malloc the tab of pipe
 * Create all the pipe
 */
int	init_pipe(t_data *data)
{
	int	i;

	data->pipe = malloc(sizeof(int *) * (data->cmd_nb - 1));
	if (data->pipe == NULL)
		return (ft_putstr_fd("Error: Malloc failed\n", 2), -1);
	i = -1;
	while (++i < data->cmd_nb - 1)
	{
		data->pipe[i] = malloc(sizeof(int) * 2);
		if (data->pipe[i] == NULL)
		{
			ft_putstr_fd("Error: Malloc failed\n", 2);
			return (close_pipe_fail(data, i));
		}
		if (pipe(data->pipe[i]) == -1)
		{
			perror("pipe");
			free(data->pipe[i]);
			data->pipe[i] = NULL;
			return (close_pipe_fail(data, i));
		}
	}
	return (0);
}

/****
 * Close all the pipe in case of fail
 */
static int	close_pipe_fail(t_data *data, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		close(data->pipe[j][0]);
		close(data->pipe[j][1]);
		j++;
	}
	return (-1);
}
