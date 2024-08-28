/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkremer <dkremer@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 15:35:03 by dkremer           #+#    #+#             */
/*   Updated: 2024/08/28 15:36:04 by dkremer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int is_direction_positive(float angle, char axis)
{
    if (axis == 'x')
        return (angle > 0 && angle < M_PI);
    if (axis == 'y')
        return (angle > M_PI / 2 && angle < 3 * M_PI / 2);
    return (0);
}

int get_step_direction(float angle, float *increment, float *step, char axis)
{
    int is_positive;

    is_positive = is_direction_positive(angle, axis);
    if (axis == 'x' && is_positive)
    {
        *increment += TILE_SIZE;
        return (-1);
    }
    if (axis == 'y')
    {
        if (!is_positive)
        {
            *increment += TILE_SIZE;
            return (-1);
        }
        *step *= -1;
    }
    return (0);
}

void  set_steps(float angle, float *x_step, float *y_step, char axis)
{
    if (axis == 'x')
    {
        *x_step = TILE_SIZE / tan(angle);
        *y_step = TILE_SIZE;
    }
    else
    {
        *x_step = TILE_SIZE;
        *y_step = TILE_SIZE * tan(angle);
    }
}

void set_position(t_cub *cub, float angle, float *x, float *y, char axis)
{
    if (axis == 'x')
    {
        *x = floor(cub->player->p_x / TILE_SIZE) * TILE_SIZE;
        *y = cub->player->p_y + (cub->player->p_x - *x) / tan(angle);
    }
    else
    {
        *y = floor(cub->player->p_y / TILE_SIZE) * TILE_SIZE;
        *x = cub->player->p_x + (cub->player->p_y - *y) * tan(angle);
    }
}

void set_step_direction(float angle, float *x_step, float *y_step, char axis)
{
    if (axis == 'x')
    {
        if ((!is_direction_positive(angle, 'y') && *x_step > 0) || \
        (is_direction_positive(angle, 'y') && *x_step < 0))
            *x_step *= -1;
    }
    else
    {
        if ((!is_direction_positive(angle, 'x') && *y_step < 0) || \
        (is_direction_positive(angle, 'x') && *y_step > 0))
            *y_step *= -1;
    }
}