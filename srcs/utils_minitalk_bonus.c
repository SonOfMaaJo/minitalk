/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_minitalk_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 01:00:13 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/01/31 17:46:46 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

int	is_valid_pid(char *pid)
{
	int	i;

	i = 0;
	if (!pid || !pid[0])
		return (0);
	while (pid[i])
	{
		if (!ft_isdigit(pid[i]))
			return (0);
		i++;
	}
	return (1);
}

t_client	*init_client(pid_t pid)
{
	t_client	*client;

	client = (t_client *)malloc(sizeof(t_client));
	if (!client)
		return (kill(pid, SIGUSR2), NULL);
	client->pid = pid;
	client->size = INITIAL_BUF_SIZE;
	client->len = 0;
	client->str = (char *)ft_calloc(client->size, sizeof(char));
	if (!client->str)
	{
		kill(pid, SIGUSR2);
		return (free(client), NULL);
	}
	return (client);
}

void	free_client(t_client **client)
{
	if (client && *client)
	{
		if ((*client)->str)
			free((*client)->str);
		free(*client);
		*client = NULL;
	}
}

int	add_char(t_client *client, char octet)
{
	char	*new_str;

	if (client->len + 1 >= client->size)
	{
		new_str = (char *)ft_calloc(client->size * 2, sizeof(char));
		if (!new_str)
			return (0);
		ft_memmove(new_str, client->str, client->len);
		free(client->str);
		client->str = new_str;
		client->size *= 2;
	}
	client->str[client->len++] = octet;
	return (1);
}
