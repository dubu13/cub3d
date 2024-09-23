/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:43:35 by dhasan            #+#    #+#             */
/*   Updated: 2024/09/23 21:20:04 by dhasan           ###   ########.fr       */
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
		msg_exit("Error\nInvalid color.\n", 1);
	color[0] = ft_atoi(rgb[0]);
	color[1] = ft_atoi(rgb[1]);
	color[2] = ft_atoi(rgb[2]);
}

void	save_map_size(int fd, t_data *data)
{
	char			*line;
	unsigned int	i;

	i = 0;
	line = skip_info(fd);
	while (line)
	{
		if (line[0] == '\0' || line[0] == '\n')
			msg_exit("Error\nInvalid map.\n", 1);
		while (line[i])
		{
			if (!ft_strchr(" 01NSEW", line[i]))
				msg_exit("Error\nMap with invalid char.\n", 1);
			if (ft_strchr("NSEW", line[i]))
				save_position(data, i, data->height);
			i++;
		}
		if (i > data->width)
			data->width = i;
		data->height++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
}

void	parse_map(int fd, t_data *data)
{
	char			*line;
	unsigned int	y;

	data->pos_x = -1;
	data->pos_y = -1;
	y = 0;
	save_map_size(fd, data);
	data->map = ft_calloc(data->height, sizeof(char *));
	line = skip_info(fd);
	while (line && y < data->height)
	{
		data->map[y] = ft_strdup(line);
		free(line);
		line = get_next_line(fd);
		y++;
	}
}

void	read_file(char *file, t_data *data)
{
	char	*contect;
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		msg_exit("Error\nFile does not exist or is not readable.\n", 1);
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
			parse_map(fd, data);
			break ;
		}
		free(contect);
		contect = skip_nl(fd);
	}
	free(contect);
	close(fd);
}
