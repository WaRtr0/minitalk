/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42.frmmorot>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 05:20:47 by mmorot            #+#    #+#             */
/*   Updated: 2024/03/03 05:23:22 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include <stddef.h>



// status == (0, 1, 2) == (PENDING, STARTING, COMPLETE)

typedef struct s_listen {
	unsigned char	status;
	unsigned char	octet;
	unsigned char	bit;
	unsigned int	len;
    unsigned int	index;
	unsigned char	len_bit;
	char			*message;
}   t_listen;

typedef unsigned char t_bool;

unsigned char *dec_to_binary(unsigned int dec, unsigned char bits);
unsigned int    binary_to_dec(unsigned char *binary, unsigned char bits);

int             ft_atoi(const char *str);

#endif
