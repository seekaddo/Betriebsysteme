#define _GNU_SOURCE
/**
 * @file main.c
 *
 * Beispiel 0
 *
 * @author Dennis Addo <ic16b026@technikum-wien.at>
 * @date 01/02/2017
 *
 * @version 01
 *
 * @todo setting a permission on file
 * @todo the permission mode is in octal number in a string.
 * @todo convert from string to base 8 and pass it to chmod
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
#include <stdlib.h>
#include <errno.h>


/*
 * --------------------------------------------------------------- defines --
 */

#define RU (S_IRUSR)
#define WU (S_IWUSR)
#define XU (S_IXUSR)
#define RWXUR (S_IRWXU)

#define RG (S_IRGRP)
#define WG (S_IWGRP)
#define XG (S_IXGRP)
#define RWXGR (S_IRWXG)

#define RO (S_IROTH)
#define WO (S_IWOTH)
#define XO (S_IXOTH)
#define RWXOT (S_IRWXO)

/*
 * -------------------------------------------------------------- typedefs --
 */

/*
 * --------------------------------------------------------------- globals --
 */

/*
 * ------------------------------------------------------------- functions --
 * */
/*int c_chmod(char *path, char *mode);
mode_t getMode(char t,char m);*/

 /**
   *
   * \brief The most minimalistic C program to chmod()
   *
   * This programm changes user permission on files
   * \return 0 on success otherwise -1
   *
   *
   * \param argc the number of arguments
   * \param argv the arguments itselves (including the program name in argv[0])
   *
   *
   */

int main(int argc, char *argv[]) {

     int ret;

     if(argc <= 2){
         fprintf(stderr,"usage: %s [mode] <file-path>\n",argv[0]);
         return 1;
     }

     char *modes = strcpy(malloc(sizeof(char) * 6),argv[1]);
     modes[strlen(modes)+1] = '\0';


     /*get the right permission in mode_t with & 07777
      * cast it to mode_t
      * convert the mode to mode_t with strtol in base 8(octal) atoi atol not allowed
      * delimeter for strtol is NULL*/
     ret = chmod(argv[2],(mode_t)strtol(argv[1],NULL,8));

     if(ret){
         int ern = errno;
         fprintf(stderr,"%s: error in chmod(%s, %s) - %d (%s)\n",
         basename(argv[0]),basename(argv[0]),modes,ern,strerror(ern));
     };


    return 0;

}

/*change the permission of a file.
 * path is the file to be modified
 * mode is the array of the permission in the hex form [600]...
 * return 1 on success and -1 on fail.
 * */
/*int c_chmod(char *path, char *mode){
    //char *modes = getMode(&mode);
    int i = 0;
    int ret = -1;
    char t = 'u';
    while(i < 3){

        ret = chmod(path,getMode(t,*(mode+i)));
        if(ret) perror("chmod error");

        i++;
    }
    return ret;
}
*//*return an array of chars for the modes
 * positions for 0. user 1. group 2. other [600] with no*sticky-bits in mind*
 * 4 read
 * 2 write
 * 1 execute
 * *//*

mode_t getMode(char type,char m){

        if(m > 7) {
            fprintf(stdin,"Wrong mode %c",m);
            return 000;
        }

        switch (type){
            case 'u':
                if(m == 4){
                    return RU;
                } else if(m == 2){
                    return WU;
                } else if (m ==1){
                    return XU;
                } else if (m == 6){
                    return RWXUR;
                } else{
                    return 000;
                }
            case 'o':
                if(m == 4){
                    return RO;
                } else if(m == 2){
                    return WO;
                } else if (m ==1){
                    return XO;
                } else if (m == 6){
                    return RWXOT;
                } else{
                    return 000;
                }
            case 'g':
                if(m == '4'){
                    return RG;
                } else if(m == '2'){
                    return WG;
                } else if (m =='1'){
                    return XG;
                } else if (m == '6'){
                    return (RG | WG);
                } else{
                    return 000;
                }

            default:
                break;

        }

    return 000;

}*/
