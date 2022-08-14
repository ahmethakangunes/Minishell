/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cdutils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agunes <agunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 19:55:59 by agunes            #+#    #+#             */
/*   Updated: 2022/08/14 23:04:15 by agunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	cdcheck(char *command)
{
	char	*buff;

	buff = ft_strdup("minishell: cd: ");
	buff = ft_strjoin(buff, command);
	buff = ft_strjoin(buff, ": ");
	if (access(command, F_OK) == -1)
	{
		buff = ft_strjoin(buff, strerror(errno));
		write(2, buff, ft_strlen(buff));
		write(1, "\n", 1);
		free(buff);
		return (0);
	}
	else if (chdir(command) == -1)
	{
		buff = ft_strjoin(buff, strerror(errno));
		write(2, buff, ft_strlen(buff));
		write(1, "\n", 1);
		free(buff);
		return (0);
	}
	free(buff);
	return (1);
}

void	notset(int status)
{
	char	*buff;

	buff = NULL;
	if (status == 1)
	{
		buff = ft_strdup("HOME NOT SET");
		write(2, buff, ft_strlen(buff));
		write(1, "\n", 1);
		free(buff);
	}
	if (status == 2)
	{
		buff = ft_strdup("minishell: cd: OLDPWD not set");
		write(2, buff, ft_strlen(buff));
		write(1, "\n", 1);
		free(buff);
	}
}

void	exportpwdupdate(char *new, char *old)
{
	char	*buff;

	buff = NULL;
	if (!exportsearch("PWD="))
	{
		buff = ft_strdup("PWD=");
		buff = ft_strjoin(buff, new);
		exportupdate(buff);
		free(buff);
	}
	if (!exportsearch("OLDPWD="))
	{
		buff = ft_strdup("OLDPWD=");
		buff = ft_strjoin(buff, old);
		exportupdate(buff);
		free(buff);
	}
}

void	envpwdupdate(char *new, char *old)
{
	char	*buff;

	buff = NULL;
	exportpwdupdate(new, old);
	if (!envsearch("PWD="))
	{
		buff = ft_strdup("PWD=");
		buff = ft_strjoin(buff, new);
		envupdate(buff);
		free(buff);
	}
	if (!envsearch("OLDPWD="))
	{
		buff = ft_strdup("OLDPWD=");
		buff = ft_strjoin(buff, old);
		envupdate(buff);
		free(buff);
	}
}