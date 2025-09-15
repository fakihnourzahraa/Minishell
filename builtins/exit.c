/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwehbe <miwehbe@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 17:33:30 by miwehbe           #+#    #+#             */
/*   Updated: 2025/08/29 17:33:30 by miwehbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

/*static int	process_digit_and_check(long long *num, char digit, int sign)
{
	long long	prev_num;

	prev_num = *num;
	*num = *num * 10 + (digit - '0');
	if ((*num / 10 != prev_num) || (sign == 1 && *num < 0) ||
			(sign == -1 && *num > 0 && (-*num) == 0))
				return (0);
	return (1);
}

static int	check_numeric_overflow(const char *str)
{
	int			pos;
	int			sign;
	long long	num;

	pos = 0;
	sign = 1;
	num = 0;
	if (str[pos] == '-' || str[pos] == '+')
		pos++;
	if (pos != 0 && str[pos - 1] == '-')
		sign = -1;
	while (str[pos])
	{
		if (!ft_isdigit(str[pos]))
			return (0);
		if (!process_digit_and_check(&num, str[pos], sign))
			return (0);
		pos++;
	}
	return (1);
}

static void	process_exit_argument(t_cmd *cmd, t_shell *shell, int arg_count)
{
	long long	exit_code;

	if (!ft_is_numeric(cmd->args[1]) || !check_numeric_overflow(cmd->args[1]))
	{
		ft_putendl_fd("minishell: exit: numeric argument required", 2);
		shell->exit_status = 255;
		exit(shell->exit_status);
	}
	if (arg_count > 2)
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		shell->exit_status = 1;
		return ;
	}
	exit_code = ft_atoll(cmd->args[1]);
	shell->exit_status = (unsigned char)exit_code;
}

void	builtin_exit(t_cmd *cmd, t_shell *shell)
{
	int	arg_count;

	ft_putendl_fd("exit", 1);
	arg_count = ft_size_of_arr(cmd->args);
	if (arg_count >= 2)
	{
		process_exit_argument(cmd, shell, arg_count);
		if (shell->exit_status == 1)
			return ;
	}
	else
		shell->exit_status = 0;
	exit(shell->exit_status);
}*/

static int	process_digit_and_check(long long *num, char digit, int sign)
{
	long long	prev_num;

	prev_num = *num;
	*num = *num * 10 + (digit - '0');
	if ((*num / 10 != prev_num) || (sign == 1 && *num < 0) ||
			(sign == -1 && *num > 0 && (-*num) == 0))
				return (0);
	return (1);
}

static int	check_numeric_overflow(const char *str)
{
	int			pos;
	int			sign;
	long long	num;

	pos = 0;
	sign = 1;
	num = 0;
	if (str[pos] == '-' || str[pos] == '+')
		pos++;
	if (pos != 0 && str[pos - 1] == '-')
		sign = -1;
	while (str[pos])
	{
		if (!ft_isdigit(str[pos]))
			return (0);
		if (!process_digit_and_check(&num, str[pos], sign))
			return (0);
		pos++;
	}
	return (1);
}

static void	process_exit_argument(t_cmd *cmd, t_shell *shell, int arg_count)
{
	long long	exit_code;

	if (!ft_is_numeric(cmd->args[1]) || !check_numeric_overflow(cmd->args[1]))
	{
		ft_putendl_fd("minishell: exit: numeric argument required", 2);
		shell->exit_status = 255;
		//shell->exit = true;
		return;
	}
	if (arg_count > 2)
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		shell->exit_status = 1;
		return ;
	}
	exit_code = ft_atoll(cmd->args[1]);
	shell->exit_status = (unsigned char)exit_code;
	shell->exit = true; 
}

void	builtin_exit(t_cmd *cmd, t_shell *shell)
{
	int	arg_count;

	ft_putendl_fd("exit", 1);
	arg_count = ft_size_of_arr(cmd->args);
	if (arg_count >= 2)
	{
		process_exit_argument(cmd, shell, arg_count);
		/*if (shell->exit_status == 1)
			return ;*/
	}
	else
	{
		shell->exit_status = 0;
		shell->exit = true;
	}
}