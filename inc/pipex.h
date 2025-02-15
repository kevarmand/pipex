/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kearmand <kearmand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 10:40:19 by kearmand          #+#    #+#             */
/*   Updated: 2025/02/15 11:36:54 by kearmand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include "libft.h"
#include <sys/wait.h>

typedef struct s_data
{
	char	**path;
	char	*infile;
	int		infile_fd;
	char	*outfile;
	int		outfile_fd;
	char	**cmd;
	int		cmd_nb;
	int		**pipe;
	int		here_doc;
	char	*name;
	
}	t_data;


int		parse(char **av, int ac, t_data *data, char **env);
char	*gen_cmd(t_data *data, char *cmd);
int		parse_path(t_data *data, char **env);
char	normilize_name(char *av);

void	print_tab(char **tab);

int		free_memory(t_data *data);
void	free_tab(char **cmd);
void	init_memory(t_data *data);
int		init_pipe(t_data *data);

void	close_pipe(t_data *data);
int		redirect_pipe(t_data *data, int i);

void	dispatch_cmd(t_data *data, char **env);
void 	exec_child_cmd(t_data *data, int i, char **env);

int		error_access_file(t_data *data, char *str);
int		error_dup2(t_data *data);

#endif