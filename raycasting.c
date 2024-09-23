/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkremer <dkremer@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 14:07:48 by dkremer           #+#    #+#             */
/*   Updated: 2024/09/23 16:19:32 by dkremer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_wall(t_cub *cub, float x, float y)
{
	int		map_x;
	int		map_y;
	size_t	row_length;

	if (x < 0 || y < 0)
		return (1);
	map_x = (int)(floor(x / TILE_SIZE));
	map_y = (int)(floor(y / TILE_SIZE));
	if (map_x < 0 || map_y < 0 || map_x >= cub->data->width || \
		map_y >= cub->data->height)
		return (1);
	row_length = ft_strlen(cub->data->map[map_y]);
	if (map_x >= (int)row_length)
		return (1);
	if (cub->data->map[map_y][map_x] == '1')
		return (1);
	return (0);
}

float	intersection(t_cub *cub, float angle, char axis)
{
	float	x_step;
	float	y_step;
	float	x;
	float	y;
	float	intercept;

	set_steps(angle, &x_step, &y_step, axis);
	set_position(cub, angle, &x, &y, axis);
	intercept = get_step_direction(angle, &x_step, &y_step, axis);
	set_step_direction(angle, &x_step, &y_step, axis);
	if (axis == 'x')
	{
		while (!is_wall(cub, x, y - intercept))
		{
			x += x_step;
			y += y_step;
		}
	}
	else
	{
		while (!is_wall(cub, x - intercept, y))
		{
			x += x_step;
			y += y_step;
		}
	}
	return (sqrt(pow(x - cub->player->p_x, 2) + pow(y - cub->player->p_y, 2)));
}

void	raycasting(t_cub *cub)
{
	double	h_intercept;
	double	v_intercept;
	int		ray;

	ray = 0;
	cub->ray->angle = cub->player->angle - cub->player->fov / 2;
	while (ray < SCREEN_WIDTH)
	{
		h_intercept = intersection(cub, cub->ray->angle, 'x');
		v_intercept = intersection(cub, cub->ray->angle, 'y');
		if (v_intercept <= h_intercept)
			cub->ray->distance = v_intercept;
		else
		{
			cub->ray->distance = h_intercept;
			cub->ray->wall_hit = 1;
		}
		// render_wall(cub, ray);
		ray++;
		cub->ray->angle += cub->player->fov / SCREEN_WIDTH;
	}
}
