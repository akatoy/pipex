#include "../inc/pipex.h"

//void	ft_error(int error, char *name);                    // Ecrit les différents messages d'erreur
void    ft_read(char **av, char **envp, int *fd);           // Lit le infile (enfant)
void    ft_write(char **av, char **envp, int *fd);          // Ecrit dans outfile (parent)
void	ft_exec(char *av, char **envp, int files);          // Cherche la commande dans pathname
void	ft_exec2(char **paths, char **cmd, char **envp);
void	ft_message(char *av, int files);

int main(int ac, char **av, char **envp)
{
    pid_t   pid; 
    int   fd[2];                                           
    
    if (ac != 5)                                             // Erreur de nombre d'argument(s)
 //       ft_error(1);
        write(2, "Error : [file1] [cmd1] [cmd2] [file2].\n", 40);
    if (pipe(fd) == -1)
		return (2);
    pid = fork();                                              // Création d'une famille avec Fork*
    if (pid < 0)                                             // Erreur à la création du Fork
        write(2, "Error : error while 'forking'.\n", 32);
    if (pid == 0)                                            // Creation Fork PID enfant pour lire
        ft_read(av, envp, fd);
    waitpid(pid, NULL, 0);
    if (pid != 0)                                            // Ecrire dans parent
        ft_write(av, envp, fd);
    return(0);
}

//void	ft_error(int error, char *name)                      // Error messages 
//{
//	if (error == 1)
//		write(2, "Error : [file1] [cmd1] [cmd2] [file2].", 39);
//	else if (error == 2)
//        write(2, "Error : error while 'forking'.", 22);
//	else if (error == 3)
//       write(2, "Error : cannot read.", 21);
//    else if (error == 4)
//        write(2, "Error : cannot write.", 22);
//    else if (error == 5)
//       write(2, "Error : command not found.", 28);
//	exit(error);
//}

void	ft_exec(char *av, char **envp, int files)
{
	char	**paths;
	int		i;
	char	**cmd;

	cmd = ft_split(av, ' ');
	execve(cmd[0], cmd, NULL);
	i = 0;
	paths = NULL;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5))
			paths = ft_split(envp[i] + 5, ':');
		i++;
	}
	if (paths == NULL)
	{
        write(2, "Error : command not found.\n", 29);
		return ;
	}
	ft_exec2(paths, cmd, envp);
	ft_message(av, files);
}

void	ft_exec2(char **paths, char **cmd, char **envp)
{
	int		i;
	char	*part_path;
	char	*path;
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, *cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
			execve(path, cmd, envp);
		i++;
	}
	free(path);
}

void    ft_read(char **av, char **envp, int *fd)
{
    int file1;                                               // Fd entrant / infile

    file1 = open(av[1], O_RDONLY);                           // Ouvre et lit le file entrant
    if (file1 < 0)
 //       ft_error(3);
        write(2, "Error : cannot read.\n", 22);
    dup2(fd[1], STDOUT_FILENO);                              // Transforme newfd en une copie de oldfd, fermant newfd si nécessaire.
	close(fd[1]);
    if (dup2(file1, STDIN_FILENO) == -1)
	{
		close(fd[0]);
		close(file1);
		return ;
	}
	close(fd[0]);
	close(file1);
    ft_exec(av[2], envp, file1);
}

void    ft_write(char **av, char **envp, int *fd)
{
    int file2;                                               //Fd de sortie / outfile

    file2 = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0777);   //Ouvre et creer/ecrit + modifie les droits du file de sortie
    if (file2 < 0)
 //       ft_error(4);
        write(2, "Error : cannot write.\n", 23);
    dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	if (dup2(file2, STDOUT_FILENO) == -1)
	{
		close(fd[1]);
		close(file2);
		return ;
	}
	close(fd[1]);
	close(file2);
    ft_exec(av[3], envp, file2);
}

void	ft_message(char *av, int files)
{
	if (files != -1)
	{
		write (2, av, ft_strlen(av));
		write (2, ": command not found.\n", 22);
	}
	return ;
}

//*PID : Identifiant du Processeur.
//*FD : File Descriptor.
//*Fork : Appel systeme creant un processeur enfant (copie du parent).
//*Open : Appel ou ouvre le fichier specifie dans 'pathname'.
//*Close : Ferme le fichier donné.
//*O_ : -O_RDONLY* : Open for reading only.
//      -O_CREAT : Create if nonexistant.
//      -O_RDWR : Open for reading and writing.
//      -O_TRUNC : Truncate for 0 legth.