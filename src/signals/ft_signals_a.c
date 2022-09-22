#include "../../minishell.h"

/*
 * set handler signals if we don't enter data (interactive mode)
 */
void	ft_set_parent_interactive(void)
{
	signal(SIGINT, &ft_parent_interactive_sigint);
	signal(SIGQUIT, SIG_IGN);
}

/*
 * set handler signals if we enter something (active mode)
 */
void	ft_set_parent_active(void)
{
	signal(SIGINT, &ft_parent_active_sigint);
	signal(SIGQUIT, &ft_parent_active_sigquit);
}

//todo:
void	ft_set_parent_heredoc(void)
{
	struct sigaction	response;

	sigemptyset(&response.sa_mask);
	response.sa_flags = SA_SIGINFO;
	response.sa_handler = &ft_parent_active_sigint;
	sigaction(SIGINT, &response, NULL);
	signal(SIGQUIT, SIG_IGN);
}

//todo:
void	ft_set_child_active(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
