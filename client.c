/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 01:32:36 by mmorot            #+#    #+#             */
/*   Updated: 2024/03/06 05:45:12 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <stdio.h>
#include <unistd.h>

static  t_state_receive g_server;

void    send_dec(int pid, unsigned int dec)
{
    unsigned char   i;

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

void    send_char(int pid, unsigned char c)
{
    unsigned char   i;

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

size_t  ft_strlen(char *str)
{
    size_t i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

void    send_message(char *message)
{
    size_t  len;

    len = ft_strlen(message);
    g_server.count = 0;
    g_server.seconds = 50;
    kill(g_server.pid, SIGUSR2);
    while (!g_server.receive && ++g_server.count && g_server.count < 10000)
        usleep(5);
    if (!g_server.available)
        write(1, "Le serveur est actuellement occupe",36);
    send_dec(g_server.pid, len);
    while (*message)
    {
        send_char(g_server.pid, *message);
        message++;
    }
    while (!g_server.receive)
        usleep(5);
    printf("Votre message a bien ete recu\n");
}

void    signal_handler(int  signum, siginfo_t *info, void *context )
{
    if (signum == SIGUSR1 && info->si_pid && info->si_pid == g_server.pid)
    {
        g_server.receive = 1;
        g_server.available = 1;
    }
    else
    {
        printf("Le serveur est actuellement occupe veuillez envoye votre message plus tard\n");
        exit(0);
    }
}

int main(int ac, char **argv)
{
    struct sigaction sa;
    g_server.available = 0;
    g_server.receive = 0;
	sa.sa_sigaction = signal_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO; 
	sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);
    if (ac != 3)
    {
        printf("Usage: ./client [PID] [MESSAGE]\n");
        return (1);
    }

    g_server.pid = ft_atoi(argv[1]);
    if (g_server.pid < 1)
        exit(-1);
    send_message(argv[2]);
    return (0);
}