/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkremer <dkremer@student.42heilbronn.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 11:58:20 by dkremer           #+#    #+#             */
/*   Updated: 2024/08/18 11:58:20 by dkremer          ###   ########.fr       */
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

int error(char *msg);
t_data *init_data();
int is_direction_positive(float angle, char axis);
int get_step_direction(float angle, float *increment, float *step, char axis);
void  set_steps(float angle, float *x_step, float *y_step, char axis);
void set_position(t_cub *cub, float angle, float *x, float *y, char axis);
void set_step_direction(float angle, float *x_step, float *y_step, char axis);
#endif