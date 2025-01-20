/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 18:32:56 by aumoreno          #+#    #+#             */
/*   Updated: 2025/01/17 10:58:52 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*para ver más includes mirar en pipex.h*/

/*
esto servirá para en el array index del pipe saber cual cerrar si el lectura (read_end) o escritura (write_end)
sin necesidad de acordarse de los indices.
revisarme el método pipe
*/
#define READ_END 0
#define WRITE_END 1 

int main(void)
{
    int fd1[2]; // para el pipe 1 (comunica ls -l con grep u)
    int fd2[2]; // para el pipe 2 (comunica grep u con wc -l)
    int status; // para el estado de los procesos hijos
    int pid; // para el id de proceso de los hijos
    
    // creamos el proceso padre
    pipe(fd1); // para comunicar ls y grep 

    // creo el hijo 1
    pid = fork(); // hereda el fd del padre (del pipe(fd1)), 
     
    // hijo 1 que va a heredar el fd del padre, es decir => van a estar abierto el de lectura y el de escritura (solo necesitamos el de escritura)
    /**
     * hijo = 0
     * error = -1
     * otro num = padre 
     */
    if(pid == 0) /*hijo*/
    {
        //primero cierro el extremo de lectura
        close(fd1[READ_END]);
        
        // ahora usamos el métdo dup2() para que lo que el ls escriba en el stdout se escriba también en el pipe
        // stdout_fileno va a ser un duplicado de write_end
        dup2(fd1[WRITE_END], STDOUT_FILENO); // STDOUT_FILENO is an int value defined in unistd.h. It's a file descriptor of LINUX system. (en el método write es el primer arg que es 1)
        //como stdout va a ser el fd que escriba en el fd[write_end] del pipe, no neceito el originar fd[write_end] entonces lo cierro!! 
        close(fd1[WRITE_END]);
        
        // con esta función se va a llamar al comando ls 
        // con esta funcion vamos a llamar al programa ls, 
        // indicarle donde está el programa, luego qué ejecutar y por último un argumento como tal
        execlp("/bin/ls","ls", "-l", NULL); // importante acabar en NULL para que sepa cuando se acaban los args
        
    }
    else /*padre*/
    {
        // cerramos el extremo de escritura porq lo va a heredar abierto 
        close(fd1[WRITE_END]); // preguntar por qué aqui lo va a heredar abierto
        
        //hacemos el pipe que comunica grep y wc 
        pipe(fd2);
        pid = fork(); // este (el segundo hijo) va a ser el proceso que va a lanzar el grep u 

        if(pid == 0) // hijo 2
        {
            /**
             * grep va a usar del pipe 1 el extremo de lectura 
             * y del pipe 1 el extremo de escritura
             * esto es porq para el stdin grep necesita LEER del pipe 1 el output de ls 
             * y para el pipe 2 necesita ESCRIBIR el resultado (output) del grep u en el pipe 2
             * por eso cerramos los que no necesitemos
             */

            // vamos a cerrar el extremo de lectura del pipe 2 
            // cerramos el de lectura porq necesitamos que coja lo que venga en stdout y lo ESCRIBA en el pipe 2, en el fd del pipe 2 
            close(fd2[READ_END]);
            
            // hacemos un duplicado porq queremos que grep lea del extremo de lectura del pipe 
            // por tanto decimos que ahora el stdin va a recibir contenido del extremo de lectura del pipe 1 (del output del pipe 1 por asi decirlo ahora es el input de grep )
            dup2(fd1[READ_END],STDIN_FILENO);
            //cerramos el extremo de escriutra del pipe 1 porq ya hemos hecho el duplicado
            close(fd1[READ_END]);
            
            // el extremo de escritura del pipe 2 va a ser el output de grep
            dup2(fd2[WRITE_END], STDOUT_FILENO);
            close(fd2[WRITE_END]); // de nuevo, cerramos porq ya tenenmos hecho el duplicado

            // ejectumos de nuevo el programa
            execlp("/bin/grep", "grep", "u", NULL);
        }else /*EL PADRE*/
        {
          // una serie de cosas que ya no necesita
          // ni el padre ni los hijos sucesivos
         /*
            ya no necesita el read end del pipe 1(fd1) porq eso ya se ha quedao atras
            tampoco necesita el wrtie end del pipe 2 (fd2) porq ya el ultimo proceso (wc -l) solo va a 
            tener que LEER el output del pipe 2 
         */ 
            close(fd1[READ_END]);
            close(fd2[WRITE_END]);

            /*HIJO 3*/
            // este es el hijo para el wc -l
            
            pid = fork();

            if(pid == 0)
            {
                // por defecto lee del standard input y lo que queremos es que lea del pipe 2
                // el "output" del pipe sea el input del wc 
                dup2(fd2[READ_END], STDIN_FILENO);
                close(fd2[READ_END]);

                execlp("/usr/bin/wc", "wc", "-l", NULL);
                
            }
             
        }
        
        
    }
    
    close(fd2[READ_END]); // extremo de lectura del pipe 2 que se quedó abierto en el padre
    
    // ahora hacemos wait para cada hijo
    wait(&status);
    wait(&status);
    wait(&status);
    
    return(0);
}