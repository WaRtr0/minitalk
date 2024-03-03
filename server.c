/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42.frmmorot>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 01:32:39 by mmorot            #+#    #+#             */
/*   Updated: 2024/03/03 18:11:50 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_putnbr(int n)
{
	if (n < 0)
	{
		write(1, "-", 1);
		n = -n;
	}
	if (n > 9)
		ft_putnbr(n / 10);
	write(1, &"0123456789"[n % 10], 1);
}

void	get_len(t_bool sig, t_listen *listen)
{
	listen->len |= sig << (31 - listen->len_bit);
	listen->len_bit++;
	if (listen->len_bit == 32)
	{
		listen->status = 2;
		listen->len_bit = 0;
	}
}

void	get_letter(t_bool sig, t_listen *listen)
{
	if (listen->bit < 8)
	{
		listen->octet |= sig << (7 - listen->bit);
		listen->bit++;
	}
	if (listen->bit > 7)
	{
		listen->message[listen->index] = listen->octet;
		listen->index++;
		listen->octet = 0;
		listen->bit = 0;
	}
	if (listen->index == listen->len)
	{
		listen->message[listen->index] = 0;
		write(1, listen->message, listen->len + 1);
		free(listen->message);
		listen->message = NULL;
		listen->status = 0;
		listen->len = 0;
		listen->index = 0;
	}
}

void	get_message(t_bool sig, t_listen *listen)
{
	if (!listen->message)
	{
		listen->message = malloc(sizeof(unsigned char) * (listen->len + 1));
		if (!listen->message)
			exit(1);
	}
	get_letter(sig, listen);
}

void    signal_handler(int  signum)
{
	static t_listen listen = {0};
	t_bool			sig;
	if (signum == SIGUSR1)
		sig = 1;
	else
		sig = 0;
	
	if (!listen.status && !sig)
		listen.status = 1;
	else if (listen.status == 1)
		get_len(sig, &listen);
	else if (listen.status == 2)
		get_message(sig, &listen);
}

int main(void)
{
	signal(SIGUSR1, signal_handler);
	signal(SIGUSR2, signal_handler);
	write(1,"\x1b[33m=============================\x1b[0m\n",40);
	write(1, "PID   : \x1b[34m", 14);
	ft_putnbr(getpid());
	write(1, "\x1b[0m\n", 5);
	write(1, "CMD   : ./client \x1b[34m<pid> \x1b[32m<text>\x1b[0m\n", 45);
	write(1, "\x1b[33m=============================\n", 36);
	write(1, "=----------\x1b[31mMessage\x1b[33m----------=\n", 41);
	write(1, "=============================\x1b[0m\n", 35);
	while (1)
		usleep(50);
	return (0);
}