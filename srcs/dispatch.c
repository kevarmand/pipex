/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kearmand <kearmand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:15:33 by kearmand          #+#    #+#             */
/*   Updated: 2025/02/16 17:10:57 by kearmand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	wait_child(int nb_child);

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
		else
			printf("Child %d created : pid = %d\n", i, pid);
		i++;
	}
	close_pipe(data);
	wait_child(i);
}

static void	wait_child(int nb_child)
{
	int	i;
	int	status;

	i = 0;
	while (i < nb_child)
	{
		//utiliser waitpid pour attendre un enfant en particulier et afficher le status
		int pid = waitpid(-1, &status, 0);
		printf("Child %d terminated\n", pid);
		i++;
	}
}
