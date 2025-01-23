/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 10:14:12 by aumoreno          #+#    #+#             */
/*   Updated: 2025/01/23 12:28:45 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int ft_check_file_permissions(char *infile, char *outfile)
{
    if (access(infile, R_OK) == -1)
        return (-1);
    if (access(outfile, W_OK) == -1) // should add check for reading permission ?
        return (-1);
    return (0);
}

// cambiar esto a otro fichero que no quede tan pegote 
char *ft_find_path_variable(char **envp)
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

    //Loop through each path and print it
    while (path[i] != NULL)
    {
        printf("Path[%d]: %s\n", i, path[i]);
        i++;
    }
}
char *ft_format_path(char *path, char *cmd)
{
    char *formatted_path;
    char *aux;

    // si el fichero es un simple exe
    //kk de esto que hay que cambiar pero ya hoy paso, esq cuando salga de este metodo 
    //va a literlamente hacer el mismo check que estoy haciendo aqui abajo 
    //lolete 

    aux = ft_strjoin(path, "/");
    formatted_path = ft_strjoin(aux, cmd);
    free(aux);
    return (formatted_path);
    
}

char *ft_check_bin(char *cmd, char **envp)
{
    char **path; //for the PATH var full route
    char *path_cmd;
    int i;
    // IMPORTANTE SEPARAR LOS PROGRAMAS DEL RESTO DE SUS ARGS
    //ft_printf("Printing cmd1: %s\n", cmd2);
    // el valor de path lo vamos a recuperar directamente de envp[] del PATH variable
    path = ft_split(ft_find_path_variable(envp), ':');
    //ft_show_path_checking(path);
    if(!path)
        return(0);
    
    // path es un arry que tiene todos los paths posibles donde se encuentran los ejecutables 
    // por tanto vamos a iterar los paths + cmd1 para checkar si existen y si son exe 
    // haremos los mismo con cmd2
    /*PROBABLY WILL END UP CREATING A NEW FUNCTION*/
    if(access(cmd, F_OK) == 0 && access(cmd, X_OK) == 0)
    {
        // si es sin más un ejecutable pues sin mas devolvemos el puntero
        // no hay problema de aloc y de leaks porq estoy haciendo aloc en split y free en main 
        return (cmd);
    }
    
    path_cmd = NULL;
    i = 0; 
    while(path[i])
    {
        //path_cmd1 = ft_strjoin(path[i], cmd1);
        path_cmd = ft_format_path(path[i], cmd); // esto tecnicamente devuelve el path asi: routa_larga/comando
        ft_printf("Printing joined path prior to checking: %s\n", path_cmd);
        if (access(path_cmd, F_OK) == 0 && access(path_cmd, X_OK) == 0) 
            break; // cambiamos esto a que devuelva el path del cmd algo asi: si f_ok y x_ok == 0 entonces no break but return * y podemos dejar abajo que en vez de devulva devuelva 0 
            // O QUE DEVULVA DIRECT SABES?? o sea en main en vez de hacer un if con ft_check_bin asignamos al cmd direct y luego un if que diga si cmd_direct == 0 lanzamos error (we'll see)
        free(path_cmd);
        path_cmd = NULL;
        i++;
    }
    ft_printf("Printing joined path: %s\n", path_cmd);
    if(!path_cmd)
    {
        ft_free_cmds(path);   
        return(0);
    }    
    ft_free_cmds(path); // we could free this first then do the path_cmd check
    // NO TOQUES
    //free(path_cmd); // este free ya no lo tengo que hacer porq se convierte en cmd_paths[0] y [1] y de eso ya hago el free en el main
    return (path_cmd);
}


int main(int argc, char **argv, char **envp)
{

    char **cmd1;
    char **cmd2;
    char **cmd_paths; // 0 => cmd1; 1 => cmd2
    // int i; // esta variable se va a ir igualmente porq es para el free asi que eso lo haremos en un método a parte 

    // check que argc no pasa de 5
    // revisar tema orden de los argumentos 
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
        cmd1 = ft_split(argv[2], ' '); // aqui estoy haciendo los alocs 
        cmd2 = ft_split(argv[3], ' ');


        /*vamos a recuperar los paths de los comando con la full route de donde está su fichero bin*/
        /*luego modificaremos para que no haya tantas llamadas a funciones q podriamos modfiicar para reusarlas o hacer 
        todo del tiron en el check bin*/
        cmd_paths = ft_calloc(sizeof(char *), 2);
        // aquí en vez de llamar a cmd_paths, vamos a usar directamente ft_check_bin
        cmd_paths[0] = ft_check_bin(cmd1[0], envp); //cmd1 
        ft_printf("Printing FINAL CMD1: %s\n", cmd_paths[0]);

        cmd_paths[1] = ft_check_bin(cmd2[0],envp);//cmd2
        ft_printf("Printing FINAL CMD2: %s\n", cmd_paths[1]);

        // check binario del comando existe (creo que sé pero no estoy segura)
        // si devulve 0 esq el puntero viene null de todas formas esto lo tengo que cambiar un poco más pero para no olvidarme
        if (cmd_paths[0] == 0 || cmd_paths[1] == 0) // use access too??
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
        ft_creating_processes(argv, envp, cmd_paths);
        // el infile => dup del stdin? + infile para fd intercambiable. CREO QUE NO HACE FALTA porq lo lee del fichero no sé es raro jeje
        // habria que pasarlo al execve como arg normal, no hace falta dup para este primero

        // luego ya el resto normal (ver otros dos mains), creamos forks para pasar el output del cmd1 omo input al cmd2

        // finalmente ver main file process para pintar el output de cmd2 al fichero outfile

        // hacemos los frees colegaa que si no da tremendo leakkkk
        ft_free_cmds(cmd1);
        ft_free_cmds(cmd2);
        // NO TOQUES creo que esto lo tengo q usar asi porque estoy usando calloc y no malloc 
        // maybe i can change this to ft_free_cmds;
        free(cmd_paths[0]);
        free(cmd_paths[1]);
        free(cmd_paths);
    }
    else
    {
        // de momento va a ser un simple exit error pero mirar como gestionarlo
        //exit(EXIT_FAILURE);
        ft_error("Check the given arguments.");
    }

    return (0);
}