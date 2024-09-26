/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:53:31 by dhasan            #+#    #+#             */
/*   Updated: 2024/09/26 20:16:04 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	msg_exit(char *msg, int exit_code)
{
	printf("%s\n", msg);
	exit(exit_code);
}

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

void	print_data(t_data *data)
{
	printf("NO: %s\n", data->no_texture);
	printf("SO: %s\n", data->so_texture);
	printf("WE: %s\n", data->we_texture);
	printf("EA: %s\n", data->ea_texture);
	printf("F: %d, %d, %d\n", data->floor_color[0], data->floor_color[1], data->floor_color[2]);
	printf("C: %d, %d, %d\n", data->ceiling_color[0], data->ceiling_color[1], data->ceiling_color[2]);
	printf("Map:\n");
	for (unsigned int i = 0; i < data->height; i++)
		printf("%s\n", data->map[i]);
	printf("Player position: %d, %d\n", data->pos_x, data->pos_y);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		msg_exit("Error\nMemory allocation failed.\n", 1);
	if (argc != 2)
	{
		printf("Error\nInvalid number of arguments\n");
		printf("Usage: %s <map_file.cub>\n", argv[0]);
		return (1);
	}
	parser(argv[1], data);
	if (init_game(data))
		msg_exit("Error\nInitialization failed.\n", 1);
}
