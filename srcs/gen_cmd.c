/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kearmand <kearmand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:39:44 by kearmand          #+#    #+#             */
/*   Updated: 2025/02/18 10:29:24 by kearmand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*****
 * Generate a command with the path
 * In case of a command with a path, return the command
 * In the other case try to find the command in the PATH
 */
char	*gen_cmd(t_data *data, char *cmd)
{
	int		i;
	char	*tmp;

	i = 0;
	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	while (data->path[i])
	{
		tmp = ft_strjoin(data->path[i], cmd);
		if (tmp == NULL)
		{
			ft_putstr_fd("Error: Malloc failed\n", 2);
			return (NULL);
		}
		if (access(tmp, F_OK) == 0 && access(tmp, X_OK) == 0)
			return (tmp);
		free (tmp);
		i++;
	}
	return (NULL);
}
