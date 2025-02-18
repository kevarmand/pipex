/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kearmand <kearmand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:34:15 by kearmand          #+#    #+#             */
/*   Updated: 2025/02/18 14:36:19 by kearmand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_memory(t_data *data)
{
	data->path = NULL;
	data->infile = NULL;
	data->infile_fd = -1;
	data->outfile = NULL;
	data->outfile_fd = -1;
	data->cmd = NULL;
	data->cmd_nb = 0;
	data->pipe = NULL;
	data->here_doc = 0;
	data->name = NULL;
	data->return_value = 0;
}
