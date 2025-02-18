/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kearmand <kearmand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 10:50:02 by kearmand          #+#    #+#             */
/*   Updated: 2025/02/18 14:40:15 by kearmand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	error_access_file(t_data *data, char *str)
{
	int	save_errno;

	save_errno = errno;
	ft_putstr_fd(data->name, 2);
	ft_putstr_fd(": ", 2);
	errno = save_errno;
	perror(str);
	return (1);
}

int	exit_no_cmd(char *tmp, t_data *data, char **cmd, int i)
{
	int	save_errno;

	save_errno = errno;
	ft_putstr_fd(data->name, 2);
	ft_putstr_fd(": ", 2);
	if (tmp == 0)
	{
		ft_putstr_fd(cmd[0], 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	else
	{
		errno = save_errno;
		perror(tmp);
		free(tmp);
	}
	if (i == data->cmd_nb - 1)
		data->return_value = 127;
	free_tab(cmd);
	free_memory(data);
	exit(127);
}

int	error_open(t_data *data, char *str)
{
	int	save_errno;

	save_errno = errno;
	if (errno == 127)
	{
		ft_putstr_fd(data->name, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": Is a directory\n", 2);
	}
	else
	{
		ft_putstr_fd(data->name, 2);
		ft_putstr_fd(": ", 2);
		errno = save_errno;
		perror(str);
	}
	return (1);
}
