/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkremer <dkremer@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 13:08:29 by dkremer           #+#    #+#             */
/*   Updated: 2024/08/22 13:11:24 by dkremer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_exit(t_cub *game)
{
	int i;

	i = 0;
	while (game->data->map[i])
		free(game->data->map[i++]);
	free(game->data->map);
	// free(game->data);
	// free(game->player);
	// free(game->ray);
	// free(game->wall);
	// free(game->data->no_texture);
	// free(game->data->so_texture);
	// free(game->data->we_texture);
	// free(game->data->ea_texture);
	mlx_delete_image(game->mlx, game->img);
	mlx_close_window(game->mlx);
	printf("GAME CLOSED\n");
	exit(0);
}
