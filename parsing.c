/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkremer <dkremer@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 13:35:56 by dkremer           #+#    #+#             */
/*   Updated: 2024/08/27 13:44:23 by dkremer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	map_parsing(t_data *data)
{
	if (!(data->map = calloc(10, sizeof(char *))))
		return (1);
	data->map[0] = strdup("1111111111111111111111111");
	data->map[1] = strdup("1000000000000000000100001");
	data->map[2] = strdup("1001000000000P00000000001");
	data->map[3] = strdup("1001000000000000001000001");
	data->map[4] = strdup("1001000000000000001000001");
	data->map[5] = strdup("1001000000100000001000001");
	data->map[6] = strdup("1001000000000000001000001");
	data->map[7] = strdup("1001000000001000001000001");
	data->map[8] = strdup("1111111111111111111111111");
	data->map[9] = NULL;
	return (0);
}

t_data	*init_data(void)
{
	t_data *data;

	if (!(data = ft_calloc(1, sizeof(t_data))))
		error("DATA ALLOC ERROR");
	data->width = 25;
	data->height = 9;
	data->pos_x = 1;
	data->pos_y = 1;
	if (map_parsing(data))
		error("MAP PARSING ERROR");
	return (data);
}