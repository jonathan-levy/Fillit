/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolevy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 16:23:26 by jolevy            #+#    #+#             */
/*   Updated: 2018/03/16 16:23:27 by jolevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

# define EMPTY '.'
# define BLOCK '#'
# define LETTER 'A'
# define NEW_LINE '\n'
# define SIZE 4
# define TETROMINO_SIZE 21
# define TETROMINO_MAX_TOTAL (26 - (LETTER - 'A'))
# define BUFFER_SIZE TETROMINO_SIZE * TETROMINO_MAX_TOTAL

int        g_num_tets;

typedef struct            s_tetromino
{
    char                letter;
    int                    x[4];
    int                    y[4];
    int                    width;
    int                    height;
    struct s_tetromino    *next;
}                        t_tetromino;

void                    ft_bzero(void *s, size_t n);
char                    **ft_strsplit(char const *s, char c);
void                    ft_putchar(char c);
void                    ft_putstr_fd(char const *s, int fd);
void                    ft_putstr(char const *s);
size_t                    ft_strlen(const char *s);
void                    ft_memdel(void **ap);
void                    *ft_memset(void *b, int c, size_t len);
double                    ft_sqrt(double x);
size_t                    ft_wordcount(const char *s, char c);
size_t                    ft_wordlen(const char *s, char c);

char                    **fillit_read(int fd);
char                    **fillit_create_map(int size);
char                    **fillit_solve(t_tetromino *tet);
t_tetromino                *fillit_tetromino(char **map);

#endif
