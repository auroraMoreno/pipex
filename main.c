/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 18:32:56 by aumoreno          #+#    #+#             */
/*   Updated: 2025/01/16 15:17:00 by aumoreno         ###   ########.fr       */
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
    if(pid == 0)
    {
        //primero cierro el extremo de lectura
        close(fd1[READ_END]);
        
        // ahora usamos el métdo dup2() para que lo que el ls escriba en el stdout se escriba también en el pipe
        // stdout_fileno va a ser un duplicado de write_end
        dup2(fd1[WRITE_END], STDOUT_FILENO); // STDOUT_FILENO is an int value defined in unistd.h. It's a file descriptor of LINUX system. (en el método write es el primer arg que es 1)
        //como stdout va a ser el fd que escriba en el fd[write_end] del pipe, no neceito el originar fd[write_end] entonces lo cierro!! 
        close(fd1[WRITE_END]);
        
        // con esta función se va a llamar al comando ls 
        // con u
        //execlp("");
        
    }
    

    
    
    return(0);
}