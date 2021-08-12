/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdapurif <cdapurif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 10:37:10 by cdapurif          #+#    #+#             */
/*   Updated: 2021/08/12 16:33:05 by cdapurif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk_bonus.h"

void	ft_putpid(pid_t pid)
{
	char	n;

	if (pid > 9)
		ft_putpid(pid / 10);
	n = pid % 10 + '0';
	write(1, &n, 1);
}

void	display_pid(void)
{
	pid_t	pid;

	pid = getpid();
	write(1, "Server PID: ", 13);
	ft_putpid(pid);
	write(1, "\n", 1);
}

void	handler(int signum, siginfo_t *info, void *context)
{
	static unsigned short	cpt = 128;
	static unsigned char	c = 0;

	(void)context;
	(void)info;
	if (signum == SIGUSR2)
		c |= cpt;
	cpt >>= 1;
	if (cpt == 0)
	{
		write(1, &c, 1);
		cpt = 128;
		c = 0;
		kill(info->si_pid, SIGUSR1);
	}
}

void	launch_serv(void)
{
	struct sigaction	sa;

	display_pid();
	sa.sa_sigaction = handler;
	sa.sa_flags = SA_RESTART | SA_SIGINFO | SA_NODEFER;
	sigemptyset(&sa.sa_mask);
	while (1)
	{
		sigaction(SIGUSR1, &sa, NULL);
		sigaction(SIGUSR2, &sa, NULL);
	}
}

int	main(void)
{
	launch_serv();
	return (0);
}
