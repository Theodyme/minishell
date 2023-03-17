/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 16:52:19 by mabimich          #+#    #+#             */
/*   Updated: 2022/06/08 21:25:54 by mabimich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <mlx.h>
# include <stdlib.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include "libft/includes/libft.h"
# include <fcntl.h>

# define WINDOW_W 1800
# define WINDOW_H 1660
# define WHITE 0xFFFFFF
# define BLACK 0x000000
# define RED 0xFF1111

typedef struct s_data
{	
	void	*ptr;
	void	*win;
	void	*img;
	char	*line;
	int		lenl;
	int		max_x;
	int		max_y;
	int		marge_x;
	int		marge_y;
	int		env;
	int		done;
	int		open;
	int		pas;
	int		ncollect;
	char	*addr;
	char	*path_p;
	char	*path_c;
	char	*path_e;
	char	*path_w;
	char	*path_v;
	int		i;
	int		bpp;
	int		line_len;
	int		endian;
	int		width_sprite;
	void	*p;
	void	*c;
	void	*e;
	void	*w;
	void	*v;
}			t_data;

int		free_solong(t_data *d);
char	*ft_3strjoin(char *s1, char *s2, char *s3);
char	*ft_strjoin_free2(char *s1, char *s2);
int		mv(t_data *data, int shift);
int		mv_up(t_data *data);
int		mv_down(t_data *data);
int		mv_left(t_data *data);
int		mv_right(t_data *data);
char	*ft_get_extension(char *name_file);
int		parsing(int fd, t_data *data);

int		render_back(t_data *data, int color);
int		render_cache_pas(t_data *data, int color);
int		xmp_to_cache(t_data *d);
int		render(t_data *data);
int		handle_keypress(int key, t_data *data);
void	cache_to_img(t_data *data);

void	cache_to_img(t_data *data);

int		render_mechant(t_data *data, size_t i0, size_t j0);

#endif
