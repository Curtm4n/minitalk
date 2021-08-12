/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdapurif <cdapurif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 15:57:25 by cdapurif          #+#    #+#             */
/*   Updated: 2021/08/12 16:32:52 by cdapurif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk_bonus.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

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

void	my_handler(int signum)
{
	static int	n_octet = 0;

	if (signum == SIGUSR1)
		n_octet++;
	else
	{
		if (signum == n_octet)
		{
			write(1, "\n**The server received the string completely**\n", 47);
			exit(EXIT_SUCCESS);
		}
		else
			write(1, "\n**Some bits were lost during transmition**\n", 45);
	}
}

void	ft_client(pid_t pid, char *str)
{
	struct sigaction	sa;
	unsigned short		bit;
	unsigned char		c;

	sa.sa_handler = my_handler;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
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
	my_handler(ft_strlen(av[2]));
	return (0);
}
