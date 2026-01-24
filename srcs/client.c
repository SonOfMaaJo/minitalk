/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 15:55:20 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/01/24 18:23:42 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int main(int ac, char **av)
{
    int     len;
	int		i;

    if (ac != 3)
        return (write(2, "usage : client PID_SERVER STRING_TO_SEND\n", 45), 0);
    len = ft_strlen(av[2]);
	i = 0;
	while (av[2][i])
	{
		send_octet((unsigned char)av[2][i++], ft_atoi(av[1]));
		usleep(100000);
	}
	send_octet((unsigned char)'\0', ft_atoi(av[1]));
    return (0);
}
