#ifndef MINISHELL_H
# define MINISHELL_H
# include "struct.h"
# include "libft.h"

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/errno.h>
# include <errno.h>
# include <dirent.h>
# ifdef LINUX
#  include <linux/errno.h>
# endif

/* ------------------------------------------------------------------------- */

/*
** Just for printf debug
*/
# define LINE(NAME) "\n=====================-"#NAME"-=======================\n"
# define LINE2 "-----------------\n"

/*
** Macros
*/
# define MAX_FD 25

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

/*
** builtin code magic numbers
*/
# define BT_ECHO 1
# define BT_PWD 2
# define BT_EXIT 3
# define BT_CD 4
# define BT_EXPORT 5
# define BT_UNSET 6
# define BT_ENV 7

/*
** tokenizer error magic numbers
*/
# define UTOKEN_OR 1
# define UTOKEN_P 2
# define UTOKEN_SC 3
# define UTOKEN_ML 4

/*
** tokenizer error message
*/
# define E_UTOKEN_OR "OR not handled"
# define E_UTOKEN_P "|"
# define E_UTOKEN_SC ";;"
# define E_UTOKEN_ML "multiline not handled"

/*
** Return code
*/
# define RT_FAIL -1
# define RT_SUCCESS 0
# define RT_EXIT 1

/*
** Environment control
** These defines shorten literals to make the code more understandable.
** NAME is of type t_list.
*/
# define ENV_KEY(NAME) ((t_env *)((NAME)->content))->key
# define ENV_VALUE(NAME) ((t_env *)((NAME)->content))->value

# define CMD(NAME) ((t_command *)((NAME)->content))->command
# define CMD_FD(NAME) ((t_command *)((NAME)->content))->fd

# define COMMAND(NAME) (t_command *)((NAME)->content)

/*
** Global variables
*/
int	g_line_eraser;
int	g_exit_status;

/* ------------------------------------------------------------------------- */

/*
** These functions will create/add/find/delete/free a list of the t_env struct,
** from the envp (char **ep) argument of the main.
*/
t_list		*create_env_list(char **envp);
char		**env_list_to_tab(t_list *head);
void		add_env_variable(t_list **head, char *var);
char		*find_env_value(t_list **head, char *key);
void		delete_env_variable(t_list **head, char *key);
void		free_env(void *env, size_t size);
int			update_underscore(t_list **env, char *path_cmd);
char		*last_arg(t_command *cmd);

/* ------------------------------------------------------------------------- */

/*
** Loop functions
*/
int			main_loop(t_list **env, t_list **export, int *err);
int			gnl_ctrld(int fd, char **line);

/*
** Loop error
*/
int			empty_line(char *line);
int			token_error_manager(int err);
void		print_token_error(char *str);
int			return_to_main(t_list **env, char *line, int ret_gnl);

/*
** Lexer/parser function that will buid t_command structure
** These functions will create a list of t_command from the input line.
*/
t_list		*tokenizer(char *line, int *err);
int			pipeline_n_link(t_list **head, char *execution_line, int *err);
int			expander(t_list **env, t_command *i_command);
char		*skip_char(char *str, char c);

/*
** tokenize split
*/
char		**split_with_exception(char *str, char c, char *exception_set);
char		*ghosting(char *str, char c, char *exception_set, int *error);

/*
** tokenize quotes
*/
char		*expand_filename(t_list **env, char **line_ptr);
char		*quotes(t_list **env, char **line_ptr);
char		*double_quotes(t_list **env, char **line_ptr);
char		*simple_quotes(char **line_ptr);
char		*no_quotes(t_list **env, char **line_ptr);
int			redirections(t_list **env, char **line_ptr, t_command *i_command);
int			expand_doll_quote(t_list **env, char **str,
								char **final_str, char quote);
char		*doll_expand(t_list **env, char **line_ptr, char quote);

/*
** tokenize error handling
*/
void		*tokenize_error_sc(t_list **head, char **array);
int			tokenize_error_pipe(t_list **head, char **pipeline,
								int i, int fd_tmp);
int			parse_token_error(char **str, int i, int *err);

/*
** tokenize quotes utils
*/
int			join_str_before(char **str, char **line_ptr, char **final_str);
int			join_char_to_str(char **final_str, char c);
int			escape_it(char **final_str, char **str, char **line_ptr);

/*
** tokenize utils
*/
void		delete_remaining_char(char *str, char c);
char		*end_of_object(char *str);
int			is_symbol(int c);
int			is_symbol_doll(int c);
int			is_symbol_v2(int c);
int			authorized_char(int c);
int			is_special_char(int c);
char		*skip_char(char *str, char c);
t_command	*init_command(char *pipeline);
int			ft_count_tab(char **tab);
char		**alpha_order_array(char **export_tab);

void	print_cmd(t_command *cmd);/////////delete
void	print_array(char **arr);/////////delete

/*
** clear lists
*/
void		clear_commandlist(void *content);
void		clear_envlist(void *content);
void		clear_arglist(void *content);
int			clear_lists_exit(t_list **cmd, t_list **env);
void		ft_array_string_del(char **array);
//void		free_command_list(t_list **cmd); is that one the clear_commandlist?

/* ------------------------------------------------------------------------- */

/*
** This function will find if the command is a builtin and execute it, or
** execute said command with execve.
*/
int			execute_command(t_list **env, t_command *cmd, t_list **export);
void		close_fd(int *fd);
void		dup_fd(int *fd);

//tests
int			exec_t(t_list **env, t_command *cmd, char **arr_env);
void		clean_fd_n_wait(int *fd, int cpid);
void		dup_it(int *fd);

/*
** Builtins
*/
int			echo_builtin(t_list **env, t_command *cmd);
int			pwd_builtin(t_list **env, t_command *cmd);

int			exit_builtin(t_command *cmd);
int			exit_arg(t_command *cmd, size_t i);

int			cd_builtin(t_list **env, t_command *cmd);
int			update_pwd(t_list **env);
char		*cd_args(t_list **env, char *arg, t_command *cmd);


int			export_builtin(t_list **env, t_command *cmd, t_list **export);
int			export_builtin_arg(t_list **env, t_list **export, t_command *cmd);
void		print_export(char **export_tab);
void		update_export_underscore(t_list **env, t_command *cmd);

int			unset_builtin(t_list **env, t_command *cmd, t_list **export);
int			env_builtin(t_list **env, t_command *cmd);

/*
** Executable external functions
*/

int			execute_builtin(t_list **env, t_command *cmd, int builtin_code,
							t_list **export);
int			is_builtin(t_command *cmd);
int			execute_extern(t_list **env, t_command *cmd);
int			fork_extern(t_command *cmd, char *path_to_cmd, char **env_tab);
int			parent_process(pid_t pid, char *pathcmd, char **env_tab);
char		*path_to_executable(t_list **env, t_command *cmd);
char		*absolute_path(t_command *cmd, char *home_path);
char		*relative_path(t_command *cmd, char **split_path);
int			test_cmd(char *env_path, char *executable);
char		*add_path_to_cmd(char *abs_path, char *executable);

/* ------------------------------------------------------------------------- */

/*
** errors/signal handlins/exits functions
*/
void		error_msg(char *bash, t_command *cmd, char *arg, char *err_msg);
int			error_msg_2(char *bash, t_command *cmd, char *arg, char *err_msg);
void		ctrl_back_slash_handler(int signal);
void		ctrl_back_slash_handler_quit(int signal);
void		ctrl_c_handler(int sign);
//void		set_line_eraser(int sign);

/* ------------------------------------------------------------------------- */

#endif
