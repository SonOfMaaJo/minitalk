/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 15:56:15 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/01/22 15:12:48 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static unsigned char    octet;

int power(int nb, int power)
{
    int i;
    int res;

    i = 0;
    res = 1;
    while (i++ < power)
        res = res * nb;
    return (res);
}

void    handler(int sig)
{
    static unsigned char    byte;
    static int              power;
    static  int             power2;

    if (sig == SIGUSR2)
         byte += power(16, 3 - power++);
    else
        power++;
    if (power == 3)
    {
        octet = byte * power(2, 1 - power2++);
        power = 0;
        byte  = 0;
    }
}

char    *get_string()
{
    static char    *string;
    char    *string_tmp;
    int     len;

    string = (char*)malloc(sizeof(char));
    if(!string)
        return (NULL);
    string[0] = '\0';
    while (1)
    {
        if(signal(SIGUSR1, handler) == -1 || signal(SIGUSR2, handler) == -1)
            return (free(string), ft_printf("Failed to catched a signal\n"), 1);
        string_tmp = string;
        len = ft_strlen(string_tmp);
        string = (char *)malloc(sizeof(char) * (len + 1));
        if (!string)
            return (free(string_tmp), ft_printf("Error\n"), 1);
        ft_strlcat(string, string_tmp, len + 1);
        string[len] = octet;
        if (!octet)
            return (free(string_tmp), string);
    }
}

int main(void)
{
    ft_printf("%d\n", getpid());
    if (signal(SIGUSR1, handler) != -1 && signal(SIGUSR2, handler) != -1)
        get_string()
    while (1)
        sleep(1);
    return (0);
}
