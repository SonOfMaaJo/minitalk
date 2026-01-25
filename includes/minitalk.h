/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 15:49:08 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/01/25 16:31:35 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H
# include "../libft/libft.h"
# include <signal.h>

typedef struct sigaction t_sigaction;
typedef struct s_client
{
	pid_t				pid_client;
	char				*string;
	struct	s_client	*next;
}	t_client;

int				send_octet(unsigned char octet, pid_t pid_server);
unsigned char	power(int nb, int power);
void			free_client(t_client **clients);
t_client		*add_client(pid_t si_pid, t_client **clients);

#endif
