/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkremer <dkremer@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 12:05:22 by dkremer           #+#    #+#             */
/*   Updated: 2024/08/27 14:18:09 by dkremer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player(t_cub cub)
{
	cub.player->p_x = cub.data->pos_x * TILE_SIZE + TILE_SIZE / 2;
	cub.player->p_y = cub.data->pos_y * TILE_SIZE + TILE_SIZE / 2;
	cub.player->fov = FOV_RAD;
	cub.player->angle = M_PI;
}

int	init_game(t_data *data)
{
	t_cub	cub;

	cub.data = data;
	if (!(cub.player = ft_calloc(1, sizeof(t_player))))
		return (1);
	if (!(cub.ray = ft_calloc(1, sizeof(t_ray))))
		return (1);
	if (!(cub.mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d", true)))
		return (1);
	init_player(cub);
	mlx_loop(cub.mlx);
	return (0);
}

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	t_data *data;

	data = init_data();
	if (init_game(data))
		error("INIT ERROR");
}