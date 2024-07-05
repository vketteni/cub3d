/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiemann <hwiemann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 19:07:31 by vketteni          #+#    #+#             */
/*   Updated: 2024/07/05 14:19:21 by hwiemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void	perform_dda(t_render_data *render_data, t_map *map_data)
{
	t_ray	*ray;

	ray = &render_data->ray;
	while (render_data->flag_hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->grid_pos_x += ray->step_x;
			render_data->flag_side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->grid_pos_y += ray->step_y;
			render_data->flag_side = 1;
		}
		if (map_data->map[ray->grid_pos_x][ray->grid_pos_y] > '0')
			render_data->flag_hit = 1;
	}
}

void	calculate_wall_distance_and_height(t_render_data *render_data,
		mlx_image_t *image, mlx_texture_t *tex)
{
	t_raycast	*raycast;
	t_ray		*ray;
	t_player	*player;
	double		wall_x;

	player = &render_data->player;
	ray = &render_data->ray;
	raycast = &render_data->raycast;
	if (render_data->flag_side == 0)
		raycast->perp_wall_dist = (ray->grid_pos_x - player->pos_x + (1
					- ray->step_x) / 2) / ray->ray_dir_x;
	else
		raycast->perp_wall_dist = (ray->grid_pos_y - player->pos_y + (1
					- ray->step_y) / (double)2) / ray->ray_dir_y;
	raycast->line_height = (int)(image->height / raycast->perp_wall_dist);
	raycast->draw_start = -raycast->line_height / 2 + image->height / 2;
	if (raycast->draw_start < 0)
		raycast->draw_start = 0;
	raycast->draw_end = raycast->line_height / 2 + image->height / 2;
	if (raycast->draw_end >= (int)image->height)
		raycast->draw_end = image->height - 1;
}
//das verwenden fuer textures drawing
void	draw_line(int x, t_render_data *render_data, mlx_image_t *image, mlx_texture_t *tex)
{
	t_color		color = {0, 0, 155, 255};
	t_color		color_side = {100, 0, 155, 255};
	t_raycast	*raycast;
	int			y;

	raycast = &render_data->raycast;

	if (render_data->flag_side == 1)
		color = color_side;
	y = raycast->draw_start;
	while (y < raycast->draw_end)
	{
		int texY = (int)render_data->raycast.tex_pos & (texture->height - 1);
        render_data->raycast.tex_pos += render_data->raycast.tex_step_size;
        uint32_t color = ((uint32_t*)texture->pixels)[texture->width * texY + render_data->raycast.tex_x];
        
		images->pixels[(y * images->width + x) * 4 + 0] = color.r;
		images->pixels[(y * images->width + x) * 4 + 1] = color.g;
		images->pixels[(y * images->width + x) * 4 + 2] = color.b;
		images->pixels[(y * images->width + x) * 4 + 3] = color.a;
		y++;
	}
}

void	render_image(t_game *game)
{
	t_render_data	*render_data;
	mlx_image_t		*img;
	uint32_t		x;
	mlx_texture_t	*selected_texture;

	img = game->img;
	render_data = &game->render_data;
	get_textures(game);
	ft_memset(img->pixels, 0, img->width * img->height * 4);
	mini_map_init(game);
	x = 0;
	while (x < img->width)
	{
		setup_render_params(x, render_data, img);
		perform_dda(render_data, &game->map);
		selected_texture = game->tex.wall;
		if (render_data->flag_side == 0)
		{
			if (render_data->ray.ray_dir_x > 0)
				selected_texture = game->tex.floor;
			else
				selected_texture = game->tex.ceiling;
		}
		else
		{
			if (render_data->ray.ray_dir_y > 0)
				selected_texture = game->tex.target;
			else
				selected_texture = game->tex.player;
		}
		calculate_wall_distance_and_height(render_data, img, selected_texture);
		draw_line(x, render_data, img, selected_texture);
		x++;
	}
}
