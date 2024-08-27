/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkremer <dkremer@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 14:07:48 by dkremer           #+#    #+#             */
/*   Updated: 2024/08/27 16:45:48 by dkremer          ###   ########.fr       */
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

int is_wall(t_cub *cub, float x, float y)
{
    int map_x;
    int map_y;
    size_t row_length;

    if (x < 0 || y < 0)
        return 0;
    map_x = (int)(floor(x / TILE_SIZE));
    map_y = (int)(floor(y / TILE_SIZE));
    if (map_x < 0 || map_y < 0 || map_x >= cub->data->width || map_y >= cub->data->height)
        return (0);
    row_length = ft_strlen(cub->data->map[map_y]);
    if (map_x >= (int)row_length)
        return 0;
    if (cub->data->map[map_y][map_x] == '1')
        return (0);
    return (1);
}

float hor_intersection(t_cub *cub, float angle)
{
    float x;
    float y;
    float x_step;
    float y_step;
    float x_intercept;

    
}

float vert_intersection(t_cub *cub, float angle)
{
    float x;
    float y;
    float x_step;
    float y_step;
    float y_intercept;

    
}
void    raycasting(t_cub *cub)
{
    
}