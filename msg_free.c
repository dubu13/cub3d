/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 13:08:29 by dkremer           #+#    #+#             */
/*   Updated: 2024/10/07 18:24:38 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_exit(t_cub *game)
{
	free_data(game->data);
	mlx_delete_image(game->mlx, game->img);
	mlx_close_window(game->mlx);
	game->mlx = NULL;
	game->img = NULL;
	game->data = NULL;
	game->player = NULL;
	game->ray = NULL;
	game->wall = NULL;
	game = NULL;
	printf("GAME CLOSED\n");
	exit(0);
}

void	error(char *msg)
{
	printf("Error\n%s", msg);
}

void	free_2d_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	array = NULL;
}

void	free_data(t_data *data)
{
	if (data->map)
		free_2d_array(data->map);
	if (data->ea_texture)
		free(data->ea_texture);
	if (data->no_texture)
		free(data->no_texture);
	if (data->so_texture)
		free(data->so_texture);
	if (data->we_texture)
		free(data->we_texture);
	data = NULL;
}
