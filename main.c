/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 10:14:12 by aumoreno          #+#    #+#             */
/*   Updated: 2025/01/20 12:35:36 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int ft_check_file_permissions(char *infile, char *outfile)
{
    if (access(infile, R_OK) == -1)
        return (-1);
    else if (access(outfile, W_OK) == -1) // should add check for reading permission ?
        return (-1);
    return (0);
}

char *ft_find_path(char **envp)
{
    // char *full_path; // malloc?
    int i;

    i = 0;
    while (envp[i])
    {
        if (ft_strncmp(envp[i], "PATH=", 5) == 0)
            return (&envp[i][5]);
        i++;
    }
    return (0);
}

void ft_show_path_checking(char **path)
{
    int i = 0;
    
    // Check if the path array is not NULL
    if (path == NULL)
    {
        printf("Path is NULL\n");
        return;
    }

    // Loop through each path and print it
    while (path[i] != NULL)
    {
        printf("Path[%d]: %s\n", i, path[i]);
        i++;
    }
}

// ESTO IMPORTANTE HACER UN MÉTODO QUE CHECK EL PATH DEL COMANDO porq si no no simepre se guardan en el mismo sitio
int ft_check_bin(char *cmd1, char *cmd2, char **envp)
{
    char **path;
    char *path_cmd1;
    char *path_cmd2;
    int i;
    // IMPORTANTE SEPARAR LOS PROGRAMAS DEL RESTO DE SUS ARGS

    // el valor de path lo vamos a recuperar directamente de envp[] del PATH variable
    path = ft_split(ft_find_path(envp), ':');
    ft_show_path_checking(path);
    if(!path)
        return(-1);
    
    // path es un arry que tiene todos los paths posibles donde se encuentran los ejecutables 
    // por tanto vamos a iterar los paths + cmd1 para checkar si existen y si son exe 
    // haremos los mismo con cmd2
    /*PROBABLY WILL END UP CREATING A NEW FUNCTION*/
    path_cmd1 = NULL;
    i = 0; 
    while(path[i])
    {
        path_cmd1 = ft_strjoin(path[i], cmd1);
        if (access(path_cmd1, F_OK) == -1 || access(path_cmd1, X_OK) == -1)
            break;
        free(path_cmd1);
        path_cmd1 = NULL;
        i++;
    }
    if(!path_cmd1)
        return(-1);
    
    // we do the same with cmd2
    path_cmd2 = NULL;
    i = 0; 
    while(path[i])
    {
        path_cmd2 = ft_strjoin(path[i], cmd2);
        if (access(path_cmd2, F_OK) == -1 || access(path_cmd2, X_OK) == -1)
            break;
        free(path_cmd2);
        path_cmd2 = NULL;
        i++;
    }
    if(!path_cmd2)
        return(-1);
    
    // free: path, path_cmd1, path_cdm2
    i = 0;
    while(path[i])
        free(path[i++]);
    free(path); // bc puntero movidas
    
    free(path_cmd1);
    free(path_cmd2);

    return (0);
}

int main(int argc, char **argv, char **envp)
{

    char **cmd1;
    char **cmd2;
    int i;

    // check que argc no pasa de 5
    if (argc == 5)
    {
        printf("There is 5 args. Let's begin\n");
        /*change ifs for elif*/

        // creo que no hace falta
        // // check que estén en el orden correcto (infile cmd1 cmd2 outfile) no sé cómo hacer esto lolete
        // if (ft_check_args_order(argv) == -1)
        // {
        //     // los args no están en el orden correcto
        //     ft_error("Args not in order\n");
        // }
        // check que el segundo argv sea un path a un fichero y que el ultimo (5) tmb (que existan)
        if (access(argv[1], F_OK) == -1 || access(argv[4], F_OK) == -1) // USE ACCESS METHOD FOR THIS ONE
        {
            // F_OK flag: Used to check for the existence of a file.
            ft_error("Path does not exist in file system.\n");
        }
        printf("El fichero existe.\n");
        // check permisos de archivos !!! (no sé como hacer esto) // use access for this one too
        if (ft_check_file_permissions(argv[1], argv[4]) == -1) // USE ACCESS METHOD FOR THIS ONE: check
        {
            /*
                F_OK flag: Used to check for the existence of a file.
                R_OK flag: Used to check for read permission bit.
                W_OK flag: Used to check for write permission bit.
            */
            ft_error("Check file permissions.\n");
        }
        printf("Tiene los permisos necesarios.\n");
        // guardar en cmd 1 y cmd 2 los args que sean comandos: 3 y 4 para luego checkarlos
        // ls -l SOLO COGER ls
        cmd1 = ft_split(argv[2], ' ');
        cmd2 = ft_split(argv[3], ' ');
        // check binario del comando existe (creo que sé pero no estoy segura)
        if (ft_check_bin(cmd1[0], cmd2[0], envp) == -1) // use access too??
        {
            /*
                F_OK flag: Used to check for the existence of a file.
                R_OK flag: Used to check for read permission bit.
                W_OK flag: Used to check for write permission bit.
                X_OK flag: Used to check for execute permission bit.
            */
            ft_error("Bin does not exist or does not have the right permissions\n");
        }
        printf("EL binario existe y tiene los permisos necesarios.\n");

        // una vez todos estos checks ya programa en sí
        ft_printf("todo guay, lets pipe\n");
        // empezariamos con crear el pipe y el primer hijo

        // el infile => dup del stdin? + infile para fd intercambiable. CREO QUE NO HACE FALTA porq lo lee del fichero no sé es raro jeje
        // habria que pasarlo al execve como arg normal, no hace falta dup para este primero

        // luego ya el resto normal (ver otros dos mains), creamos forks para pasar el output del cmd1 omo input al cmd2

        // finalmente ver main file process para pintar el output de cmd2 al fichero outfile

        // hacemos los frees colegaa que si no da tremendo leakkkk HCER MÉTODO
            if(cmd1)
            {
                i = 0;
                while (cmd1[i])
                {
                    free(cmd1[i]);
                    i++;
                }
                free(cmd1);
            }

            if(cmd2)
            {
                i = 0;
                while (cmd2[i])
                {
                    free(cmd2[i]);
                    i++;
                }
                free(cmd2);
            }

    }
    else
    {
        // de momento va a ser un simple exit error pero mirar como gestionarlo
        exit(EXIT_FAILURE);
    }

    return (0);
}