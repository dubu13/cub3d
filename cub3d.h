/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 11:58:20 by dkremer           #+#    #+#             */
/*   Updated: 2024/10/07 17:56:22 by dhasan           ###   ########.fr       */
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

t_data	*init_data();

//raycasting
int		is_direction_positive(float angle, char axis);
int		get_step_direction(float angle, float *increment, char axis);
void	set_steps(float angle, float *x_step, float *y_step, char axis);
void	set_position(t_cub *cub, float angle, float pos[2], char axis);
void	set_step_direction(float angle, float *x_step, float *y_step, char axis);
void	raycasting(t_cub *cub);
int		inter_check(float angle, float *inter, float *step, int is_horizon);
int		dir_check(float angle, char c);
//paser.c
int	check_extension(char *file);
int	read_file(char *file, t_data *data);

//checker.c
int	is_map_enclosed(t_data *data);
int	check_color(char **rgb);
int	check_texture(char *contect);
//parser_utils.c
char	*skip_nl(int fd);
bool	is_texture(char *contect);
bool	is_color(char *contect);
// char	*skip_info(int fd);
int32_t	convert_rgb(int r, int g, int b, int a);
//map_utils.c
int	char_check(t_data *data);
int	file_to_map(int fd, t_data *data, char *line);

//rendering

void	render_wall(t_cub *mlx, int ray);

//rendering_utils.c
float			nor_angle(float angle);
double			get_texture_x(t_cub *game, mlx_texture_t *texture);
mlx_texture_t	*get_textures(t_cub *game, int wall_hit);
uint32_t		get_texture_color(mlx_texture_t *texture, int tex_x, int tex_y);
//movement
void	hook(t_cub *game, double move_x, double move_y);
void	mlx_key(mlx_key_data_t keydata, void *ml);

void	ft_exit(t_cub *game);
void	free_2d_array(char **array);
void	error(char *msg);
void	free_data(t_data *data);
#endif
