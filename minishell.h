/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agunes <agunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 11:41:06 by agunes            #+#    #+#             */
/*   Updated: 2022/08/11 18:35:15 by agunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include "builtin/builtin.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <signal.h>
# include <string.h>
# include <fcntl.h>
# include <signal.h>

typedef struct s_token
{
	char	**path;
	char	**arglist;
	char	**command;
	int		*fd;
	int		*fd1;
	int		pr_lstfreeflag;
}		t_token;

typedef struct s_shell
{
	char		**commandlist;
	char		**env;
	char		**export;
	char		**path;
	char		*command;
	char		*prompt;
	int			echoflag;
	int			pipe_flag;
	int			envflag;
	int			exportflag;
	int			**pipes;
	int			*pids;
	t_token		*program;
}		t_shell;

t_shell	*g_shell;

t_token	*create_tokens(char *commandlist);
char	**spltnorm(char *command, int i, int k, int j);
char	**splt2norm(char *command, int i, int k, int j);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_prompt(void);
char	*merge(char **command);
void	ft_parser(void);
void	runcommand(char *arr);
void	ft_path(char *arr);
void	ft_free(void);
void	create_pipes(t_token *program);
void	run_pipes(void);
void	ft_signal(void);
void	ft_searchfor(char *arr);
void	dbfree(char **arr);
void	exportupdate(char *commandlist);
int		ft_commandsearch(void);
int		ft_strcmp(char *arr, char *arr1);
int		ft_builtinsearch_pipe(char *arr);
int		dblen(char **array);
int		dblen2(char **array);
#endif
