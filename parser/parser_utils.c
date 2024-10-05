/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:45:31 by dhasan            #+#    #+#             */
/*   Updated: 2024/10/05 17:53:47 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int32_t	convert_rgb(int r, int g, int b, int a)
{
	return ((r << 24) | (g << 16) | (b << 8) | a);
}

char	*skip_nl(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line && *line == '\n')
	{
		free(line);
		line = get_next_line(fd);
	}
	return (line);
}

bool	is_texture(char *contect)
{
	if (!ft_strncmp(contect, "NO ", 3))
		return (true);
	if (!ft_strncmp(contect, "SO ", 3))
		return (true);
	if (!ft_strncmp(contect, "WE ", 3))
		return (true);
	if (!ft_strncmp(contect, "EA ", 3))
		return (true);
	return (false);
}

bool	is_color(char *contect)
{
	if (!ft_strncmp(contect, "F ", 2))
		return (true);
	if (!ft_strncmp(contect, "C ", 2))
		return (true);
	return (false);
}

char	*skip_info(int fd)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
		msg_exit("Error\nMissing information.\n", 1);
	while (line && (is_texture(line) || *line == 'F' || *line == 'C'))
	{
		free(line);
		line = get_next_line(fd);
	}
	return (line);
}
