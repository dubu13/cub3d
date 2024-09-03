/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:53:31 by dhasan            #+#    #+#             */
/*   Updated: 2024/09/03 18:34:49 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	msg_exit(char *msg, int exit_code)
{
	printf("%s\n", msg);
	exit(exit_code);
}

void	check_extension(char *file)
{
	int	len;

	len = ft_strlen(file);
	if (file[len - 1] != 'b' || file[len - 2] != 'u' \
		|| file[len - 3] != 'c' || file[len - 4] != '.')
		msg_exit("Error\nMap should be in '.ber' format.\n", 1);
}
void	read_file(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		msg_exit("Error\nFile does not exist or is not readable.\n", 1);
	
}
int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Error\nInvalid number of arguments\n");
		printf("Usage: %s <map_file.cub>\n", argv[0]);
		return (1);
	}
	//check file extension ".cub"
	check_extension(argv[1]);
	//is file exist and readable
	read_file(argv[1]);
	//parse textures (no, so, we, ea) and store the paths
	//parse the floor(F) and ceiling(C) colors ande store them
	//! red, gree, blue (RGB); range is 0-255!
	//read the map and store it in a 2D array
	//is map enclosed by walls?
	//store the player's position and orientation
	//for data struct : map(2d), textures(no, so, we, ea), colors(F, C), player(pos, orientation)
}
