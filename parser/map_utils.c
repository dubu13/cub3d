/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:15:05 by dhasan            #+#    #+#             */
/*   Updated: 2024/09/26 20:13:55 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	save_position(t_data *data, unsigned int x, unsigned int y)
{
	if (data->pos_x != -1 || data->pos_y != -1)
		msg_exit("Error\nMultiple player positions.", 1);
	data->pos_x = x;
	data->pos_y = y;
}

void	char_check(t_data *data)
{
	unsigned int	y;
	unsigned int	x;

	y = 0;
	x = 0;
	while (data->map[y])
	{
		x = 0;
		if (data->map[y][0] == '\0')
			msg_exit("Error\nInvalid map.", 1);
		while (data->map[y][x])
		{
			if (!ft_strchr(" 01NSEW", data->map[y][x]))
				msg_exit("Error\nMap with invalid char.", 1);
			if (ft_strchr("NSEW", data->map[y][x]))
				save_position(data, x, y);
			x++;
		}
		if (x > data->width)
			data->width = x;
		y++;
	}
}

void	file_to_map(int fd, t_data *data, char *line)
{
	unsigned int	y;

	y = 0;
	if (!line)
		msg_exit("Error\nMissing map.", 1);
	while (line)
	{
		data->map_temp = ft_strjoin_gnl(data->map_temp, line);
		free(line);
		if (!data->map_temp)
			msg_exit("Error\nMemory allocation failed.", 1);
		data->height++;
		line = get_next_line(fd);
	}
	free(line);
	data->map = ft_split(data->map_temp, '\n');
	free(data->map_temp);
	if (!data->map)
		msg_exit("Error\nMemory allocation failed.\n", 1);
}
