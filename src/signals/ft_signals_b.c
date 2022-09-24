/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals_b.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  jknotts <jknotts@student.21-school>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 22:43:52 by jknotts           #+#    #+#             */
/*   Updated: 2022/09/24 23:07:18 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../minishell.h"

/*
 * catch ctrl+c in interactive mode
 */
void	ft_parent_interactive_sigint(int sign)
{
	if (sign == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

/*
 * catch ctrl+c in active mode
 */
void	ft_parent_active_sigint(int sign)
{
	if (sign == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
	}
}

/*
 * catch ctrl+/ in active mod
 */
void	ft_parent_active_sigquit(int sign)
{
	if (sign == SIGQUIT)
	{
		ft_write_fd(1, "Quit\n");
	}
}
