/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42.frmmorot>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 01:32:36 by mmorot            #+#    #+#             */
/*   Updated: 2024/03/03 17:48:27 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void    send_dec(int pid, unsigned int dec)
{
    unsigned char i;

    i = 0;
    while (i < 32)
    {
        if (dec & 1 << (31 - i))
            kill(pid, SIGUSR1);
        else
            kill(pid, SIGUSR2);
        i++;
        usleep(200);
    }
}

void    send_char(int pid, unsigned char c)
{
    unsigned char i;

    i = 0;
    while (i < 8)
    {
        if (c & 1 << (7 - i))
            kill(pid, SIGUSR1);
        else
            kill(pid, SIGUSR2);
        i++;
        usleep(200);
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

void    send_message(int pid, char *message)
{
    size_t len;

    len = ft_strlen(message);
    printf("Sending %zu bytes\n", len);
    kill(pid, SIGUSR2);
    usleep(200);
    send_dec(pid, len);
    while (*message)
    {
        send_char(pid, *message);
        message++;
    }
}

int main(int ac, char **argv)
{
    unsigned int pid;

    if (ac != 3)
    {
        printf("Usage: ./client [PID] [MESSAGE]\n");
        return (1);
    }

    pid = ft_atoi(argv[1]);
    printf("Sending message to %d\n", pid);
    send_message(pid, argv[2]);
    return (0);
}