/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kearmand <kearmand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:34:44 by kearmand          #+#    #+#             */
/*   Updated: 2025/02/18 14:04:11 by kearmand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//BC:87:FA:9C:CF:E9

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (tab == NULL)
		return ;
	while (tab[i])
	{
		free (tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
	tab = NULL;
}

int	free_memory(t_data *data)
{
	int	i;

	i = -1;
	if (data->path)
		free_tab(data->path);
	data->path = NULL;
	if (data->cmd)
	{
		free(data->cmd);
		data->cmd = NULL;
	}
	if (data->pipe)
	{
		while (++i < data->cmd_nb - 1 && data->pipe[i])
		{
			free (data->pipe[i]);
			data->pipe[i] = NULL;
		}
		free (data->pipe);
		data->pipe = NULL;
	}
	return (0);
}
