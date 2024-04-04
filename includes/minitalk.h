/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 05:20:47 by mmorot            #+#    #+#             */
/*   Updated: 2024/03/06 09:17:47 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <stddef.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

// status == (0, 1, 2) == (PENDING, STARTING, COMPLETE)

typedef struct s_listen
{
	pid_t			pid;
	unsigned char	status;
	unsigned char	octet;
	unsigned char	bit;
	unsigned int	len;
	unsigned int	index;
	unsigned char	len_bit;
	char			*message;
}					t_listen;

typedef uint8_t		t_bool;

typedef struct s_state_receive
{
	pid_t			pid;
	t_bool			receive;
	t_bool			available;
	useconds_t		seconds;
	unsigned int	count;
}					t_state_receive;

unsigned char		*dec_to_binary(unsigned int dec, unsigned char bits);
unsigned int		binary_to_dec(unsigned char *binary, unsigned char bits);

int					ft_atoi(const char *str);
size_t				ft_strlen(char *str);
void				ft_putnbr(int n);

#endif
