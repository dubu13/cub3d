/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:55:47 by dhasan            #+#    #+#             */
/*   Updated: 2024/10/08 15:19:31 by dkremer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_extension(char *file)
{
	char	*extension;

	extension = ft_strrchr(file, '.');
	if (extension == NULL || ft_strncmp(extension, ".cub\0", 5) != 0)
		return (error("Map should be in '.cub' format."), 0);
	return (1);
}

int	check_texture(char *contect)
{
	int	fd;

	fd = open(contect, O_RDONLY);
	if (fd == -1)
	{
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}

int	ft_ischar(char *c)
{
	while(*c)
	{
		if ((*c >= '0' && *c <= '9'))
			return (1);
		c++;
	}
	return (0);
}

int	check_color(char **rgb)
{
	if (!rgb[0] || !rgb[1] || !rgb[2])
		return (0);
	if (!ft_ischar(rgb[0]) || !ft_ischar(rgb[1]) || !ft_ischar(rgb[2]))
		return (0);
	if (ft_atoi(rgb[0]) < 0 || ft_atoi(rgb[0]) > 255
		|| ft_atoi(rgb[1]) < 0 || ft_atoi(rgb[1]) > 255
		|| ft_atoi(rgb[2]) < 0 || ft_atoi(rgb[2]) > 255)
		return (0);
	return (1);
}

int	check_around_position(t_data *data, unsigned int x, unsigned int y)
{
	if (x == 0 || x == data->width - 1 || y == 0 || y == data->height - 1)
		return (0);
	else if (data->map[y - 1][x] == ' ' || data->map[y][x - 1] == ' ' || \
		data->map[y][x + 1] == ' ' || data->map[y + 1][x] == ' ')
		return (0);
	else if (data->map[y - 1][x] == '\0' || data->map[y][x - 1] == '\0' || \
		data->map[y][x + 1] == '\0' || data->map[y + 1][x] == '\0')
		return (0);
	return (1);
}

int	is_map_enclosed(t_data *data)
{
	unsigned int	y;
	unsigned int	x;

	y = 0;
	while (y < data->height)
	{
		x = 0;
		while (data->map[y][x] != '\0')
		{
			if (data->map[y][0] == '\n' )
				return (error("Newline inside map."), 0);
			if (data->map[y][x] != '1' && data->map[y][x] != ' ')
				if (!check_around_position(data, x, y))
					return (error("Map is not enclosed by walls."), 0);
			x++;
		}
		y++;
	}
	return (1);
}
