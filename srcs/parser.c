/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kearmand <kearmand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 11:54:06 by kearmand          #+#    #+#             */
/*   Updated: 2025/02/18 16:06:16 by kearmand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

/****
 * Add / at the end of the path
 */
int	parse_pathinette(t_data *data)
{
	int		i;
	char	*tmp;

	i = 0;
	while (data->path[i])
	{
		tmp = ft_strjoin(data->path[i], "/");
		if (tmp == NULL)
		{
			ft_putstr_fd("Error: Malloc failed\n", 2);
			return (-1);
		}
		free(data->path[i]);
		data->path[i] = tmp;
		i++;
	}
	return (0);
}

/****
 * Parse the PATH
 */
int	parse_path(t_data *data, char **env)
{
	if (!env || !env[0])
	{
		ft_putstr_fd("Error: env not found\n", 2);
		return (-1);
	}
	while (*env && ft_strncmp(*env, "PATH=", 5))
		env++;
	if (!*env)
	{
		ft_putstr_fd("Error: PATH not found\n", 2);
		return (-1);
	}
	*env += 5;
	data->path = ft_split(*env, ':');
	if (data->path == NULL)
	{
		ft_putstr_fd("Error: Malloc failed\n", 2);
		return (-1);
	}
	return (parse_pathinette(data));
}

/****
 * Parse the command line
 */
int	parsinette(char **av, int ac, t_data *data, char **env)
{
	int	i;

	i = 0;
	data->infile = av[1];
	data->outfile = av[ac - 1];
	data->cmd = malloc(sizeof(char *) * (ac - 3));
	if (data->cmd == NULL)
	{
		ft_putstr_fd("Error: Malloc failed\n", 2);
		return (1);
	}
	while (i < ac - 3)
	{
		data->cmd[i] = av[i + 2];
		i++;
	}
	data->cmd_nb = i;
	if (data->here_doc == 1)
		here_doc_infile (data);
	return (parse_path(data, env));
}

/***
 * Store the name of the command in data
 */
char	*normalise_name(char *av)
{
	char	*tmp;

	tmp = ft_strrchr(av, '/');
	if (tmp == NULL)
		return (av);
	return (tmp + 1);
}

/****
 * Init the parsing
 */
int	parse(char **av, int ac, t_data *data, char **env)
{
	if (ac < 5)
	{
		ft_putstr_fd("Error: Not enough arguments\n", 2);
		return (1);
	}
	data->name = normalise_name(av[0]);
	if (ft_strncmp(av[1], "here_doc", 9) == 0)
	{
		if (ac < 6)
		{
			ft_putstr_fd("Error: Not enough arguments\n", 2);
			return (1);
		}
		data->here_doc = 1;
		av++;
		ac--;
	}
	return (parsinette(av, ac, data, env));
}
