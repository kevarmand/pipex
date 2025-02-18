/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kearmand <kearmand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 10:39:00 by kearmand          #+#    #+#             */
/*   Updated: 2025/02/18 15:12:37 by kearmand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **env)
{
	t_data	data;

	init_memory(&data);
	if (parse(av, ac, &data, env))
	{
		free_memory(&data);
		return (1);
	}
	if (init_pipe(&data))
	{
		free_memory(&data);
		return (1);
	}
	dispatch_cmd(&data, env);
	free_memory(&data);
	return (data.return_value);
}
