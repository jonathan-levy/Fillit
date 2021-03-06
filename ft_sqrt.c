/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolevy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 16:15:44 by jolevy            #+#    #+#             */
/*   Updated: 2018/03/16 16:15:46 by jolevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

double		ft_sqrt(double x)
{
	long	i;

	i = 1;
	if (x < 0)
		return (0);
	while (i * i < x)
		i += 1;
	return (i);
}
