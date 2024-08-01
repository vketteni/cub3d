/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiemann <hwiemann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:20:17 by vketteni          #+#    #+#             */
/*   Updated: 2024/07/30 17:21:02 by hwiemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void	move_straight(t_game *game, t_minimap *minimap,
		t_render *render, int direction)
{
	t_player	*player;
	double		next_x;
	double		next_y;

	player = &render->player;
	next_x = player->pos_x + player->dir_x * MOVE_SPEED * direction;
	next_y = player->pos_y + player->dir_y * MOVE_SPEED * direction;
	player = &game->render.player;
	if (minimap->map[(int)(next_y)][(int)(next_x)] == '0')
	{
		player->pos_x = next_x;
		player->pos_y = next_y;
	}
}

void	move_sideways(t_game *game, t_minimap *minimap,
		t_render *render, int direction)
{
	double	side_dir_x;
	double	side_dir_y;
	double	next_x;
	double	next_y;

	(void)game;
	side_dir_x = (render->player.dir_y);
	side_dir_y = -(render->player.dir_x);
	next_x = render->player.pos_x + side_dir_x * MOVE_SPEED * direction;
	next_y = render->player.pos_y + side_dir_y * MOVE_SPEED * direction;
	if (minimap->map[(int)(next_y)][(int)(next_x)] == '0')
	{
		render->player.pos_x = next_x;
		render->player.pos_y = next_y;
	}
}

void	rotate(t_render *render, int direction)
{
	double		old_dir_x;
	double		old_plane_x;
	t_player	*player;
	t_camera	*camera;

	player = &render->player;
	camera = &render->camera;
	old_dir_x = player->dir_x;
	player->dir_x = player->dir_x * cos(ROT_SPEED * direction) - player->dir_y
		* sin(ROT_SPEED * direction);
	player->dir_y = old_dir_x * sin(ROT_SPEED * direction) + player->dir_y
		* cos(ROT_SPEED * direction);
	old_plane_x = camera->plane_x;
	camera->plane_x = camera->plane_x * cos(ROT_SPEED * direction)
		- camera->plane_y * sin(ROT_SPEED * direction);
	camera->plane_y = old_plane_x * sin(ROT_SPEED * direction) + camera->plane_y
		* cos(ROT_SPEED * direction);
}
