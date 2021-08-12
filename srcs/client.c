/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdapurif <cdapurif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 15:57:25 by cdapurif          #+#    #+#             */
/*   Updated: 2021/08/12 00:37:43 by cdapurif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

pid_t	ft_atoi(char *str)
{
	pid_t	nb;

	nb = 0;
	while (*str >= '0' && *str <= '9')
	{
		nb = nb * 10 + *str - '0';
		str++;
	}
	return (nb);
}

void	ft_client(pid_t pid, char *str)
{
	unsigned short	bit;
	unsigned char	c;

	while (*str)
	{
		c = *str;
		bit = 128;
		while (bit > 0)
		{
			if (!(c & bit))
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			bit /= 2;
			usleep(TIME);
		}
		str++;
	}
}

int	main(int ac, char **av)
{
	if (ac != 3)
	{
		write(1, "The client requires the server PID and a string\n", 48);
		exit(EXIT_FAILURE);
	}
	ft_client(ft_atoi(av[1]), av[2]);
	return (0);
}
