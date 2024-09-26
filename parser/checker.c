/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:55:47 by dhasan            #+#    #+#             */
/*   Updated: 2024/09/26 20:11:52 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_extension(char *file)
{
	char	*extension;

	extension = ft_strrchr(file, '.');
	if (extension == NULL || ft_strncmp(extension, ".cub\0", 5) != 0)
		msg_exit("Error\nMap should be in '.cub' format.", 1);
}

bool	check_texture(char *contect)
{
	int	fd;

	fd = open(contect, O_RDONLY);
	if (fd == -1)
	{
		close(fd);
		return (false);
	}
	close(fd);
	return (true);
}

bool	check_color(char **rgb)
{
	if (!rgb[0] || !rgb[1] || !rgb[2])
		return (false);
	if (ft_atoi(rgb[0]) < 0 || ft_atoi(rgb[0]) > 255
		|| ft_atoi(rgb[1]) < 0 || ft_atoi(rgb[1]) > 255
		|| ft_atoi(rgb[2]) < 0 || ft_atoi(rgb[2]) > 255)
		return (false);
	return (true);
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

void	is_map_enclosed(t_data *data)
{
	unsigned int	y;
	unsigned int	x;

	y = 0;
	while (y < data->height)
	{
		x = 0;
		while (data->map[y][x] != '\0')
		{
			if (data->map[y][x] != '1' && data->map[y][x] != ' ')
				if (!check_around_position(data, x, y))
					msg_exit("Error\nMap is not enclosed by walls.", 1);
			x++;
		}
		y++;
	}
}
