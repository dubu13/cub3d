/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 15:47:14 by dhasan            #+#    #+#             */
/*   Updated: 2024/10/04 17:34:23 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

mlx_texture_t	*get_textures(t_cub *game, int wall_hit)
{
	char			*texture;
	const double	normalized_angle = nor_angle(game->ray->angle);

	if (wall_hit == 0)
	{
		if (normalized_angle > M_PI / 2 && normalized_angle < 3 * (M_PI / 2))
			texture = game->data->we_texture;
		else
			texture = game->data->ea_texture;
	}
	else
	{
		if (normalized_angle > 0 && normalized_angle < M_PI)
			texture = game->data->so_texture;
		else
			texture = game->data->no_texture;
	}
	return (mlx_load_png(texture));
}

//fix this
double	get_texture_x(t_cub *game, mlx_texture_t *texture)
{
	double	wall_x;

	// if (game->ray->wall_hit == 0)
	// 	wall_x = game->player->p_y + game->ray->distance * \
	// 		sin(game->ray->angle);
	// else
	// 	wall_x = game->player->p_x + game->ray->distance * \
	// 		cos(game->ray->angle);
	if (game->ray->wall_hit == 0) // Horizontal wall hit
	{
		wall_x = game->player->p_y + game->ray->distance * sin(game->ray->angle);
		if (!is_direction_positive(game->ray->angle, 'y')) // Adjusting for ray direction
			wall_x = -wall_x;
	}
	else // Vertical wall hit
	{
		wall_x = game->player->p_x + game->ray->distance * cos(game->ray->angle);
		if (!is_direction_positive(game->ray->angle, 'x')) // Adjusting for ray direction
			wall_x = -wall_x;
	}
	wall_x -= floor(wall_x);
	return (wall_x * texture->width);
}

uint32_t	get_texture_color(mlx_texture_t *texture, int tex_x, int tex_y)
{
	uint8_t	*pixel;

	pixel = &texture->pixels[(tex_y * texture->width + tex_x) * 4];
	return ((pixel[0] << 24) | (pixel[1] << 16) | (pixel[2] << 8) | pixel[3]);
}

float	nor_angle(float angle)
{
	while (angle < 0)
		angle += (2 * M_PI);
	while (angle > (2 * M_PI))
		angle -= (2 * M_PI);
	return (angle);
}
