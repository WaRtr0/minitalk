/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 01:32:36 by mmorot            #+#    #+#             */
/*   Updated: 2024/03/06 06:37:44 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static t_state_receive	g_server;

void	send_dec(int pid, unsigned int dec)
{
	unsigned char	i;

	i = 0;
	while (i < 32)
	{
		g_server.receive = 0;
		if (dec & 1 << (31 - i))
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		while (!g_server.receive)
			usleep(5);
		i++;
	}
}

void	send_char(int pid, unsigned char c)
{
	unsigned char	i;

	i = 0;
	while (i < 8)
	{
		g_server.receive = 0;
		if (c & 1 << (7 - i))
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		while (!g_server.receive)
			usleep(5);
		i++;
	}
}

void	send_message(char *message)
{
	size_t	len;

	len = ft_strlen(message);
	g_server.count = 0;
	g_server.seconds = 50;
	kill(g_server.pid, SIGUSR2);
	while (!g_server.receive && ++g_server.count && g_server.count < 10000)
		usleep(5);
	if (!g_server.available)
	{
		write(2, "Server No Found\n", 17);
		exit(1);
	}
	send_dec(g_server.pid, len);
	while (*message)
	{
		send_char(g_server.pid, *message);
		message++;
	}
	while (!g_server.receive)
		usleep(5);
	write(1, "Message received\n", 18);
}

void	signal_handler(int signum, siginfo_t *info, void *context)
{
	(void)context;
	if (signum == SIGUSR1 && info->si_pid && info->si_pid == g_server.pid)
	{
		g_server.receive = 1;
		g_server.available = 1;
	}
	else
	{
		write(2, "Server unavailable\n", 20);
		exit(1);
	}
}

int	main(int ac, char **argv)
{
	struct sigaction	sa;

	g_server.available = 0;
	g_server.receive = 0;
	sa.sa_sigaction = signal_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	if (!sigaction(SIGUSR1, &sa, NULL) && sigaction(SIGUSR2, &sa, NULL))
	{
		write(2, "Signal Error", 12);
		exit(1);
	}
	if (ac != 3)
	{
		write(1, "Usage: ./client <PID> <MESSAGE>\n", 33);
		return (1);
	}
	g_server.pid = ft_atoi(argv[1]);
	if (g_server.pid < 1)
		exit(-1);
	send_message(argv[2]);
	return (0);
}
