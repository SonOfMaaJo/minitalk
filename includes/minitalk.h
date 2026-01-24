/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 15:49:08 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/01/24 18:56:46 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H
# include "../libft/libft.h"
# include <signal.h>

typedef struct sigaction t_sigaction;
typedef struct s_client
{
	pid_t		pid_client;
	char		*string;
	t_client	*next;
}	t_client;

int send_octet(unsigned char octet, pid_t pid_server);

#endif
