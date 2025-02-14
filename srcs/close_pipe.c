/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kearmand <kearmand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 12:52:38 by kearmand          #+#    #+#             */
/*   Updated: 2025/02/14 17:55:56 by kearmand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*****
 * Close all the pipe
 */
void	close_pipe(t_data *data)
{
	int	j;

	j = 0;
	while (j < data->cmd_nb - 1)
	{
		close(data->pipe[j][0]);
		close(data->pipe[j][1]);
		j++;
	}
}
