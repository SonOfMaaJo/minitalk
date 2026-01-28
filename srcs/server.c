/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 15:56:15 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/01/28 15:45:02 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static t_client	*g_client;

static void	send_feedf(int sig)
{
	kill(g_client->pid, sig);
	if (sig == SIGUSR1)
		ft_printf("%s\n", g_client->str);
	free_client(&g_client);
}

static void	handle_signal(int sig, siginfo_t *info, void *context)
{
	static unsigned char	octet;
	static int				bits;

	(void)context;
	if (!g_client)
		g_client = init_client(info->si_pid);
	if (!g_client)
		return ;
	if (sig == SIGUSR2)
		octet |= (1 << (7 - bits));
	if (++bits == 8)
	{
		if (octet == '\0')
			send_feedf(SIGUSR1);
		else if (!add_char(g_client, octet))
			send_feedf(SIGUSR2);
		bits = 0;
		octet = 0;
	}
	kill(info->si_pid, SIGUSR1);
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
		ft_printf(SIG_ERROR_MSG);
		return (1);
	}
	while (1)
		pause();
	return (0);
}
