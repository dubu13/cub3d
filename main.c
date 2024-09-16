/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:53:31 by dhasan            #+#    #+#             */
/*   Updated: 2024/09/16 16:43:59 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	msg_exit(char *msg, int exit_code)
{
	printf("%s\n", msg);
	exit(exit_code);
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
	//check file extension ".cub"
	check_extension(argv[1]);
	//is file exist and readable
	read_file(argv[1], data);
	//parse textures (no, so, we, ea) and store the paths
	//parse the floor(F) and ceiling(C) colors ande store them
	//! red, gree, blue (RGB); range is 0-255!
	//read the map and store it in a 2D array
	//is map enclosed by walls?
	//store the player's position and orientation
	//for data struct : map(2d), textures(no, so, we, ea), colors(F, C), player(pos, orientation)
}
