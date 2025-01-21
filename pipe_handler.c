/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 10:35:56 by aumoreno          #+#    #+#             */
/*   Updated: 2025/01/21 17:45:50 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
#define READ_END 0
#define WRITE_END 1
*/

void ft_handle_child(int* fd, char** argv, char* full_path) //vamos a suponer que full_path está bien y luego haré el metodo para arreglarlo bien 
{
    // quizá si hago el metodo abstracto i can actually re use it for the checking 
    int infile_fd;
    char** cmd1;
    char* infile_path = argv[1]; // esto quizás los sustituyo
    char* exec_args[] = {full_path, cmd1[1], NULL};
    
    close(fd[READ_END]); //creo
    /*reemplazamos el fd del stdin por el fd del fichero*/
    infile_fd = open(infile_path,O_RDONLY);
    /*error check*/
    if(infile_fd == -1)
        ft_error("Error in opening infile.");
    
    dup2(infile_fd,STDIN_FILENO);
    close(infile_fd);
    
    //exec_args = 
    execve(full_path,); 
    
}


void ft_creating_processes(char** argv, char** envp)
{
    int fd1[2]; // para el hijo
    int fd2[2]; // para el padre
    int status;
    int pid; 
    char *full_path = ft_find_path(envp); //cambiar esto por un método que me devuelva el path en concreto de dónde se están sacando los exe (hacerlo en path_utils )

    /*creamos el pipe*/
    if(pipe(fd1) == -1)
        ft_error("Error creating pipe.");
    
    /*Primer hijo: ls -l*/
    pid = fork();
    
    if(pid == -1)
        /*error*/
        ft_error("Error creating the child.");
    else if(pid == 0)
    {
        /*hijo*/
        ft_handle_child(fd1, argv, full_path);   
    }
    else 
    {
        /*padre*/
        ft_handle_parent();    
    }

    /*hacemos los wait de los hijos*/
    waitpid(pid,&status, WNOHANG);
    waitpid(pid,&status, WNOHANG);
}