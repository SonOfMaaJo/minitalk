/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 15:56:15 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/01/31 17:11:46 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

static t_client	*g_client;

static void	send_feedf(pid_t pid, int sig, char *MSG)
{
	if (kill(pid, sig) == -1)
	{
		write(2, "Error : fail to send an signal\n", 32);
		exit(EXIT_FAILURE);
	}
	if (sig == SIGUSR1)
		ft_printf("%s", g_client->str);
	free_client(&g_client);
	if (sig == SIGUSR2 && MSG)
	{
		write (2, MSG, ft_strlen(MSG));
		exit(EXIT_FAILURE);
	}
}

static void	handle_signal(int sig, siginfo_t *info, void *context)
{
	static unsigned char	octet;
	static int				bits;

	(void)context;
	if (!g_client)
		g_client = init_client(info->si_pid);
	if (!g_client)
		send_feedf(info->si_pid, SIGUSR2, "Error : an allocation fail\n");
	if (sig == SIGUSR2)
		octet |= (1 << (7 - bits));
	if (++bits == 8)
	{
		if (octet == '\0')
			send_feedf(info->si_pid, SIGUSR1, NULL);
		else if (!add_char(g_client, octet))
			send_feedf(info->si_pid, SIGUSR2, "Error : an allocation fail\n");
		bits = 0;
		octet = 0;
	}
	if (g_client && kill(g_client->pid, SIGUSR1) == -1)
	{
		write(2, "Error : fail to send an signal\n", 32);
		exit(EXIT_FAILURE);
	}
}

int	main(void)
{
	t_sigaction	sa;

	ft_printf("Server PID: %d\n", getpid());
	sa.sa_sigaction = handle_signal;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		write(2, SIG_ERROR_MSG, ft_strlen(SIG_ERROR_MSG));
		return (1);
	}
	while (1)
		pause();
	return (0);
}
