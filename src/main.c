/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:53:31 by dhasan            #+#    #+#             */
/*   Updated: 2024/10/09 15:12:40 by dkremer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player(t_cub *cub)
{
	cub->player->p_x = cub->data->pos_x * TILE_SIZE + TILE_SIZE / 2;
	cub->player->p_y = cub->data->pos_y * TILE_SIZE + TILE_SIZE / 2;
	cub->player->fov = (FOV * M_PI / 180);
	if (cub->data->dir == 'N')
		cub->player->angle = NORTH;
	else if (cub->data->dir == 'S')
		cub->player->angle = SOUTH;
	else if (cub->data->dir == 'E')
		cub->player->angle = EAST;
	else if (cub->data->dir == 'W')
		cub->player->angle = WEST;
}

void	game_loop(void *param)
{
	t_cub	*cub;

	cub = param;
	mlx_delete_image(cub->mlx, cub->img);
	cub->img = mlx_new_image(cub->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	hook(cub, 0, 0);
	raycasting(cub);
	mlx_image_to_window(cub->mlx, cub->img, 0, 0);
}

int	init_game(t_data *data)
{
	t_cub		cub;
	t_player	player;
	t_ray		ray;

	ft_bzero(&cub, sizeof(t_cub));
	ft_bzero(&player, sizeof(t_player));
	ft_bzero(&ray, sizeof(t_ray));
	cub.data = data;
	cub.player = &player;
	cub.ray = &ray;
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	cub.mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d", true);
	if (!cub.mlx)
		return (0);
	init_player(&cub);
	mlx_close_hook(cub.mlx, &ft_exit, &cub);
	mlx_loop_hook(cub.mlx, &game_loop, &cub);
	mlx_key_hook(cub.mlx, &mlx_key, &cub);
	mlx_loop(cub.mlx);
	mlx_terminate(cub.mlx);
	ft_exit(&cub);
	return (1);
}

void	leaks(void)
{
	system("leaks cub3d");
}

int	main(int argc, char **argv)
{
	t_data	data;

	atexit(leaks);
	ft_bzero(&data, sizeof(t_data));
	if (argc != 2)
	{
		printf("Error\nInvalid number of arguments\n");
		printf("Usage: %s <map_file.cub>\n", argv[0]);
		return (1);
	}
	if (!check_extension(argv[1]) || !read_file(argv[1], &data))
		return (free_data(&data), 1);
	if (!init_game(&data))
		return (error("Initialization failed."), free_data(&data), 1);
	return (0);
}
