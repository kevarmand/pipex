/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kearmand <kearmand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 17:07:20 by kearmand          #+#    #+#             */
/*   Updated: 2025/02/14 17:58:27 by kearmand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	init_pipe(t_data *data)
{
	int i;

	data->pipe = malloc(sizeof(int *) * (data->cmd_nb - 1));
	if (data->pipe == NULL)
	{
		ft_putstr_fd("Error: Malloc failed\n", 2);
		return (-1);
	}
	i = 0;
	while (i < data->cmd_nb - 1)
	{
		data->pipe[i] = malloc(sizeof(int) * 2);
		if (data->pipe[i] == NULL)
		{
			ft_putstr_fd("Error: Malloc failed\n", 2);
			return (-1);
		}
		if (pipe(data->pipe[i]) == -1)
		{
			perror("pipe");
			data->pipe[i] = NULL;
			return (-1);
		}
		i++;
	}
	return (0);
}
