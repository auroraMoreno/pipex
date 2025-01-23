/*file only used to modify a method to make it more abstract
    once the method is done, delete file
*/

#include "pipex.h"

/*esta es la definiciób*/

/*
    queremos que el check bin devuelva la ruta, osea devuelva un string 
    luego en el main se lo asignamos al array cmd_paths 
    hacemos el if con cada cmd_paths[0] y [1] 
    si tiene NULL dentro lanzamos error de que no encuentra el path 
    si no pues todo igual. 
*/

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
    ft_free_cmds(path);
    // NO TOQUES
    //free(path_cmd); // este free ya no lo tengo que hacer porq se convierte en cmd_paths[0] y [1] y de eso ya hago el free en el main
    return (path_cmd);
}
