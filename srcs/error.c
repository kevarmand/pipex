/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kearmand <kearmand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 10:50:02 by kearmand          #+#    #+#             */
/*   Updated: 2025/02/15 10:59:35 by kearmand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	error_access_file(t_data *data, char *str)
{
	ft_putstr_fd(data->name, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	perror(data->infile);
	return (1);
}

int	error_dup2(t_data *data)
{
	ft_putstr_fd(data->name, 2);
	ft_putstr_fd(": ", 2);
	perror("dup2");
	return (1);
}