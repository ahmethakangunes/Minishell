/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exportenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agunes <agunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 17:46:36 by agunes            #+#    #+#             */
/*   Updated: 2022/08/16 00:36:21 by agunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*exportedit3(char *export)
{
	int		i;
	char	*buff;

	i = 0;
	buff = NULL;
	if (!ft_strncmp(export, "SHELL=", 6))
	{
		while (g_shell->env[i])
			i++;
		free(export);
		export = ft_strdup("SHELL=");
		buff = g_shell->env[i - 1] + \
		findfirstindex(g_shell->env[i - 1], '=') + 1;
		export = ft_strjoin(export, buff);
		return (export);
	}
	return (export);
}

char	*exportedit2(char *export)
{
	char	*temp;

	temp = NULL;
	export = exportedit3(export);
	if (!ft_strncmp(export, "OLDPWD=", 7))
	{
		free(export);
		export = ft_strdup("OLDPWD");
		return (export);
	}
	else
	{
		if (equalcheck(export))
		{
			temp = export;
			export = addquote(export, 0);
			free(temp);
			return (export);
		}
	}
	return (export);
}

void	exportedit(char **export)
{
	int		i;
	int		x;
	char	*temp;

	i = 0;
	x = 0;
	while (export[i])
	{
		x = 0;
		while (export[x + 1])
		{
			if (export[x + 1][0] >= 65 && export[x + 1][0] <= 90)
			{
				if (export[x][0] > export[x + 1][0])
				{
					temp = export[x];
					export[x] = export[x + 1];
					export[x + 1] = temp;
				}
			}
			x++;
		}
		i++;
	}
}

void	exportenvcpy(char **env)
{
	int		i;
	char	*buff;

	i = -1;
	buff = merge(env, 1);
	g_shell->env = ft_split(buff, ' ');
	g_shell->export = ft_split(buff, ' ');
	while (g_shell->export[++i])
		g_shell->export[i] = exportedit2(g_shell->export[i]);
	free(g_shell->export[i - 1]);
	g_shell->export[i - 1] = NULL;
	free(buff);
}