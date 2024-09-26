/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:43:35 by dhasan            #+#    #+#             */
/*   Updated: 2024/09/26 20:16:00 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_texture(char *contect, t_data *data)
{
	char	**texture;
	char	*path;

	texture = ft_split(contect, ' ');
	if (texture[1])
	{
		path = ft_strtrim(texture[1], " \t\n\r\v\f");
		if (texture[2] || !check_texture(path))
			msg_exit("Error\nInvalid texture.", 1);
		if (!ft_strncmp(texture[0], "NO ", 3))
			data->no_texture = ft_strdup(path);
		else if (!ft_strncmp(texture[0], "SO ", 3))
			data->so_texture = ft_strdup(path);
		else if (!ft_strncmp(texture[0], "WE ", 3))
			data->we_texture = ft_strdup(path);
		else if (!ft_strncmp(texture[0], "EA ", 3))
			data->ea_texture = ft_strdup(path);
		free(path);
	}
	free(texture);
}

void	parse_color(char *contect, int *color)
{
	char	**rgb;

	rgb = ft_split(contect, ',');
	if (!check_color(rgb))
		msg_exit("Error\nInvalid color.", 1);
	color[0] = ft_atoi(rgb[0]);
	color[1] = ft_atoi(rgb[1]);
	color[2] = ft_atoi(rgb[2]);
}

void	parse_map(int fd, t_data *data, char *line)
{
	data->pos_x = -1;
	data->pos_y = -1;

	file_to_map(fd, data, line);
	char_check(data);
	is_map_enclosed(data);
}

void	read_file(char *file, t_data *data)
{
	char	*contect;
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		msg_exit("Error\nFile does not exist or is not readable.", 1);
	contect = skip_nl(fd);
	while (contect)
	{
		if (is_texture(contect))
			parse_texture(contect, data);
		else if (*contect == 'F')
			parse_color(contect + 2, data->floor_color);
		else if (*contect == 'C')
			parse_color(contect + 2, data->ceiling_color);
		else
		{
			parse_map(fd, data, contect);
			break ;
		}
		free(contect);
		contect = skip_nl(fd);
	}
	close(fd);
}

void	parser(char *file, t_data *data)
{
	check_extension(file);
	read_file(file, data);
}
