/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_process_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 12:14:57 by aumoreno          #+#    #+#             */
/*   Updated: 2025/01/21 09:43:48 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

#define READ_END 0
#define WRITE_END 1

#define FILE_NAME "file.txt" // donde vamos a escribir el output final, el archivo debe existir!! en el mismo directorio que estamos exe el program

int main(int argc, char **argv, char **envp)
{

    // printf("%d\n", argc);

    // printf("Command-line arguments:\n");
    // for (int i = 0; i < argc; i++)
    // {
    //     printf("Argument %d: %s\n", i, argv[i]);
    // }

    // printf("Environment variables:\n");
    // for (int i = 0; envp[i] != NULL; i++)
    // {
    //     printf("Variable %d: %s\n", i, envp[i]);
    // }
    // return 0;

    int fd1[2];
    int fd2;
    int status; // para realizar el wait que hace el padre para cada uno de los hijos (repasar video fork y wait)
    int pid;    // id del proceso de los hijos

    pipe(fd1); // creará el pipe q comunica ls y wc y devolverá el array con los fd correspondientes

    /*
        el padre ha creado el pipe con los extremos de lect y escr abiertos
        los hijos los heredan abiertos tmb por eso es importante cerrar los que no necesitamos
    */

    /*HIJO 1: ls -l*/
    pid = fork();

    // si pid = 0 significa que se está ejecutando el hijo

    if (pid == 0)
    {
        close(fd1[READ_END]);

        dup2(fd1[WRITE_END], STDOUT_FILENO); // para que cuando el programa quiera escribir en el fd de STDOUT esté escribiendo en el extremo de escritura del pipe
        close(fd1[WRITE_END]);

        execlp("/bin/ls", "ls", "-l", NULL);
    }
    else /*PADRE*/
    {
        // ahora como ya no vamos a usar más el extremo de escritura del pipe lo cerramos
        close(fd1[WRITE_END]);

        pid = fork();

        /*hijo 2: wc Y escriba el resultado en el archivo file.txt*/

        if (pid == 0)
        {
            // el hijo va a heredar el extremo de lectura del pipe (el padre ha cerrado el de escritura)

            // vamos a abrir el archivo file.txt y asi conseguir su fd y es donde vamos a escribir las cosas al final
            fd2 = open(FILE_NAME, O_WRONLY);
            // lo que salga como salida de ls en el extremo de lectura del pipe tiene que escribirse en el STDIN:
            dup2(fd1[READ_END], STDIN_FILENO);
            close(fd1[READ_END]);

            // por defecto el wc escribe su salida en el stdout y queremos que escriba en el file.txt
            // entonces vamos a usar el dup para que lo que salga en el stdout se escriba en el fd del file.txt
            dup2(fd2, STDOUT_FILENO);

            execlp("/usr/bin/wc", "wc", NULL);
        }
        else /*PADRE*/
        {
            close(fd1[READ_END]); // ya no hace falta
        }
    }

    wait(&status);
    wait(&status);

    return (0);
}