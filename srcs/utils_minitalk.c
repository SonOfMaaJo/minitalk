/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_minitalk.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 01:00:13 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/01/22 03:57:03 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int send_bytes(int oc, pid_t pid_server)
{
    int nb_bytes;
    int res;

    nb_bytes = 8;
    res = 0;
    while (1)
    {
        res = oc / nb_bytes;
        if (res == 0)
        {
            if (kill(pid_server, SIGUSR1) == -1 || usleep(100000) == -1)
                return (0);
        }
        else
            if (kill(pid_server, SIGUSR2) == -1 || usleep(100000) == -1)
                return (0);
        oc = oc % nb_bytes;
        nb_bytes = nb_bytes / 2;
        if (!nb_bytes)
            return (1);
    }
}

int send_octet(unsigned char octet, pid_t pid_server)
{
    if(!send_bytes(octet / 16, pid_server))
        return (0);
    if (!send_bytes(octet % 16, pid_server))
        return (0);
    return (1);
}
