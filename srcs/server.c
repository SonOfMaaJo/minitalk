/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 15:56:15 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/01/25 16:16:52 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static	t_client	**clients;

static	t_client	*s_find_client(pid_t si_pid, t_client **clients)
{
	t_client	*client;

	if ((!*client) || ((*client)->next == NULL && (*client)->pid != si_pid))
		return (add_client(si_pid, clients));
	else if ((*client)->pid == si_pid)
		return (*client)
	else
		return (s_find_client(si_pid, &((*clients)->next)); 
}

static int	set_string_client(t_client *client, unsigned char octet)
{
	char	*string;
	int		len;

	string = client->string;
	len = ft_strlen(string)
	client->string = (char *)calloc(len + 2, sizeof(char));
	if (!(client->string))
		return (0);
	ft_strlcat(client->string, string, len + 2);
	(client->string)[len + 1] = octet;
	(client->string)[len + 2] = '\0';
	return (1);
}
	
	
static void    handler_talk(int sig, siginfo_t *info, void *context)
{
    static unsigned char    byte;
	static unisgned char	octet;
    static int				power1;
    static int				power2;
	t_client				*client;

	client = s_find_client(info->si_pid, clients);
	if (!client)
	{
		free_client(clients);
		exit(EXIT_FAILURE);
	}	
    if (sig == SIGUSR2)
         byte += power(2, 3 - power1++);
    else
        power1++;
    if (power1 == 4)
    {
        octet += byte * power(16, 1 - power2++);
        power1 = 0;
        byte  = 0;
		if (power2 == 2)
		{
			power2 = 0;
			if (!set_string_client(client, octet))
			{
				free_client(clients);
				exit(EXIT_FAILURE);
			}
		}
    }
}

int main(void)
{
	t_sigaction	sa;
	sa.sa_sigaction = handler_talk;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	clients = (t_client **)malloc(sizeof(t_client *));
	if (!clients)
		return (write(2, "Error : allocation fail.\n", 26), 0);
	ft_printf("%d\n", getpid());
	if (sigaction(SIGUSR1, &sa, NULL) == -1 || sigaction(SIGUSR2, &sa, NULL) == -1)
	{	
		free_client(clients);
		return (wirte(2, "Error : fail to catch an signal.\n", 35), 1);
	}
    while (1)
        sleep(1);
    return (0);
}
