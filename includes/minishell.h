/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derey <derey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:24:38 by maxouvra          #+#    #+#             */
/*   Updated: 2024/08/09 15:18:47 by derey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <signal.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <errno.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/ioctl.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

typedef enum e_token
{
	TOKEN_SIMPLE_QUOTE,
	TOKEN_DOUBLE_QUOTES,
	TOKEN_REDIRECT_INPUT,
	TOKEN_REDIRECT_OUTPUT,
	TOKEN_DELIMITER,
	TOKEN_APPEND,
	TOKEN_PIPE,
	TOKEN_VARIABLE,
	TOKEN_STATUS_LAST_PIPE,
	TOKEN_BACKSLASH,
	TOKEN_SEMICOLON,
	TOKEN_BUILTIN,
	TOKEN_EXPAND,
	TOKEN_ARGS,
}	t_token_type;

typedef struct s_exp
{
	int		squot;
	int		dquot;
	int		expan;
	int		len;
	int		idx;
	int		idx_tab;
	int		space;
	int		pipe;
	int		x;
	int		q;
	char	*tmp_exp;
	char	*word_env;
	char	*end_str;
	char	*exp;
}t_exp;


typedef struct s_token
{
	const char		*symbol;

	t_token_type	type;
}t_token;

typedef struct s_lexer_tab
{
	int					index;
	int					len;
	char				*arg;
	int					infile;
	int					outfile;
	t_token_type		type;
	struct s_lexer_tab	*next;
}	t_lexer_tab;

typedef struct s_input
{
	char	*input;
	char	*path;
	char	**all_tokens;
}	t_input;

typedef struct s_pipe
{
    pid_t 	pid;
    int 	fdin;
    int 	fdout;
    int		saved_fdout;
	int		saved_fdin;
	char	*fdin_str;
} t_pipe;

typedef struct s_init
{
	char	**cpy_env;
	char	actual_dir[128];
	char	*pathearly;
	int		exit_code;
	int		on;
	struct sigaction sig;
	struct sigaction ignore;
}	t_init;

typedef struct s_execute
{
	int		n_pipe;
	int		i;
	int		last_exit_status;
	int		pipefd[2];
}	t_execute;

/*=====================cmd_cd.c======================*/
void			cmd_cd(t_input *line, int i, t_init *init_shell);
void			cd_end(char	*oldpwd, char *result, t_init *init_shell);

/*=====================cmd_env.c=====================*/
void			cmd_env(t_init *init_shell, int fd);

/*=====================cmd_pwd.c=====================*/
void			cmd_pwd(void);

/*=====================cmd_exit.c====================*/
void			cmd_exit(t_input *line, int i, t_init *init_shell);

/*=====================cmd_unset.c===================*/
void			cmd_unset(char **list, int idx, t_init *init_shell);

/*=====================cmd_export.c==================*/
void			cmd_export(char **list, int idx, t_init *init_shell);

/*=====================cmd_export_2.c================*/
void			print_export(t_init *init_shell);

/*=====================cmd_export_3.c================*/
void			print_solo(int a, t_init *init_shell);
int				print_var(char *s, int fd, int i, char c);
void			print_ex(char *result);
char			*ft_find_export(const char *big, const char *little, char find);

/*=====================cmd_echo.c====================*/
void	cmd_echo(char **list, int i, int fd,  t_init *init_shell);

/*=====================proces.c======================*/
void	proces(t_input *line, int fd, t_init *init_shell, int o);
int		check_process(t_lexer_tab **tab_lexer, t_execute *process, t_input *line);

/*=====================error.c=======================*/
void			print_error(char *str);
int				error_cd(t_input *line, int i,  t_init *init_shell);
void			error_expand(t_init *init_shell);

/*=====================ft_printf.c===================*/
int				ft_printf(const char *s, ...);

/*=====================ft_printf_utils.c=============*/
int				ft_putstr_i(char *s);
int				ft_putchar_i(char c);
int				ft_putnbr_i(int nb);
int				ft_putnbr_u(unsigned int nb);

/*=====================ft_printf.c===================*/
int				ft_printf_error(const char *s, ...);

/*=====================ft_printf_utils.c=============*/
int				ft_putstr_i_error(char *s);
int				ft_putchar_i_error(char c);
int				ft_putnbr_i_error(int nb);
int				ft_putnbr_u_error(unsigned int nb);

/*=====================init.c========================*/
void			ft_init(t_init *init_shell, t_execute *process, char **env);
void			init_exp(t_exp *expa, t_input *line);

/*=====================lexer.c=======================*/
void			append_node(t_lexer_tab **tab_lexer, t_input *line, int i);
t_token_type	ft_lexer(char *current_token);
t_lexer_tab		*get_last_node(t_lexer_tab *node);
t_lexer_tab		*ft_new_node(int i, t_input *line);
t_lexer_tab		*create_lexer_tab(t_lexer_tab *tab_lexer, t_input *line, int i);
void			stack_add_back(t_lexer_tab **tab_lexer, t_lexer_tab *new);

/*=====================minishell.c===================*/
int				open_file(char *file, int in_or_out);
char			*check_rights(char *cmd, char **env);
void			ft_free_path(char **all_paths);
void			exec_cmd(char **args, t_input *line, t_init *init_shell);
void			pipeline_execute(t_input *line, t_execute *process, t_init *init_shell, t_lexer_tab *tab_lexer);
void			ft_free(char **all_paths);
void			path_early(t_init *init_shell);
char			**get_command_args(t_input *line, t_lexer_tab **lexer_tab, t_pipe *pipes, int n_process);
int				set_file(t_execute *process, t_pipe *pipes, t_lexer_tab *current, t_init *init_shell);
void			pipe_init(t_execute *process, t_pipe *pipes);
void			child_process(t_pipe *pipes, t_execute *process, int i);
void			parent_process(t_pipe *pipes, t_execute *process, t_init *init_shell);
void			set_pipe_fd(t_pipe *pipes, t_execute *process, int i);
void			close_all_fds(t_pipe *pipes, t_execute *process);
int				acces_dirnocd(char *result, t_init *init_shell);

/*=====================utils.c=======================*/
char			*ft_find_str(const char *big, const char *little, char find);
int				ft_strstr(const char *big, const char little, int i);
int				ft_strcmp(const char *s1, const char *s2);
void			ft_free_next_line(t_lexer_tab *lexer_tab, t_input *line);
void			ft_split_expand(char const *s, t_exp *expa, t_input *line);
int				try_close(int fd);

/*=====================utils_str.c===================*/
int				ft_strexit(char *str);
int				ft_strlen_list(char **s);
int				ft_strlenback(char *str);
int				ft_strlenlen(char *str, int x);
int				ft_strlen_exp(char *str, char c);

/*=====================utils_expand.c================*/
char			*print_expend(const char *s, int c);
char			*ft_expcpy(char *str, char c, int z);
char			*ft_joinlen(char const *s1, char const *s2, int a);

/*=====================expand.c======================*/
void			ft_expand(t_input *line, t_init *init_shell);

int				end_word(char c);
void			text_exp(t_exp *expa, t_init *init_shell, t_input *line, int a);
void			word_expand(t_exp *expa, t_input *line);

void			handle_signal(int signa);

char		*ft_str_unset(const char *big, const char *little);
void	modif_env(t_init *init_shell, char *str);
int	verif_export(char *str, t_init *init_shell);
void	realloc_env(t_init *init_shell, char *str, int i);
void	change_env(char *oldpwd, char *pwd, t_init *init_shell);
int				find_homes(t_init *init_shell);
void	ft_split_expand(char const *s, t_exp *expa, t_input *line);

int	verif_str(char *str);

void	quot_exp(t_exp *expa, t_input *line);

void	squot_verif(t_exp *expa);
void	dquot_verif(t_exp *expa);
void	space_verif(t_exp *expa);
void	ft_idxexp(char const *s, t_exp *expa, int i);
char	*ft_substr_exp(char const *s, unsigned int start, size_t len);
void	append_node(t_lexer_tab **tab_lexer, t_input *line, int i);


#endif
