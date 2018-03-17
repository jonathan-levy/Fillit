/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit_tetromino.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolevy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 16:05:56 by jolevy            #+#    #+#             */
/*   Updated: 2018/03/16 18:15:45 by famartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static void				fillit_set_dimensions(t_tetromino *tet)
{
	int		row;
	int		col;
	int		width;
	int		height;

	row = -1;
	width = 0;
	height = 0;
	while (++row < SIZE)
	{
		col = -1;
		while (++col < SIZE)
		{
			(tet->x[row] == tet->x[col]) ? width += 1 : width;
			(tet->y[row] == tet->y[col]) ? height += 1 : height;
		}
	}
	if ((width % SIZE) || (height % SIZE))
	{
		width += 4;
		height += 4;
	}
	tet->width = (width / 4);
	tet->height = (height / 4);
}

static char				***fillit_split_tetromino(char **map)
{
	int		i;
	char	***fullmap;

	i = 0;
	if (!(fullmap = (char ***)malloc(sizeof(char **) * g_num_tets + 1)))
		return (NULL);
	while (i < g_num_tets)
	{
		fullmap[i] = ft_strsplit(map[i], '\n');
		i += 1;
	}
	return (fullmap);
}

static t_tetromino		*fillit_new_tetrominos(int size)
{
	int			i;
	t_tetromino	*new;
	t_tetromino *head;

	if (!(new = (t_tetromino *)malloc(sizeof(t_tetromino) + 1)))
		return (NULL);
	head = new;
	i = 0;
	while (i++ < size)
	{
		if (!(new->next = (t_tetromino *)malloc(sizeof(t_tetromino) + 1)))
			return (NULL);
		new = new->next;
	}
	ft_memset(new, 0, (sizeof(t_tetromino) + 1));
	return (head);
}

static t_tetromino		*fillit_create_tetrominos(char ***fullmap, \
						t_tetromino *tet, char letter, int *counter)
{
	t_tetromino *head;

	head = tet;
	counter[0] = -1;
	while (++counter[0] < g_num_tets)
	{
		counter[3] = 0;
		counter[1] = -1;
		while (++counter[1] < SIZE)
		{
			counter[2] = -1;
			while (++counter[2] < SIZE)
			{
				if (fullmap[counter[0]][counter[1]][counter[2]] == BLOCK)
				{
					tet->x[counter[3]] = counter[1];
					tet->y[counter[3]++] = counter[2];
				}
			}
		}
		fillit_set_dimensions(tet);
		tet->letter = letter++;
		tet = tet->next;
	}
	return (head);
}

t_tetromino				*fillit_tetromino(char **map)
{
	int				*counter;
	char			***fullmap;
	t_tetromino		*tetromino;

	if (!(counter = (int *)malloc(sizeof(int) * 4)))
		return (NULL);
	if (!(fullmap = (char ***)malloc(sizeof(char **) * g_num_tets + 1)))
		return (NULL);
	tetromino = fillit_new_tetrominos(g_num_tets);
	fullmap = fillit_split_tetromino(map);
	return (fillit_create_tetrominos(fullmap, tetromino, LETTER, counter));
}
