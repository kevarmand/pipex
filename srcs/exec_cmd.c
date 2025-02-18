/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kearmand <kearmand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:15:56 by kearmand          #+#    #+#             */
/*   Updated: 2025/02/18 14:36:41 by kearmand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec_child_cmd(t_data *data, int i, char **env)
{
	char	**cmd;
	char	*tmp;
	int		test;

	test = redirect_pipe(data, i);
	close_pipe(data);
	if (test != 0)
	{
		free_memory(data);
		exit(1);
	}
	cmd = ft_split(data->cmd[i], ' ');
	if (cmd == NULL)
	{
		ft_putstr_fd("Error: Malloc failed\n", 2);
		free_memory(data);
		exit(1);
	}
	tmp = gen_cmd(data, cmd[0]);
	if (tmp == NULL)
		exit_no_cmd(tmp, data, cmd, i);
	execve(tmp, cmd, env);
	exit_no_cmd(tmp, data, cmd, i);
}
