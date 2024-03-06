/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 01:32:36 by mmorot            #+#    #+#             */
/*   Updated: 2024/03/06 03:44:45 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <stdio.h>
#include <unistd.h>

static  t_state_receive server;

void    send_dec(int pid, unsigned int dec)
{
    unsigned char i;

    i = 0;
    while (i < 32)
    {
        server.receive = 0;
        if (dec & 1 << (31 - i))
            kill(pid, SIGUSR1);
        else
            kill(pid, SIGUSR2);

        while (!server.receive)
            usleep(5);
        i++;
    }
}

void    send_char(int pid, unsigned char c)
{
    unsigned char i;

    i = 0;
    while (i < 8)
    {
        server.receive = 0;
        if (c & 1 << (7 - i))
            kill(pid, SIGUSR1);
        else
            kill(pid, SIGUSR2);
        while (!server.receive)
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
    server.count = 0;
    server.seconds = 50;
    while (!server.available)
    {
        if (server.count == 2)
        {
            printf("Le serveur est actuellement occuper...\n...Veuillez patienter...\n");
            server.seconds = 500000;
        }
        usleep(server.seconds);
        kill(server.pid, SIGUSR2);
        server.count++;
    }
    send_dec(server.pid, len);
    while (*message)
    {
        send_char(server.pid, *message);
        message++;
    }
    while (!server.receive)
        usleep(5);
    printf("Votre message a bien ete recu\n");
}

void    signal_handler(int  signum, siginfo_t *info, void *context )
{
    if (signum == SIGUSR1 && info->si_pid && info->si_pid == server.pid)
    {
        server.receive = 1;
        server.available = 1;
    }
    else
        server.available = 0;
}

int main(int ac, char **argv)
{
    struct sigaction sa;
    server.available = 0;
    server.receive = 0;
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

    server.pid = ft_atoi(argv[1]);
    if (server.pid < 1)
        exit(-1);
    send_message(argv[2]);
    return (0);
}