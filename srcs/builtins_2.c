#include "minishell.h"

int		pwd_builtin(t_list **env, t_list **cmd)
{
	char	*stored;

	(void)env;
	stored = getcwd(NULL, 0);
	ft_putstr_fd(stored, CMD_FD(*cmd)[1]);
	ft_putchar_fd('\n', CMD_FD(*cmd)[1]);
	free(stored);
	return (0);
}

/* if expand_tilde detects the ~ sign, it search the HOME env variable
 * and join to it the path which can be typed behind, then return a malloc()
 * pointer to this string. The string given as paramater is free.
 * Otherwise, no tilde had been detected as first character, & it returns
 * the string given as parameter, untouched.
*/
char	*expand_tilde(t_list **env, char *arg)
{
	char	*expanded;
	char	*env_home;
	int		i;

	i = 0;
	if (arg[i++] != '~')
		return (arg);
	env_home = find_env_value(env, "HOME");
	if (!(expanded = ft_strjoin(env_home, &arg[i])))
		return (NULL);
	free(arg);
	return (expanded);
}

/* cd uses the chdir func to sail into the filesystem & set errors.
 * This builtin must specifically change the OLDPWD & the PWD variables; and
 * handle the tilde char as well as the 'no' char, which means HOME directory.
*/
int		cd_builtin(t_list **env, t_list **cmd)
{
	char    *tmp;
	char    *pwd;
	char    *old_pwd;

	if (!(CMD(*cmd)[1]))
		CMD(*cmd)[1] = ft_strjoin("~", "");
	else if (!(CMD(*cmd)[1][0]))
		return (0);
	CMD(*cmd)[1] = expand_tilde(env, CMD(*cmd)[1]);
	if ((chdir(CMD(*cmd)[1])) == -1)
	{
		tmp = strerror(errno);
		write(2, "bash: cd: ", 11);
		write(2, CMD(*cmd)[1], ft_strlen(CMD(*cmd)[1]));
		write(2, ": ", 3);
		write(2, tmp, ft_strlen(tmp));
		write(2, "\n", 2);
		return (-1);
	}
	old_pwd = find_env_value(env, "PWD");
	tmp = ft_strjoin("OLDPWD=", old_pwd);
	add_env_variable(env, tmp);
	free(tmp);
	pwd = getcwd(NULL, 0);
	tmp = ft_strjoin("PWD=", pwd);
	add_env_variable(env, tmp);
	free(tmp);
	free(pwd);
	return (0);
}

int		exit_arg(t_list **cmd, size_t i)
{
	int	errnb;

	errnb = 0;
	if (i == ft_strlen(CMD(*cmd)[1]))
	{
		if (!CMD(*cmd)[2])
		{
			errno = ft_atoi(CMD(*cmd)[1]);
			errno += 256;
			errno %= 256;
			exit(errno);
		}
		else if (CMD(*cmd)[2])
		{
			errnb = 1;
			error_msg_bash(cmd, errnb, "too many arguments\n");
			return (errnb);// or 131?
		}
	}
	return (0);
}

/* exit <nb less than long long>
 * output: exit\n
 * echo $? = if nb > 255 < longlong, it starts over again to count from 0 to 255
 *
 * exit <any string or number bigger than a long long>
 * output: exit\nbash: exit: <argv>: numeric argument required\n
 * echo $? = 2
 *
 * exit <str or nb less than long long> <str or nb less than long long>
 * output: exit\nbash: exit: too many arguments\n
 * IT DOES EXIT THE SHELL
 * echo $? = 1
 *
 * If <argv> is omitted, the exit status is that of the last command executed.
 */
int		exit_builtin(t_list **env, t_list **cmd)
{
	size_t	i;
	int	errnb;

	(void)env;
	errnb = 0;
	i = 0;
	ft_putstr_fd("exit\n", 2);
	if (CMD(*cmd)[1] == NULL)
		exit(0);
	else if (CMD(*cmd)[1])
	{
		if (CMD(*cmd)[1][0] == '+' || CMD(*cmd)[1][0] == '-')
			i++;
		while (ft_isdigit((char)CMD(*cmd)[1][i]) == 1)
			i++;
		if (i != ft_strlen(CMD(*cmd)[1]))
		{
			errnb = 2;
			error_msg_bash(cmd, errnb, CMD(*cmd)[1]);
			ft_putstr_fd(": numeric argument required\n", CMD_FD(*cmd)[2]);
			exit(errnb);
		}
		exit_arg(cmd, i);
	}
	return (0);
}
