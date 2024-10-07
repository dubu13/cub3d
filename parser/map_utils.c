/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:15:05 by dhasan            #+#    #+#             */
/*   Updated: 2024/10/07 19:44:40 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	save_position(t_data *data, unsigned int x, unsigned int y)
{
	if (data->pos_x != -1 || data->pos_y != -1)
		return (error("Multiple player positions."), 0);
	data->pos_x = x;
	data->pos_y = y;
	data->dir = data->map[y][x];
	return (1);
}

int	char_check(t_data *data)
{
	unsigned int	y;
	unsigned int	x;

	y = 0;
	x = 0;
	while (data->map[y])
	{
		x = 0;
		if (data->map[y][0] == '\0' || data->map[y][0] == '\n')
			return (error("Invalid map."), 0);
		while (data->map[y][x])
		{
			if (!ft_strchr(" 01NSEW", data->map[y][x]))
				return (error("Map with invalid char."), 0);
			if (ft_strchr("NSEW", data->map[y][x]))
				if (!save_position(data, x, y))
					return (0);
			x++;
		}
		if (x > data->width)
			data->width = x;
		y++;
	}
	return (1);
}

int	check_nl(char *map)
{
	int	i;

	i = 0;
	while (map[i] != '\0')
	{
		if (map[i] == '\n' && map[i + 1] == '\n')
			return (error("Extra newline in map."), 0);
		i++;
	}
	return (1);
}

int	file_to_map(int fd, t_data *data, char *line)
{
	if (!line)
		return (error("Missing map."), 0);
	while (line)
	{
		data->map_temp = ft_strjoin_gnl(data->map_temp, line);
		free(line);
		if (!data->map_temp)
			return (error("Memory allocation failed."), 0);
		data->height++;
		line = get_next_line(fd);
	}
	free(line);
	if (!check_nl(data->map_temp))
		return (free(data->map_temp), 0);
	data->map = ft_split(data->map_temp, '\n');
	free(data->map_temp);
	data->map_temp = NULL;
	if (!data->map)
		return (error("Memory allocation failed."), 0);
	return (1);
}
