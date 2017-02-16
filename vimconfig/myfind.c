//
// Created by seekaddo on 2/16/17.
//


/**
 * @file myfind.c
 *
 * Beispiel 0
 *
 * @author Dennis Addo <ic16b026@technikum-wien.at>
 * @author Robert Niedermeyar <ic16b089@technikum-wien.at>
 * @date 15/02/2017
 *
 * @version 0.1
 *
 * @todo
 * @todo
 * @todo
 *
 *
 */

/*
 * -------------------------------------------------------------- includes --
 */

#include <stdio.h>
#include <sys/stat.h>

/*
 * --------------------------------------------------------------- defines --
 */

/*
 * -------------------------------------------------------------- typedefs --
 */

typedef struct _params{
    char *spath;
    int help;
    int print;
    char f_type;
    int ls;
    char *user;
    unsigned long usr_id;
    char *name;

}parms;

/*
 * --------------------------------------------------------------- globals --
 */

/*
 * ------------------------------------------------------------- functions --
 * */

void print_help(void);
do_file(const char * file_name, const char * const * parms);
do_dir(const char * dir_name, const char * const * parms);
char *get_smlink(char file_path, const struct stat attr);
void do_ls(const struct stat atrr);





/**
  *
  * \brief This is a clone of the GNU find command in pure c
  *
  *
  *
  * \param argc the number of arguments
  * \param argv the arguments itselves (including the program name in argv[0])
  *
  * \return always "success"
  * \retval 0 always
  *
  */


int maint (int argc, char *argv[]){


    printf("I");

    return 0;
}


void print_help(void){
    printf("Usage: myfind <file or directory> [ <options> ] ...\n"
                   "default path is the current directory if none is specified; default expression is -print\n"
                   "Options: (You can specify any of the following options)\n"
                   "       : -help                   Shows all necessary informations for this command\n"
                   "       : -user <name>/<uid>     file or directory belongig to specified user\n"
                   "       : -name <pattern>        file or directory with specified name\n"
                   "       : -type [bcdpfls]        All entry with specified file type\n"
                   "       : -print                 print entries with the path\n"
                   "       : -ls                    print entries with more details\n"
                   "");

}


