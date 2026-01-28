/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 15:49:08 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/01/28 14:38:15 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H
# include "../libft/libft.h"
# include <signal.h>
# define SIG_ERROR_MSG "Error: Failed to set up signal handlers.\n"
# define CLIENT_USG_MSG "Usage: ./client <SERVER_PID> <MESSAGE>\n"
# define CLIENT_REC_FEED "Success: Message received by server.\n"
# define ALLOC_ERROR_MSG "Error: Memory allocation failed.\n"

# define INITIAL_BUF_SIZE 100

typedef struct sigaction	t_sigaction;

typedef struct s_client
{
	pid_t	pid;
	char	*str;
	size_t	size;
	size_t	len;
}	t_client;

int			is_valid_pid(char *pid);
t_client	*init_client(pid_t pid);
void		free_client(t_client **client);
int			add_char(t_client *client, char c);

#endif
