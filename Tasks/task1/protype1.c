//
// Created by seekaddo on 2/10/17.
//


/**
 * @file prototype1.c
 *
 * Beispiel 0
 *
 * @author Dennis Addo <ic16b026@technikum-wien.at>
 * @date 01/02/2017
 *
 * @version 0.1
 *
 * @todo Get the file permission in the form of a string (-rwxrwxrwx)
 * @todo get the file type for the first permission position
 * @todo Display the file permission for a given file
 *
 *
 */

/*
 * -------------------------------------------------------------- includes --
 */
#include <stdio.h>
#include <sys/stat.h>
#include <malloc.h>
#include <memory.h>
#include <grp.h>
#include <pwd.h>
#include <time.h>


/*
 * --------------------------------------------------------------- defines --
 */
#define STR_SIZE sizeof("?rwxrwxrwx")
#define LEN 12

/*
 * -------------------------------------------------------------- typedefs --
 */

/*
 * --------------------------------------------------------------- globals --
 */

/*
 * ------------------------------------------------------------- functions --
 * */
char *filePermTostring(mode_t perm);
char getFtype( mode_t m);
void print_ls(const struct stat sb);


/**
  *
  * \brief This Programm displays the permission of a file
  *
  * \param argc the number of arguments
  * \param argv the arguments itselves (including the program name in argv[0])
  *
  * \return always "success"
  * \retval 0 always
  *
  */
int main(int argc, char *argv[]) {

    int ret;
    struct stat sb;
    struct group *gp;
    struct passwd *pd;

    if(argc <= 2){
        fprintf(stderr,"usage: %s -option <file-path>\n",argv[0]);
        return 1;
    }
    if(!argv[2]){
        fprintf(stderr,"%s\nusage: %s -option <file-path>\n","Missing file-path",argv[0]);
        return 1;
    }

    ret = stat(argv[2],&sb);
    if(ret){
        perror("stat processing error");
    }

    //TODO: get owner name and group name from the passed file
    gp = getgrgid(sb.st_gid);
    pd = getpwuid(sb.st_uid);

    size_t len = strlen(ctime(&sb.st_mtim.tv_sec)) -1;
    char *fpstr = filePermTostring(sb.st_mode);

    /*-rwxr-xr-x. 1 root root 3756 Feb  5 20:18 filename.extension*/
    printf("%s %ld %s %s %lld %.*s %s\n",
                     fpstr, sb.st_nlink,
                     pd->pw_name, gp->gr_name, (long long)sb.st_size,
                     (int)(len -4),ctime(&sb.st_mtim.tv_sec),argv[2]);


    free(fpstr);

    return 0;

}

/* emulating the -l in the linux command ls -l
 * putting everything in the main function here as one method.
 * */
void print_ls(const struct stat sb){

}




/*Return a char denoting the various linux file types
 * returns '?' when not found
 * */
char getFtype(mode_t mode){

    switch (mode & S_IFMT){
        case S_IFREG:
            return '-';
        case S_IFDIR:
            return 'd';
        case S_IFBLK:
            return 'b';
        case S_IFCHR:
            return 'c';
        case S_IFIFO:
            return 'p';
        case S_IFLNK:
            return 'l';
        case S_IFSOCK:
            return 's';
        default:
            return '?';
    }
}
/* get the permission for a passed mode
 * as for now only normal permissions rwx,
 * sticky bits and SUID and GUID will come later
 * don't forget to free it.
 * \retrun a null-terminated string
 * */
char *filePermTostring(mode_t perm){
    char *permstr = malloc(sizeof(char)*LEN);

    snprintf(permstr,STR_SIZE, "%c%c%c%c%c%c%c%c%c%c",(getFtype(perm)), (perm & S_IRUSR) ? 'r' : '-',
                    (perm & S_IWUSR) ? 'w':'-',(perm & S_ISUID)?'x':'-',
                    (perm && S_IRGRP)?'r':'-',(perm & S_IWGRP)?'w':'-',(perm & S_ISGID)?'x':'-',
                    (perm & S_IROTH)?'r':'-',(perm & S_IWOTH)?'w':'-',(perm & S_ISVTX)?'x':'-');

    permstr[LEN-1] = '\0';
    return permstr;

}
