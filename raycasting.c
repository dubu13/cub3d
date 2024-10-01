/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 14:07:48 by dkremer           #+#    #+#             */
/*   Updated: 2024/10/01 15:28:37 by dkremer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	wall_hit(float x, float y, t_cub *game)
{
	unsigned int	x_m;
	unsigned int	y_m;

	if (x < 0 || y < 0)
		return (0);
	x_m = floor(x / TILE_SIZE);
	y_m = floor(y / TILE_SIZE);
	if ((y_m >= game->data->height || x_m >= game->data->width))
		return (0);
	if (game->data->map[y_m] && x_m <= strlen(game->data->map[y_m]))
		if (game->data->map[y_m][x_m] == '1')
			return (0);
	return (1);
}

float	get_h_inter(t_cub *game, float angle)
{
	float	h_x;
	float	h_y;
	float	x_step;
	float	y_step;
	int		pixel;

	set_steps(angle, &x_step, &y_step, 'x');
	h_y = floor(game->player->p_y / TILE_SIZE) * TILE_SIZE;
	pixel = inter_check(angle, &h_y, &y_step, 1);
	h_x = game->player->p_x + (h_y - game->player->p_y) / tan(angle);
	set_step_direction(angle, &x_step, &y_step, 'x');
	while (wall_hit(h_x, h_y - pixel, game))
	{
		h_x += x_step;
		h_y += y_step;
	}
	return (sqrt(pow(h_x - game->player->p_x, 2) + pow(h_y - game->player->p_y,
				2)));
}

float	get_v_inter(t_cub *game, float angle)
{
	float	v_x;
	float	v_y;
	float	x_step;
	float	y_step;
	int		pixel;

	set_steps(angle, &x_step, &y_step, 'y');
	v_x = floor(game->player->p_x / TILE_SIZE) * TILE_SIZE;
	pixel = inter_check(angle, &v_x, &x_step, 0);
	v_y = game->player->p_y + (v_x - game->player->p_x) * tan(angle);
	set_step_direction(angle, &x_step, &y_step, 'y');
	while (wall_hit(v_x - pixel, v_y, game))
	{
		v_x += x_step;
		v_y += y_step;
	}
	return (sqrt(pow(v_x - game->player->p_x, 2) + pow(v_y - game->player->p_y,
				2)));
}

void	raycasting(t_cub *mlx)
{
	double	h_inter;
	double	v_inter;
	int		ray;

	ray = 0;
	mlx->ray->angle = mlx->player->angle - (mlx->player->fov / 2);
	while (ray < SCREEN_WIDTH)
	{
		mlx->ray->wall_hit = 0;
		h_inter = get_h_inter(mlx, nor_angle(mlx->ray->angle));
		v_inter = get_v_inter(mlx, nor_angle(mlx->ray->angle));
		if (v_inter <= h_inter)
			mlx->ray->distance = v_inter;
		else
		{
			mlx->ray->distance = h_inter;
			mlx->ray->wall_hit = 1;
		}
		render_wall(mlx, ray);
		ray++;
		mlx->ray->angle += (mlx->player->fov / SCREEN_WIDTH);
	}
}
