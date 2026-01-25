/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_minitalk.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 01:00:13 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/01/25 16:04:30 by vnaoussi         ###   ########.fr       */
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

unsigned char	power(int nb, int power)
{
	int	i;
	int	res;

	i = 0;
	res = 1;
	while (i++ < power)
		res = res * nb;
	return ((unsigned char)res);
}

int send_octet(unsigned char octet, pid_t pid_server)
{
    if(!send_bytes(octet / 16, pid_server))
        return (0);
    if (!send_bytes(octet % 16, pid_server))
        return (0);
    return (1);
}

t_client	*add_client(pid_t si_pid, t_client **clients)
{
		t_client	*client;
		t_client	*tmp;

		client = (t_client *)malloc(sizeof(t_client));
		tmp = NULL;
		if (!client)
			return (NULL)
		client->pid = si_pid;
		client->next = NULL;
		client->string = (char *)calloc(1, sizeof(char));
		if (!(client->string))
			return (free(client), NULL);
		if (*string)
		{
			tmp	= *clients;
			while (tmp->next != NULL)
				tmp = tmp->next;
			tmp->next = client
		}
		else
			*client = client;
		return (client);
}

void free_client(t_client **clients)
{
	t_client	*client;

	client = (*clients)->next;
	free((*clients)->string);
	free(*clients)
	if (client == NULL)
	{
		free(clients);
		return ;
	}
	free_client(&client);
}
	
