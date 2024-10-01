/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkremer <dkremer@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 12:22:36 by dkremer           #+#    #+#             */
/*   Updated: 2024/09/30 16:28:24 by dkremer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_cub *game, int x, int y, int color)
{
	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
		return ;
	mlx_put_pixel(game->img, x, y, color);
}

float	nor_angle(float angle)
{
	while (angle < 0)
		angle += (2 * M_PI);
	while (angle > (2 * M_PI))
		angle -= (2 * M_PI);
	return (angle);
}

void	draw_floor_ceiling(t_cub *game, int ray, int t_pix, int b_pix)
{
	int	i;

	i = b_pix;
	while (i < SCREEN_HEIGHT)
		my_mlx_pixel_put(game, ray, i++, 0xB99470FF);
	i = 0;
	while (i < t_pix)
		my_mlx_pixel_put(game, ray, i++, 0x89CFF3FF);
}

int	get_color(t_cub *game, int flag)
{
	game->ray->angle = nor_angle(game->ray->angle);
	if (flag == 0)
	{
		if (game->ray->angle > M_PI / 2 && game->ray->angle < 3 * (M_PI / 2))
			return (0xFF1493FF);
		else
			return (0x00FF7FFF);
	}
	else
	{
		if (game->ray->angle > 0 && game->ray->angle < M_PI)
			return (0xFFD700FF);
		else
			return (0x8A2BE2FF);
	}
}

void	draw_wall(t_cub *game, int ray, int t_pix, int b_pix)
{
	int	color;

	color = get_color(game, game->ray->wall_hit);
	while (t_pix < b_pix)
		my_mlx_pixel_put(game, ray, t_pix++, color);
}

void	render_wall(t_cub *mlx, int ray)
{
	double	wall_h;
	double	b_pix;
	double	t_pix;

	// Correct the distance for fish-eye effect
	mlx->ray->distance *= cos(nor_angle(mlx->ray->angle - mlx->player->angle));

	// Calculate wall height
	wall_h = (TILE_SIZE / mlx->ray->distance) * ((SCREEN_WIDTH / 2) / tan(mlx->player->fov / 2));

	// Calculate top and bottom pixel positions
	b_pix = (SCREEN_HEIGHT / 2) + (wall_h / 2);
	t_pix = (SCREEN_HEIGHT / 2) - (wall_h / 2);

	// Clamp the pixel positions to screen boundaries
	if (b_pix > SCREEN_HEIGHT)
		b_pix = SCREEN_HEIGHT;
	if (t_pix < 0)
    	t_pix = 0;
	// Draw the wall
	draw_wall(mlx, ray, t_pix, b_pix);

	// Draw the floor and ceiling
	draw_floor_ceiling(mlx, ray, t_pix, b_pix);
}
