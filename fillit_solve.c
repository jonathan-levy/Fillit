/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit_solve.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolevy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 16:03:13 by jolevy            #+#    #+#             */
/*   Updated: 2018/03/16 16:03:18 by jolevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static void	fillit_set_tetromino(t_tetromino *tet, char **map, int y, int x)
{
	int		row;
	int		col;
	int		i;

	i = 0;
	col = 0;
	while (tet->height > col)
	{
		row = 0;
		while (tet->width > row)
		{
			if (tet->x[i] == col && tet->y[i] == row)
			{
				map[col + y][row + x] = tet->letter;
				i += 1;
			}
			row += 1;
		}
		col += 1;
	}
}

static int	fillit_check_placement(t_tetromino *tet, char **map, int y, int x)
{
	int		row;
	int		col;
	int		i;

	i = 0;
	col = 0;
	while (tet->height > col)
	{
		row = 0;
		while (tet->width > row)
		{
			if (tet->x[i] == col && tet->y[i] == row && i < SIZE)
			{
				if (map[col + y][row + x] != EMPTY)
					return (0);
				i += 1;
			}
			row += 1;
		}
		col += 1;
	}
	fillit_set_tetromino(tet, map, y, x);
	return (1);
}

static void	fillit_move_tetromino_upperleft(t_tetromino *tet)
{
	int			i;
	int			pos_x;
	int			pos_y;

	while (tet)
	{
		i = -1;
		pos_x = SIZE - 1;
		pos_y = SIZE - 1;
		while (++i < SIZE)
		{
			if (tet->x[i] < pos_x)
				pos_x = tet->x[i];
			if (tet->y[i] < pos_y)
				pos_y = tet->y[i];
		}
		i = -1;
		while (++i < SIZE)
		{
			tet->x[i] -= pos_x;
			tet->y[i] -= pos_y;
		}
		tet = tet->next;
	}
}

static int	fillit_solve_map(char **map, t_tetromino *tet, int size)
{
	int		x;
	int		y;
	char	letter;

	if (!tet->next)
		return (1);
	y = -1;
	letter = tet->letter;
	while (++y <= (size - tet->height))
	{
		x = -1;
		while (++x <= (size - tet->width))
		{
			if (fillit_check_placement(tet, map, y, x))
			{
				if (fillit_solve_map(map, tet->next, size))
					return (1);
				tet->letter = EMPTY;
				fillit_set_tetromino(tet, map, y, x);
				tet->letter = letter;
			}
		}
	}
	return (0);
}

char		**fillit_solve(t_tetromino *tet)
{
	char	**map;
	int		size;

	if (!tet)
		return (NULL);
	size = ft_sqrt(g_num_tets * SIZE);
	map = fillit_create_map(size);
	fillit_move_tetromino_upperleft(tet);
	while (!fillit_solve_map(map, tet, size))
	{
		ft_memdel((void **)map);
		size += 1;
		map = fillit_create_map(size);
	}
	return (map);
}