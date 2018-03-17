/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 18:40:51 by famartin          #+#    #+#             */
/*   Updated: 2018/03/16 18:48:43 by famartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static void		fillit_usage(char *argv0)
{
	ft_putstr("usage: ");
	ft_putstr(argv0);
	ft_putstr(" [fillit_file]\n");
}

static void		fillit_print_map(char **map)
{
	size_t		i;
	size_t		len;

	i = -1;
	len = ft_strlen(*map);
	while (++i < len)
	{
		ft_putstr(map[i]);
		ft_putchar('\n');
	}
}

int				main(int argc, char *argv[])
{
	int			fd;
	char		**map;
	t_tetromino *tetrominos;

	if (argc == 2)
	{
		if ((fd = open(argv[1], O_RDONLY)) == -1)
			ft_putstr("error\n");
		else if ((map = fillit_read(fd)) && (ft_strlen(map[0])) && \
				(!map[g_num_tets - 1][TETROMINO_SIZE - 1]))
		{
			tetrominos = fillit_tetromino(map);
			map = fillit_solve(tetrominos);
			fillit_print_map(map);
			free(tetrominos);
			ft_memdel((void **)map);
		}
		else
			ft_putstr("error\n");
		close(fd);
	}
	else
		fillit_usage(argv[0]);
	return (0);
}
