/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 11:58:20 by dkremer           #+#    #+#             */
/*   Updated: 2024/09/30 15:45:47 by dkremer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "MLX42/include/MLX42/MLX42.h"
# include "libft/include/libft.h"
# include "cub3d_types.h"
# include <math.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>

int		error(char *msg);
t_data	*init_data();

//raycasting
int		is_direction_positive(float angle, char axis);
int		get_step_direction(float angle, float *increment, float *step, char axis);
void	set_steps(float angle, float *x_step, float *y_step, char axis);
void	set_position(t_cub *cub, float angle, float *x, float *y, char axis);
void	set_step_direction(float angle, float *x_step, float *y_step, char axis);

//paser.c
void	check_extension(char *file);
void	parser(char *file, t_data *data);
//msg
void	msg_exit(char *msg, int exit_code);
//checker.c
void	is_map_enclosed(t_data *data);
bool	check_color(char **rgb);
bool	check_texture(char *contect);
//parser_utils.c
char	*skip_nl(int fd);
bool	is_texture(char *contect);
bool	is_color(char *contect);
char	*skip_info(int fd);
//map_utils.c
void	char_check(t_data *data);
void	file_to_map(int fd, t_data *data, char *line);

//rendering

void	render_wall(t_cub *mlx, int ray);

#endif
