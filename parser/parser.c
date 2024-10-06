/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:43:35 by dhasan            #+#    #+#             */
/*   Updated: 2024/10/06 20:10:32 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_texture(char *contect, t_data *data)
{
	char	**texture;
	char	*path;
	int		i;

	texture = ft_split(contect, ' ');
	if (texture[1])
	{
		path = ft_strtrim(texture[1], " \t\n\r\v\f");
		if (texture[2] || !check_texture(path))
			msg_exit("Error\nInvalid texture.", 1);
		if (!ft_strncmp(texture[0], "NO", 3))
			data->no_texture = ft_strdup(path);
		else if (!ft_strncmp(texture[0], "SO", 3))
			data->so_texture = ft_strdup(path);
		else if (!ft_strncmp(texture[0], "WE", 3))
			data->we_texture = ft_strdup(path);
		else if (!ft_strncmp(texture[0], "EA", 3))
			data->ea_texture = ft_strdup(path);
		free(path);
		path = NULL;
	}
	i = 0;
	while (texture[i])
		free(texture[i++]);
	texture = NULL;
}

void	parse_color(char *contect, t_data *data, char type)
{
	char	**colors;
	int		rgb[3];
	int		i;

	colors = ft_split(contect, ',');
	if (!check_color(colors))
		msg_exit("Error\nInvalid color.", 1);
	rgb[0] = ft_atoi(colors[0]);
	rgb[1] = ft_atoi(colors[1]);
	rgb[2] = ft_atoi(colors[2]);
	if (type == 'f')
		data->floor_c = convert_rgb(rgb[0], rgb[1], rgb[2], 255);
	else
		data->ceiling_c = convert_rgb(rgb[0], rgb[1], rgb[2], 255);
	i = 0;
	while (colors[i])
		free(colors[i++]);
	colors = NULL;
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
	char	*content;
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		msg_exit("Error\nFile does not exist or is not readable.", 1);
	content = skip_nl(fd);
	while (content)
	{
		if (is_texture(content))
			parse_texture(content, data);
		else if (*content == 'F')
			parse_color(content + 2, data, 'f');
		else if (*content == 'C')
			parse_color(content + 2, data, 'c');
		else
		{
			parse_map(fd, data, content);
			break ;
		}
		free(content);
		content = skip_nl(fd);
	}
	close(fd);
}

void	parser(char *file, t_data *data)
{
	check_extension(file);
	read_file(file, data);
}
