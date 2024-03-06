/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 01:32:39 by mmorot            #+#    #+#             */
/*   Updated: 2024/03/06 03:06:33 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <bits/types/siginfo_t.h>
#include <bits/types/sigset_t.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

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
		listen->pid = 0;
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

void    signal_handler(int  signum, siginfo_t *info, void *context )
{
	static t_listen listen = {0};
	t_bool			sig;

	if (listen.pid == 0)
		listen.pid = info->si_pid;
	if(info->si_pid && listen.pid == info->si_pid)
	{
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
		kill(info->si_pid, SIGUSR1);
	}
	else if(info->si_pid)
		kill(info->si_pid, SIGUSR2);
}

int main(void)
{
	struct sigaction sa;
	sa.sa_sigaction = signal_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO; 

	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	write(1,"\x1b[33m=============================\x1b[0m\n",40);
	write(1, "PID   : \x1b[34m", 14);
	ft_putnbr(getpid());
	write(1, "\x1b[0m\n", 5);
	write(1, "CMD   : ./client \x1b[34m<pid> \x1b[32m<text>\x1b[0m\n", 45);
	write(1, "\x1b[33m=============================\n", 36);
	write(1, "=----------\x1b[31mMessage\x1b[33m----------=\n", 41);
	write(1, "=============================\x1b[0m\n", 35);
	while (1)
		pause();
	return (0);
}