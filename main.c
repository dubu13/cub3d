/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:53:31 by dhasan            #+#    #+#             */
/*   Updated: 2024/10/06 19:12:26 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_types.h"

void	msg_exit(char *msg, int exit_code)
{
	printf("%s\n", msg);
	exit(exit_code);
}

void	init_player(t_cub *cub)
{
	cub->player->p_x = cub->data->pos_x * TILE_SIZE + TILE_SIZE / 2;
	cub->player->p_y = cub->data->pos_y * TILE_SIZE + TILE_SIZE / 2;
	cub->player->fov = (FOV * M_PI / 180);
	cub->player->angle = M_PI;
}

void	game_loop(void *ml)
{
	t_cub	*mlx;

	mlx = ml;
	mlx_delete_image(mlx->mlx, mlx->img);
	mlx->img = mlx_new_image(mlx->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	hook(mlx, 0, 0);
	raycasting(mlx);
	mlx_image_to_window(mlx->mlx, mlx->img, 0, 0);
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
	if (!(cub.mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d", true)))
		return (1);
	init_player(&cub);
	mlx_loop_hook(cub.mlx, &game_loop, &cub);
	mlx_key_hook(cub.mlx, &mlx_key, &cub);
	mlx_loop(cub.mlx);
	mlx_terminate(cub.mlx);
	return (0);
}

// void	print_data(t_data *data)
// {
// 	printf("NO: %s\n", data->no_texture);
// 	printf("SO: %s\n", data->so_texture);
// 	printf("WE: %s\n", data->we_texture);
// 	printf("EA: %s\n", data->ea_texture);
// 	printf("F: %d, %d, %d\n", data->floor_color[0], data->floor_color[1], data->floor_color[2]);
// 	printf("C: %d, %d, %d\n", data->ceiling_color[0], data->ceiling_color[1], data->ceiling_color[2]);
// 	printf("Map:\n");
// 	for (unsigned int i = 0; i < data->height; i++)
// 		printf("%s\n", data->map[i]);
// 	printf("Player position: %d, %d\n", data->pos_x, data->pos_y);
// }

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
	parser(argv[1], &data);
	// print_data(data);
	if (init_game(&data))
		msg_exit("Error\nInitialization failed.\n", 1);
	return (0);
}
