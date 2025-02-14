/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kearmand <kearmand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 10:39:00 by kearmand          #+#    #+#             */
/*   Updated: 2025/02/14 17:56:01 by kearmand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int main(int ac, char **av, char **env)
{
	t_data	data;

	init_memory(&data);
	if (parse(av, ac, &data, env))
		return (0);
	if (init_pipe(&data))
		return (free_memory(&data), 0);
	dispatch_cmd(&data, env);
	free_memory(&data);
	return (0);
}
