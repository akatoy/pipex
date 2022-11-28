#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include <string.h>

//void	ft_error(int error, char *name);
void    ft_message(char *av, int files);
void    ft_read(char **av, char **envp, int *fd);
void    ft_write(char **av, char **envp, int *fd);
void	ft_exec(char *av, char **envp, int files);
void	ft_exec2(char **paths, char **cmd, char **envp);

char        *ft_strnstr(const char *haystack, const char *needle, size_t len);
char	    *ft_strjoin(const char *s1, const char *s2);
int	        ft_strlen(const char *s);
char	    **ft_split(char const *s, char c);


#endif
