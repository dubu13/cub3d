/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:45:31 by dhasan            #+#    #+#             */
/*   Updated: 2024/09/18 19:52:23 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	while (line && (is_texture(line) || *line == "F" || *line == "C"))
	{
		free(line);
		line = get_next_line(fd);
	}
	return (line);
}

void	save_position(t_data *data, unsigned int x, unsigned int y)
{
	if (data->player.x != -1 || data->player.y != -1)
		msg_exit("Error\nMultiple player positions.\n", 1);
	data->player.x = x;
	data->player.y = y;
}
// void	copy_map(t_data *data)
// {
// 	char	**cpy_map;
// 	int		i;

// 	i = 0;
// 	cpy_map = ft_calloc(data->height + 1, sizeof(char *));
// 	if (!cpy_map)
// 		msg_exit("Error\nMemory allocation failed.\n", 1);
// 	while (data->map[i])
// 	{
// 		cpy_map[i] = ft_strdup(data->map[i]);
// 		if (!cpy_map[i])
// 			msg_exit("Error\nMemory allocation failed.\n", 1);
// 		i++;
// 	}
// 	return (cpy_map);
// }