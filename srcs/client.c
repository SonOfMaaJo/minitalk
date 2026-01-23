/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 15:55:20 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/01/22 03:21:56 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int main(int ac, char **av)
{
    char    *string;
    int     len;

    if (ac != 3)
        return (ft_printf("usage : client PID_SERVER STRING_TO_SEND\n"));
    len = ft_strlen(av[2]);
    string = (char *)malloc(sizeof(char) * (len + 1));
    if (!string)
        return (ft_printf("an error occur\n"));
    send_octet((unsigned char)'a', ft_atoi(av[1]));
    ft_printf("%s", string);
    return (0);
}
