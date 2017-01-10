/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biasinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 13:06:54 by biasinov          #+#    #+#             */
/*   Updated: 2017/01/09 18:06:39 by biasinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "header.h"
#include <unistd.h>
#include <stdio.h>

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define BUFF 600

static	void	check_buff(char *buff)
{
	int	nline;
	int dot;
	int diez;

	nline = 0;
	dot = 0;
	diez = 0;
	while (*buff)
	{
		if (*buff == '.')
			dot++;
		else if (*buff == '#')
			diez++;
		else if (*buff == '\n')
			nline++;
		else
			error_exit(1);
		buff++;
	}
	if (dot % 12 != 0 || diez % 4 != 0 || (nline + 1) % 5 != 0)
		error_exit(1);
}

static	void	read_file(char *source, char *buff)
{
	int	fd;
	int ret;

	fd = open(source, O_RDONLY);
	if (fd == -1)
		error_exit(2);
	ret = read(fd, buff, 600);
	buff[ret] = '\0';
	check_buff(buff);
	if (close(fd) == -1)
		error_exit(3);
}

int				main(int argc, char **argv)
{
	char		*buff;
	t_pieces	*all_pieces;

	if (argc != 2)
		error_exit(0);

	buff = (char *)malloc(BUFF);
	read_file(argv[1], buff);
	all_pieces = get_pieces_from_buff(buff);
	free(buff);



	//TEST PRINT
	while (all_pieces)
	{
		printf("index: %d | x: %d -  y: %d\n",all_pieces->index, all_pieces->piece.pos[0].x, all_pieces->piece.pos[0].y);
		printf("index: %d | x: %d -  y: %d\n",all_pieces->index, all_pieces->piece.pos[1].x, all_pieces->piece.pos[1].y);
		printf("index: %d | x: %d -  y: %d\n",all_pieces->index, all_pieces->piece.pos[2].x, all_pieces->piece.pos[2].y);
		printf("index: %d | x: %d -  y: %d\n",all_pieces->index, all_pieces->piece.pos[3].x, all_pieces->piece.pos[3].y);
		printf("Visited: %d\n", all_pieces->visited);
		printf("\n");

		all_pieces = all_pieces->next;
	}
}
