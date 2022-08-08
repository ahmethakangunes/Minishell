/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agunes <agunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 12:53:45 by agunes            #+#    #+#             */
/*   Updated: 2022/08/08 17:36:19 by agunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	ft_cd(char *command)
{
	int		i;
	char	*old;
	char	*new;

	i = 0;
	if (!command)
	{
		old = getcwd(NULL, 0);
		chdir(getenv("HOME"));
		new = getcwd(NULL, 0);
		envupdate(new, old);
	}
	else
	{
		if (access(command, F_OK) == -1)
		{
			printf("cd: no such file or directory: %s\n", command);
			return (1);
		}
		old = getcwd(NULL, 0);
		if (chdir(command) == -1)
			printf("cd: permission denied: %s\n", command);
		new = getcwd(NULL, 0);
		envupdate(new, old);
	}
	return (1);
}

void	envupdate(char *new, char *old)
{
	int		i;

	i = 0;
	while (g_shell->env[i])
	{
		if (!ft_strncmp(g_shell->env[i], "PWD", 3))
		{
			free(g_shell->env[i]);
			g_shell->env[i] = ft_strdup("PWD=");
			g_shell->env[i] = ft_strjoin(g_shell->env[i], new);
		}
		if (!ft_strncmp(g_shell->env[i], "OLDPWD", 5))
		{
			free(g_shell->env[i]);
			g_shell->env[i] = ft_strdup("OLDPWD=");
			g_shell->env[i] = ft_strjoin(g_shell->env[i], old);
		}
		i++;
	}
	free(new);
	free(old);
}
