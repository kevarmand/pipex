/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kearmand <kearmand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 11:54:06 by kearmand          #+#    #+#             */
/*   Updated: 2025/02/15 12:45:39 by kearmand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	parse_path(t_data *data, char **env)
{
	int i;
	char *tmp;
	
	while (ft_strncmp(*env, "PATH=", 5) != 0)
		env++;
	if (*env == NULL)
	{
		ft_printf("Error: PATH not found\n");
		return (-1);
	}
	*env += 5;
	data->path = ft_split(*env, ':');
	if (data->path == NULL)
	{
		ft_printf("Error: Malloc failed\n");
		return (-1);
	}
	i = 0;
	while(data->path[i])
	{
		tmp = ft_strjoin(data->path[i], "/");
		if (tmp == NULL)
		{
			ft_printf("Error: Malloc failed\n");
			return (-1);
		}
		free(data->path[i]);
		data->path[i] = tmp;
		i++;
	}
	//afficher les commande
	for (int j = 0; data->cmd_nb > j; j++)
	{
		ft_printf("cmd[%d]: %s\n", j, data->cmd[j]);
	}
	printf("here_doc: %d\n", data->here_doc);
	printf("infile: %s\n", data->infile);
	return (0);
}

int	parsinette(char **av, int ac, t_data *data, char **env)
{
	int i;
	
	i = 0;
	data->infile = av[1];
	data->outfile = av[ac - 1];
	data->cmd = malloc(sizeof(char *) * (ac - 3));
	if (data->cmd == NULL)
	{
		ft_printf("Error: Malloc failed\n");
		return (1);
	}
	while (i < ac - 3)
	{
		data->cmd[i] = av[i + 2];
		i++;
	}
	data->cmd_nb = i;
	return (parse_path(data, env));
}

char	*normalise_name(char *av)
{
	char *tmp;
	
	tmp = ft_strrchr(av, '/');
	if (tmp == NULL)
		return (av);
	return (tmp + 1);
}

int	parse(char **av, int ac, t_data *data, char **env)
{
	if (ac < 5)
	{
		ft_printf("Error: Not enough arguments\n");
		return (1);
	}
	data->name = normalise_name(av[0]);
	if (ft_strncmp(av[1], "here_doc", 9) == 0)
	{
		if (ac < 6)
		{
			ft_printf("Error: Not enough arguments\n");
			return (1);
		}
		data->here_doc = 1;
		av++;
		ac--;
	}
	return (parsinette(av, ac, data, env));
}
