/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 15:55:20 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/01/28 21:18:52 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	g_receiver;

static void	ack_handler(int sig)
{
	if (sig == SIGUSR1)
		g_receiver = 1;
	else if (sig == SIGUSR2)
	{
		write(2, "Error: server didn't receive my message.\n", 41);
		exit(EXIT_FAILURE);
	}
}

static void	send_bits(pid_t pid, unsigned char octet)
{
	int	bit;
	int	sig;

	bit = 7;
	while (bit >= 0)
	{
		g_receiver = 0;
		if ((octet >> bit) & 1)
			sig = SIGUSR2;
		else
			sig = SIGUSR1;
		if (kill(pid, sig) == -1)
		{
			write(2, "Error : Fail to send an signal.\n", 33);
			exit(EXIT_FAILURE);
		}
		while (!g_receiver)
			usleep(100);
		bit--;
	}
}

int	main(int ac, char **av)
{
	pid_t		server_pid;
	int			i;
	t_sigaction	sa;

	if (ac != 3 || !is_valid_pid(av[1]))
	{
		write(2, CLIENT_USG_MSG, ft_strlen(CLIENT_USG_MSG));
		return (1);
	}
	server_pid = ft_atoi(av[1]);
	sa.sa_handler = ack_handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
		return (write(2, SIG_ERROR_MSG, ft_strlen(SIG_ERROR_MSG)), 1);
	i = 0;
	while (av[2][i])
		send_bits(server_pid, av[2][i++]);
	send_bits(server_pid, '\0');
	write(1, CLIENT_REC_FEED, ft_strlen(CLIENT_REC_FEED));
	return (0);
}
