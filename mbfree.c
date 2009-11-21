/* mbfree -- possibly free up some system memory
**
** Copyright © 2000, 2001 Jeremy Brand <jeremy@nirvani.net>.
** http://www.jeremybrand.com/Jeremy/Brand/Jeremy_Brand.html
**
** Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions
** are met:
** 1. Redistributions of source code must retain the above copyright
**    notice, this list of conditions and the following disclaimer.
** 2. Redistributions in binary form must reproduce the above copyright
**    notice, this list of conditions and the following disclaimer in the
**    documentation and/or other materials provided with the distribution.
**
** THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
** ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
** IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
** ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
** FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
** DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
** OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
** HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
** LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
** OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
** SUCH DAMAGE.
*/


#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#define EXIT exit(EXIT_FAILURE)

static char *argv0=NULL;

void usage(void);
void missing_arg(void);
void bad_arg(char*);
void help(void);
void version(void);
void footer(void);
void license(void);
unsigned parse_arg(char**, int*);

int main (int argc, char** argv)
{
  int argn = 1;
  unsigned bytes = 0;
  int tmp;

  argv0 = argv[0];

  if (argc == 1)
  {
    usage();
    EXIT;
  }

  if (argv[argn][0] == '-') 
  {
    while (argn < argc)
    {
      if (strcmp(argv[argn], "-b") == 0 || 
          strncmp(argv[argn], "--bytes", 7) == 0)
      {
        bytes += parse_arg(argv, &argn);
      }
      else if (strcmp(argv[argn], "-k") == 0 || 
               strncmp(argv[argn], "--kilobytes", 11) == 0)
      {
        tmp = parse_arg(argv, &argn);
        bytes += (1024*tmp);
      }
      else if (strcmp(argv[argn], "-m") == 0 || 
               strncmp(argv[argn], "--megabytes", 11) == 0)
      {
        tmp = parse_arg(argv, &argn);
        bytes += (1024*1024*tmp);
      }
      else if (strcmp(argv[argn], "-g") == 0 || 
               strncmp(argv[argn], "--gigabytes", 11) == 0)
      {
        tmp = parse_arg(argv, &argn);
        bytes += (1024*1024*1024*tmp);
      }
      else if (strcmp(argv[argn], "-h") == 0 || 
               strcmp(argv[argn], "--help") == 0)
      {
        usage();
        help();
        footer();
        EXIT;
      }
      else if (strcmp(argv[argn], "-v") == 0 || 
               strcmp(argv[argn], "--version") == 0)
      {
        version();
        footer();
        EXIT;
      }
      else if (strcmp(argv[argn], "--license") == 0)
      {
        license();
        footer();
        EXIT;
      }
      else
      {
        bytes = 0;
        printf("%s: unrecognized option '%s'\n", argv0, argv[argn]);
        printf("Try '%s --help' for more information.\n", argv0);
        EXIT;
      }
      ++argn;
    }
    if (bytes)
      bytesfree(bytes);
  }
  else
  {
    bytes = atoi(argv[argn]);
    if (bytes)
    {
      printf("Warning: no size argument specified.  defaulting to megabytes.\n");
      printf("         try '%s --help' for more options.\n",argv0);
      printf("\n");
      bytesfree(bytes*1024*1024);
    }
    else
    {
      usage();
    } 
  }
  exit(0); 
}


int bytesfree(unsigned bytes)
{
  char* ptr=NULL;
  int* i=NULL;
  
  if ((ptr = (char *)malloc(bytes * sizeof(char))))
  {
    printf ("Allocating %d bytes.\n", bytes);
    for (i=(int*)ptr; i<(int*)(ptr+bytes); ++i)
    {
    *i = (RAND_MAX*rand()/RAND_MAX+1);
    }
    free(ptr);
    printf ("%d bytes freed.  Exiting.\n", bytes);
  }
  else
  {
    printf ("Can not allocate %d bytes.  Exiting.\n",bytes);
  }
 
}

unsigned parse_arg(char** argv, int *argn)
{
  char* pos;
  int tmp;
  unsigned bytes = 0;

  if ((pos = (char*)strchr(argv[*argn], '=')) != NULL)
  {
    ++pos;
    if (pos && *pos)
    {
      tmp = atoi(pos);
    }
    else
    {
      missing_arg();
      EXIT;
    }
  }
  else
  {
    *argn += 1;
    if (argv[*argn])
    {
      tmp = atoi(argv[*argn]);
    }
    else
    {
      missing_arg();
      EXIT;
    }
  }
  if (tmp)
    bytes += tmp;
  else
    bad_arg(argv[*argn]);
  return bytes;
}

void version()
{
  printf("mbfree 1.0.5\n");
  printf("Written by Jeremy Brand.\n");
  printf("\n");
  printf("Copyright © 2000, 2001 Jeremy Brand.\n");
  printf("This is free software; see the source for copying conditions.  There is NO\n");
  printf("warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\n");
  printf ("\n");
}

void usage()
{
  printf ("Usage: %s [OPTION]...\n", argv0);
  printf ("Attempts to free memory\n");
  printf ("\n");
}

void missing_arg()
{
  printf ("Warning: missing argument\n");
  printf ("    '%s --help' for more options\n",argv0);
  printf ("\n");
}

void bad_arg(char* arg)
{

  if (strcmp(arg, "-h") == 0 || strcmp(arg, "--help") == 0)
  {
    usage();
    help();
    footer();
    EXIT;
  }
  else if (strcmp(arg, "-v") == 0 || strcmp(arg, "--version") == 0)
  {
    version();
    footer();
    EXIT;
  }
  else if (strcmp(arg, "--license") == 0)
  {
    license();
    footer();
    EXIT;
  }

  printf ("%s: invalid option '%s'\n", argv0, arg);
  printf ("Try '%s --help' for more information.\n",argv0);
  printf ("\n");
  EXIT;
}

void help()
{
  printf ("  -b, --bytes=BYTES          attempt to free BYTES bytes\n");
  printf ("  -k, --kilobytes=KILOBYTES  attempt to free KILOBYTES kilobytes\n");
  printf ("  -m, --megabytes=MEGABYTES  attempt to free MEGABYTES megabytes\n");
  printf ("  -g, --gigabytes=GIGABYTES  attempt to free GIGABYTES gigabytes\n");
  printf ("  -h, --help                 display this help and exit\n");
  printf ("  -v, --version              output version information and exit\n");
  printf ("      --license              output the software license\n");
  printf ("\n");

}

void license()
{
  printf("\n");
  printf("   Copyright © 2000, 2001 Jeremy Brand <jeremy@nirvani.net>.\n");
  printf("   http://www.jeremybrand.com/Jeremy/Brand/Jeremy_Brand.html\n");
  printf("\n");
  printf("   Redistribution and use in source and binary forms, with or without\n");
  printf("   modification, are permitted provided that the following conditions\n");
  printf("   are met:\n");
  printf("   1. Redistributions of source code must retain the above copyright\n");
  printf("      notice, this list of conditions and the following disclaimer.\n");
  printf("   2. Redistributions in binary form must reproduce the above copyright\n");
  printf("      notice, this list of conditions and the following disclaimer in the\n");
  printf("      documentation and/or other materials provided with the distribution.\n");
  printf("\n");
  printf("   THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND\n");
  printf("   ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE\n");
  printf("   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE\n");
  printf("   ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE\n");
  printf("   FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL\n");
  printf("   DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS\n");
  printf("   OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)\n");
  printf("   HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT\n");
  printf("   LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY\n");
  printf("   OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF\n");
  printf("   SUCH DAMAGE.  \n");
  printf("\n");
}

void footer()
{
  printf ("New versions can be found here: http://www.nirvani.net/software/\n");
  printf ("Report bugs to: jeremy@nirvani.net\n");
}
