/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beroy <beroy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:44:03 by beroy             #+#    #+#             */
/*   Updated: 2024/05/13 17:18:25 by beroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct s_env	t_env;
typedef struct s_redir	t_redir;
typedef struct s_cmd	t_cmd;
typedef struct s_head	t_head;

// init.c

t_head	*head_init(char **env);

// init_utils.c

int		find_equal(char *str);
t_redir	*ft_redir_new(char *line, int start, int end, int type);
t_redir	*ft_redirlast(t_redir *lst);
void	ft_rediradd_back(t_redir **lst, t_redir *new);

// parser.c

int		quote_skip(char *input, int *i, char find);
int		ft_parse(char *input, t_head *head);

// parser_utils.c

t_cmd	*ft_cmd_new(char *input);
t_cmd	*ft_cmdlast(t_cmd *lst);
void	ft_cmdadd_back(t_cmd **lst, t_cmd *new);
void	index_up(char *input, int *i);
void	find_pipe(char *input, int *i);

// parser_utils_2.c

int 	char_is_ws(char c);
char	**split_ws_quote(char *input);
int		split_ws(t_cmd *cmd);

// parser_utils_3.c

void	tab_display(char **tab);
int 	space_redir(t_cmd *cmd);

// format.c

int		format(t_head *head);
int		format_redir(t_cmd *cmd);

// format_utils.c

int 	redir_type(char *line, int i);
int		find_redir(char *line);
int		extract_redir(t_cmd *cmd);
#endif