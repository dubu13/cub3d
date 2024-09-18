/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:53:31 by dhasan            #+#    #+#             */
/*   Updated: 2024/09/18 19:52:29 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	msg_exit(char *msg, int exit_code)
{
	printf("%s\n", msg);
	exit(exit_code);
}

void	parser(char *file, t_data *data)
{
	check_extension(file);
	read_file(file, data);
	is_map_enclosed(data);
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
}
