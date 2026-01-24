/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 15:56:15 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/01/24 18:43:46 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static unsigned char    octet;

static unsigned char power(int nb, int power)
{
    int i;
    int res;

    i = 0;
    res = 1;
    while (i++ < power)
        res = res * nb;
    return ((unsigned char)res);
}

void    handler(int sig)
{
    static unsigned char    byte;
    static int              power1;
    static int             power2;

    if (sig == SIGUSR2)
         byte += power(2, 3 - power1++);
    else
        power1++;
    if (power1 == 4)
    {
        octet = byte * power(16, 1 - power2++);
        power1 = 0;
        byte  = 0;
		if (power2 == 2)
			power2 = 0;
    }
}

static void	*get_string(char **string)
{
    char	*string_tmp;
    int     len;

	if (*string == NULL)
	{
		*string = (char *)calloc(1, sizeof(char));
		if (!*string)
			return (write(2, "Error : an allocation fail", 26), NULL);
	} 
    string_tmp = *string;
    len = ft_strlen(string_tmp);
    *string = (char *)calloc(len + 2, sizeof(char));
    if (!*string)
    	return (free(*string), write(2, "Error : an allocation fail", 26), NULL);
    ft_strlcat(*string, string_tmp, len + 2);
    *string[len + 1] = octet;
	*string[len + 2] = '\0';
	free(string_tmp);
	return (NULL);
}

int main(void)
{
	char		**string;
	t_sigaction	sa;

	sa.sa_handler = handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	octet = 1;
	string = (char **)malloc(sizeof(char *));
	if (!string)
		return (write(2, "Error : an allocation fail\n", 26), 0);
	*string = NULL;
    ft_printf("%d\n", getpid());
    if (sigaction(SIGUSR1, &sa, NULL) != -1 
		&& sigaction(SIGUSR2, &sa, NULL) != -1)
	{
        get_string(string);
		if (!octet)
		{
			ft_printf("%s\n", *string);
			free(*string);
			*string = NULL;
		}
	}
    while (1)
        sleep(1);
    return (0);
}
