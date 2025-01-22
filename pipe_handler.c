/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 10:35:56 by aumoreno          #+#    #+#             */
/*   Updated: 2025/01/22 17:51:08 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
#define READ_END 0
#define WRITE_END 1
*/

// we need the first command for this (i.e: ls -l)
// in argv we have the commands to execute so we can get them from there.
void ft_handle_child(int* fd, char** argv, char* cmd_path, char** envp) //vamos a suponer que full_path está bien y luego haré el metodo para arreglarlo bien 
{
    ft_printf("Printing path:%s\n", cmd_path); // está printing un path to raro porq la memoria está haciendo lo que quiere
    // quizá si hago el metodo abstracto i can actually re use it for the checking 
    int infile_fd;
    char** cmd1; 
    char* infile_path = argv[1]; // esto quizás lo sustituyo
    int i; // esta var la quitaré porq haré un método 

    cmd1 = ft_split(argv[2], ' '); // cmd1 ls -l //u could add a check if u wanted but is gonna check it in execve 
    // cmd1[0] => ls
    // cmd1[1] => -l
    
    close(fd[READ_END]); //creo
    /*usamos el fd del fichero*/
    infile_fd = open(infile_path,O_RDONLY);
    /*error check*/
    if(infile_fd == -1)
        ft_error("Error in opening infile.");
    
    /*reemplazamos el fd del stdin por el fd del fichero*/
    dup2(infile_fd,STDIN_FILENO);
    close(infile_fd);

    /*
        el segundo proceso tiene que usar como input el output del primer proceso
        por defecto, el output se pone en el stdout 
        entonces tenemos que decir que "no se escriba en el stdout", si no que todo lo que se escriba
        en el stdout se escriba tmb en el extremo de escritura del pipe
    */

   //hay que hacer el dup antes de que se ejecute porq despues ya no sirve para nada, ya ha salido por el stdout
    dup2(fd[WRITE_END], STDOUT_FILENO);
    close(fd[WRITE_END]);

    if(execve(cmd_path, cmd1, envp) < 0)
        ft_error("Error in the child process exec.");

    // free el cmd1 bc ft_split
    if(cmd1)
    {
        i = 0;
        while(cmd1[i])
            free(cmd1[i++]);
        free(cmd1);
    }
}

// grep tiene que coger el input del output de ls -l, how do i do that lmao 
// using dup2 cambiar el output STDOUT por el extremo de escritura ? i guess ?? 
// donde lo pongo? 

// cmd2 i.e.: wc -l
void ft_handle_parent(int* fd, char** argv, char* cmd_path, char** envp)
{
    int outfile_fd; 
    char** cmd2;
    char* outfile_path;
    int pid; // cambiar por pid_t
    int i;
    
    outfile_path = argv[4];
    cmd2 = ft_split(argv[3], ' ');

    
    /* segundo proceso: "wc -l"*/
    pid = fork();
    close(fd[WRITE_END]); // ahora solo tengo que leer pero a lo mejor lo tengo que dejar abierto bc tengo que escribir en el fichero pero creo que no
    
    if(pid == -1)
    {
        ft_error("Error in second process fork.");
    }
    else if (pid == 0)
    {
        outfile_fd = open(outfile_path, O_WRONLY | O_APPEND | O_TRUNC);
        //check for errors
        if(outfile_fd == -1)
            ft_error("Error in opening the outfile.");
        /*hijo*/
        // el input lo tiene q sacar del extremo de lectura del pipe 
        dup2(fd[READ_END],STDIN_FILENO);
        close(fd[READ_END]);
        // el resultado del segundo proceso lo tienes q poner en el outfile y no en el stdout
        // vamos a hacer el dup 
        dup2(outfile_fd, STDOUT_FILENO);

        //exe el proceso
        if(execve(cmd_path, cmd2, envp) < 0)
            ft_error("Error in exe the second."); //REVISAR COMO SE TRATAN LOS ERRORES!!!

        if(cmd2){
            i = 0;
            while(cmd2[i])
                free(cmd2[i++]);
            free(cmd2);
        }
    }        
    else
        /*padre*/     
        //cerraremos lo que no haga falta ya
        close(fd[READ_END]);
}


int ft_creating_processes(char** argv, char** envp, char **cmd_paths)
{
    ft_printf("Comencemos con la creación.\n");
    int fd1[2]; // para el hijo CAMBIARLE EL NOMBRE AL FD1
    //int fd2[2]; // para el padre si solo hay un pipe no me hace falta porq uso el fd1
    int status;
    int pid; //change to pid_t
     //cambiar esto por un método que me devuelva el path en concreto de dónde se están sacando los exe (hacerlo en path_utils )

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
        // 0 => cmd1; 1 => cmd2
        ft_handle_child(fd1, argv, cmd_paths[0], envp);   
    }
    else 
    {
        /*padre*/
        // 0 => cmd1; 1 => cmd2

        ft_handle_parent(fd1, argv, cmd_paths[1], envp);    
    }

    /*hacemos los wait de los hijos*/
    waitpid(pid,&status, WNOHANG);
    waitpid(pid,&status, WNOHANG);

    return(status);
}