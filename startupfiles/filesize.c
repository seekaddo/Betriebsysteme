#define _GNU_SOURCE

/**
 * @file filezise.c
 * Betriebssysteme filesize finder File.
 * Beispiel 0
 *
 * @author Dennis Kwame Addo <ic16b026@technikum-wien.at>
 * @date 2017/02/05
 *
 * @version 1.0
 *
 * @todo read the metadata of the file pass in (flags)
 * @todo print the size of the file in bytes
 * @todo if the parameter length is less than 2 return error.
 *
 */

/*
 * -------------------------------------------------------------- includes --
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>


/*
 * --------------------------------------------------------------- defines --
 */

/*
 * -------------------------------------------------------------- typedefs --
 */

/*
 * --------------------------------------------------------------- globals --
 */

/*
 * ------------------------------------------------------------- functions --
 */

/**
 *
 * \brief The most minimalistic C program
 *
 * This is the main entry point for any C program.
 *
 * \param argc the number of arguments
 * \param argv the arguments itselves (including the program name in argv[0])
 *
 * \return always "success"
 * \retval 0 always
 *
 */
int main(int argc , const char *argv[])
{
   struct stat sb;
   int retv;
   
   if(argc <= 1){
   	fprintf(stderr,"usage: %s <file> \n",argv[0]);
	return 1;
   }

   retv = stat(argv[1],&sb);

   if(retv){
   	perror("reading stats error");
	return 1;
   }

   printf("The file: %s is %ld\n",basename(argv[1]),sb.st_size);


    return 0;
}

/*
 * =================================================================== eof ==
 */
