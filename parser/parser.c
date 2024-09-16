/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:43:35 by dhasan            #+#    #+#             */
/*   Updated: 2024/09/16 19:00:18 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_texture(char *contect, t_data *data)
{
	if (!check_texture(contect))
		msg_exit("Error\nInvalid texture.\n", 1);
	if (!ft_strncmp(contect, "NO ", 3))
		data->no_texture = ft_strdup(contect + 3);
	else if (!ft_strncmp(contect, "SO ", 3))
		data->so_texture = ft_strdup(contect + 3);
	else if (!ft_strncmp(contect, "WE ", 3))
		data->we_texture = ft_strdup(contect + 3);
	else if (!ft_strncmp(contect, "EA ", 3))
		data->ea_texture = ft_strdup(contect + 3);
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

void	parse_map(int fd, t_data *data)
{
	
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
		else if (*contect == "F")
			parse_color(contect + 2, data->floor_color);
		else if (*contect == "C")
			parse_color(contect + 2, data->ceiling_color);
		else
		{
			parse_map(fd, data);
			break ;
		}
		free(contect);
		contect = skip_nl(fd);
	}
	close(fd);
}
