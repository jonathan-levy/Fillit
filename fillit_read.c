/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit_read.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 18:45:53 by famartin          #+#    #+#             */
/*   Updated: 2018/03/16 18:48:30 by famartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static int	fillit_valid_characters(char *tetromino)
{
	int		i;
	int		height;
	int		blocks;
	int		characters;

	i = 0;
	blocks = 0;
	characters = 0;
	height = 0;
	while ((tetromino[i] == EMPTY || tetromino[i] == BLOCK || \
		tetromino[i] == '\n') && tetromino[i] && (height != SIZE))
	{
		if (tetromino[i] == EMPTY || tetromino[i] == BLOCK)
		{
			if (tetromino[i] == BLOCK)
				blocks += 1;
			characters += 1;
		}
		if (tetromino[i++] == '\n')
			height += 1;
	}
	if (((characters) == SIZE * SIZE) && (height == SIZE) && \
		(blocks == SIZE) && (tetromino[i] == '\n' || tetromino[i] == '\0'))
		return (1);
	return (0);
}

static int	fillit_valid_tetromino(char **tetromino)
{
	int		cnt;
	int		row;
	int		col;

	cnt = 0;
	row = -1;
	while (SIZE > ++row)
	{
		col = -1;
		while (SIZE > ++col)
		{
			if (tetromino[row][col] == BLOCK && row < 3)
				tetromino[row + 1][col] == BLOCK ? cnt++ : cnt;
			if (tetromino[row][col] == BLOCK && row > 0)
				tetromino[row - 1][col] == BLOCK ? cnt++ : cnt;
			if (tetromino[row][col] == BLOCK && col < 3)
				tetromino[row][col + 1] == BLOCK ? cnt++ : cnt;
			if (tetromino[row][col] == BLOCK && col > 0)
				tetromino[row][col - 1] == BLOCK ? cnt++ : cnt;
		}
	}
	if (cnt == 6 || cnt == 8)
		return (1);
	return (0);
}

static int	fillit_valid(char *map)
{
	if (fillit_valid_characters(map))
		if (fillit_valid_tetromino((ft_strsplit(map, '\n'))))
			return (1);
	return (0);
}

char		**fillit_create_map(int size)
{
	char	**map;
	int		row;
	int		col;

	if (!(map = (char **)malloc(sizeof(char *) * size)))
		return (NULL);
	row = 0;
	while (row < size)
	{
		if (!(map[row] = (char *)malloc(sizeof(char) * size + 1)))
			return (NULL);
		row += 1;
	}
	row = 0;
	while (row < size)
	{
		col = 0;
		while (col < size)
			map[row][col++] = EMPTY;
		map[row][col] = '\0';
		row += 1;
	}
	return (map);
}

char		**fillit_read(int fd)
{
	int		i;
	char	**map;

	i = 0;
	if (!(map = (char **)malloc(sizeof(char *) * BUFFER_SIZE)))
		return (NULL);
	while (i < TETROMINO_MAX_TOTAL)
	{
		if (!(map[i] = (char *)malloc(sizeof(char) * TETROMINO_SIZE)))
			return (NULL);
		ft_bzero(map[i], TETROMINO_SIZE);
		if (!(read(fd, map[i], TETROMINO_SIZE)))
			return (map);
		if (!(fillit_valid(map[i])))
			return (NULL);
		i += 1;
		g_num_tets = i;
	}
	return (NULL);
}
