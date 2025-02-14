/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kearmand <kearmand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:15:56 by kearmand          #+#    #+#             */
/*   Updated: 2025/02/14 15:15:18 by kearmand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec_child_cmd(t_data *data, int i, char **env)
{
	char **cmd;
	char *tmp;
	
	redirect_pipe(data, i);
	close_pipe(data);
	cmd = ft_split(data->cmd[i], ' ');
	if (cmd == NULL)
	{
		write(2, "Error: Malloc failed\n", 21);
		free_memory(data);
		exit(1);
	}
	tmp = gen_cmd(data, cmd[0]);
	if (tmp == NULL)
	{
		ft_putstr_fd(cmd[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		free(tmp);
		free_tab(cmd);
		free_memory(data);
		exit(1);
	}
	execve(tmp, cmd, env);
	perror(cmd[0]);
	free(tmp);
	free_tab(cmd);
	free_memory(data);
	exit(127);
}
