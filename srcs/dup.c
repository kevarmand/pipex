/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kearmand <kearmand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 12:58:14 by kearmand          #+#    #+#             */
/*   Updated: 2025/02/15 12:49:36 by kearmand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*****
 *  infile   ------ cmd0 ---- pipe 0[1]
 * pipe 0[0] ------ cmd1 ---- pipe 1[1]
 * pipe 1[0] ------ cmd2 ---- pipe 2[1]
 * pipe 2[0] ------ cmd3 ---- pipe 3[1]
 * 
 * pipe i-1[0] ---- cmd_i --- pipe i[1]
 * 
 * pipe nb-1[0] --- cmd_nb -- outfile
 * 
 * 				pipe_i[0] lecture
 * 				pipe_i[1] ecriture
 * 
 * redirect all the pipe
 */

int	ft_here_doc_outfile(t_data *data)
{
	int	fd;

	if (-1 == access(data->outfile, W_OK))
		return (error_access_file(data, data->outfile));
	fd = open(data->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (error_access_file(data, "open"));
	if (dup2(fd, 1) == -1)
		return (error_dup2(data));
	close(fd);
	return (0);
}

int	redirect_outfile(t_data *data)
{
	int	fd;
	
//	if (data->here_doc == 1)
//		return (ft_here_doc_outfile(data));
	if (-1 == access(data->outfile, W_OK))
		return (error_access_file(data, data->outfile));
	fd = open(data->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (error_access_file(data, "open"));
	if (dup2(fd, 1) == -1)
		return (error_dup2(data));
	close(fd);
	return (0);
}
int	ft_here_doc_infile(t_data *data)
{
	char	*line;
	char	*limiter;
	t_list	*lst;
	t_list	*tmp;
	//creer une liste chainee pour stocker les here doc
	// utiliser GNL pour lire les here doc
	
	lst = NULL;
	limiter = data->infile;
	while (1)
	{
		line = get_next_line(0);
		if (line == NULL)
			break ;
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
		{
			free(line);
			break ;
		}
		tmp = ft_lstnew(line);
		if (tmp == NULL)
		{
			ft_lstclear(&lst, free);
			return (error_access_file(data, "malloc"));
		}
		ft_lstadd_back(&lst, tmp);
	}
	close(1);
	while (lst)
	{
		line = lst->content;
		write(0, line, ft_strlen(line));
		tmp = lst;
		lst = lst->next;
		free(tmp->content);
		free(tmp);
	}
	
	close(0);
	return (0);
}

int	redirect_infile(t_data *data)
{
	int	fd;

	if (data->here_doc == 1)
		return (ft_here_doc_infile(data));
	if (-1 == access(data->infile, R_OK))
		return (error_access_file(data, data->infile));
	fd = open(data->infile, O_RDONLY);
	if (fd == -1)
		return (error_access_file(data, "open"));
	if (dup2(fd, 0) == -1)
		return (error_dup2(data));
	close(fd);
	return (0);
}

void	write_error(char *str, int i)
{
	char str2[1000];
	int j;

	j = 0;
	j += sprintf(str2, "Child: %d ", i);
	j += sprintf(str2 + j, "%s\n", str);
	write(2, str2, j);
}


int	redirect_pipe(t_data *data, int i)
{
	write_error("debut", i);
	if (i == 0)
	{
		if (redirect_infile(data) == 1)
			return(1);
	}
	else if (-1 == dup2(data->pipe[i - 1][0], 0))
	{
		perror("dup2");
		return(1);
	}
	write_error("inter",i);
	if (i == data->cmd_nb - 1)
	{
		if(redirect_outfile(data) == 1)
			return(1);
	}
	else if (-1 == dup2(data->pipe[i][1], 1))
	{

		perror("dup2");
		return(1);
	}
	write_error("end",i);
	return(0);
}
