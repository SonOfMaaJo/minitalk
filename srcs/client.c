/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 15:55:20 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/01/25 16:31:14 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static	pid_t	pid_server;

static	void	handler_client(int sig, siginfo_t *info, void *context)
{
		if (pid_server == info->si_pid)
		{
			if (sig == SIGUSR1)
				write(1, "Server received my string\n", 40);
			else
				write(1, "Server don't received my message\n", 50);
		}
		exit(1);
}
	
int main(int ac, char **av)
{
    int     len;
	int		i;
	t_sigaction	sa;

	sa.sa_sigaction = handler_client;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
    if (ac != 3)
        return (write(2, "usage : client PID_SERVER STRING_TO_SEND\n", 45), 0);
    len = ft_strlen(av[2]);
	pid_server = ft_atoi(av[1]);
	i = 0;
	while (av[2][i])
	{
		send_octet((unsigned char)av[2][i++], pid_server);
		usleep(100000);
	}
	send_octet((unsigned char)'\0', pid_server);
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		return (write(2, "Error : fail to catch a signal.\n", 50), 1);
	pause();
    return (0);
}
