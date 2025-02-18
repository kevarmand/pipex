/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kearmand <kearmand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:15:33 by kearmand          #+#    #+#             */
/*   Updated: 2025/02/18 15:02:16 by kearmand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	wait_child(int nb_child, int pid, t_data *data);

/****
 * Create a child process for each command
 * Wait for all the child process
 */
void	dispatch_cmd(t_data *data, char **env)
{
	int	i;
	int	pid;

	i = 0;
	while (i < data->cmd_nb)
	{
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			break ;
		}
		if (pid == 0)
			exec_child_cmd(data, i, env);
		i++;
	}
	close_pipe(data);
	wait_child(i, pid, data);
}

static void	wait_child(int nb_child, int pid_save, t_data *data)
{
	int	i;
	int	status;
	int	pid;

	i = 0;
	while (i < nb_child)
	{
		pid = waitpid(-1, &status, 0);
		i++;
		if (pid == pid_save)
			data->return_value = WEXITSTATUS(status);
	}
}
