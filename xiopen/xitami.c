/*===========================================================================*
 *  Name:       xitami.c                                                     *
 *  Title:      Xitami Web Server                                            *
 *                                                                           *
 *  Generated:  2004/07/22 from ximodel.gsl, using GSLgen.                   *
 *                                                                           *
 *  Copyright (c) 1991-2003 iMatix Corporation                               *
 ============================================================================*/

#include "smtdefn.h"                    /*  SMT definitions                  */
#include "smthttpl.h"                   /*  SMT HTTP functions               */
#include "xixlog.h"
#include "version.h"    

#define SERVER_NAME "Xitami/" VERSION

#define USAGE                                                               \
    "Syntax: xitami [options...]\n"                                         \
    "Options:\n"                                                            \
    "  -w directory     Working directory for server\n"                     \
    "  -r directory     Root directory for web pages (webpages)\n"          \
    "  -c directory     Directory for CGI programs (cgi-bin)\n"             \
    "  -b portbase      Shift HTTP port 80 by this value.  E.g. to run\n"   \
    "                   Xitami on port 5080, do 'xitami -b 5000'\n"         \
    "  -f directory     Root directory for FTP files (webpages)\n"          \
    "  -q               Quiet mode: no messages\n"                          \
    "  -s               Server mode: run as background job\n"               \
    "  -S               Console mode: run as foreground job\n"              \
    "  -t               Trace all socket i/o operations to log file\n"      \
    "  -v               Show Xitami version information\n"                  \
    "  -h               Show summary of command-line options\n"             \
    "\nThe order of arguments is not important. Switches and filenames\n" \
    "are case sensitive. See documentation for detailed information.\n"

/*  Prototypes for agents used by this Xitami model                          */

int xilrwp_init (void);                 /*  LRWP service agent               */
int xiadmin_init (void);                /*  Administration agent             */
int xisuper_init (void);                /*  Supervisor agent                 */
int xierror_init (void);                /*  Error-simulation agent           */
int xiredir_init (void);                /*  Redirection agent                */
int xiddns_init (void);                 /*  Dynamic DNS registration         */
int xiimap_init (void);                 /*  Image mapping agent              */
int xixlog_init (void);                 /*  Extended logging agent           */
int xixssi_init (void);                 /*  Internal SSI processor           */
int xixxml_init (void);                 /*  Internal XML processor           */

int
main (int argc, char *argv [])
{
    int
        argn;                           /*  Argument number                  */
    Bool
        args_ok = TRUE,                 /*  Were the arguments okay?         */
        quiet_mode = FALSE;             /*  -q means suppress messages       */
    char
        *workdir,                       /*  Working directory                */
        *rootdir,                       /*  Default root directory           */
        *cgidir,                        /*  CGI program directory            */
        *ftproot,                       /*  Default FTP root directory       */
        *portbase,                      /*  Value for IP portbase            */
        *background,                    /*  -s means run in background       */
        **argparm;                      /*  Argument parameter to pick-up    */

    /*  First off, switch to user's id                                       */
    set_uid_user ();

    /*  These are the arguments we may get on the command line               */
    workdir    = NULL;
    rootdir    = NULL;
    cgidir     = NULL;
    portbase   = NULL;
    background = NULL;
    ftproot    = NULL;

    argparm = NULL;                     /*  Argument parameter to pick-up    */
    for (argn = 1; argn < argc; argn++)
      {
        /*  If argparm is set, we have to collect an argument parameter      */
        if (argparm)
          {
            if (*argv [argn] != '-')    /*  Parameter can't start with '-'   */
              {
                *argparm = strdupl (argv [argn]);
                argparm = NULL;
              }
            else
              {
                args_ok = FALSE;
                break;
              }
          }
        else
        if (*argv [argn] == '-')
          {
            switch (argv [argn][1])
              {
                /*  These switches take a parameter                          */
                case 'w':
                    argparm = &workdir;  break;
                case 'r':
                    argparm = &rootdir;  break;
                case 'c':
                    argparm = &cgidir;   break;
                case 'b':
                    argparm = &portbase; break;
                case 'f':
                    argparm = &ftproot;  break;

                /*  These switches have an immediate effect                  */
                case 'q':
                    quiet_mode = TRUE;
                    break;
                case 's':
                    background = "1";
                    break;
                case 'S':
                    background = "0";
                    break;
                case 't':
                    smtsock_trace (TRUE);
                    break;
                case 'v':
                    coprintf (PRODUCT);
                    coprintf (BUILDMODEL);
                    coprintf (COPYRIGHT);
                    coprintf ("Built on: %s", BUILDDATE);
                    exit (EXIT_SUCCESS);
                case 'h':
                    coprintf (SERVER_NAME);
                    coprintf (COPYRIGHT);
                    coprintf (USAGE);
                    exit (EXIT_SUCCESS);

                /*  Anything else is an error                                */
                default:
                    args_ok = FALSE;
              }
          }
        else
          {
            args_ok = FALSE;
            break;
          }
      }

    /*  If there was a missing parameter or an argument error, quit          */
    if (argparm)
      {
        puts ("Argument missing - type 'xitami -h' for help");
        exit (EXIT_FAILURE);
      }
    else
    if (!args_ok)
      {
        puts ("Invalid arguments - type 'xitami -h' for help");
        exit (EXIT_FAILURE);
      }
      
    /*  Set server working directory if necessary                            */
    if (workdir
    &&  set_curdir (workdir))
      {
        printf ("Can't work in '%s' - %s\n", workdir, strerror (errno));
        exit (EXIT_FAILURE);
      }

    /*  Load configuration data, if any, into the config_table               */
    config = ini_dyn_load (NULL, "xitami.cfg");
    ini_dyn_load (config, CONFIG ("server:defaults"));

    /*  Initialise arguments, taking defaults from the config_table          */
    if (!rootdir)
        rootdir    = CONFIG ("server:webpages");
    if (!cgidir)
        cgidir     = CONFIG ("server:cgi-bin");
    if (!portbase)
        portbase   = CONFIG ("server:portbase");
    if (!background)
        background = CONFIG ("server:background");
    if (!ftproot)
        ftproot    = CONFIG ("ftp:root");

    /*  Now, handle the remaining arguments we got                           */
    ip_portbase = atoi (portbase);
    if (quiet_mode)
      {
        fclose (stdout);                /*  Kill standard output             */
        fclose (stderr);                /*   and standard error              */
      }
    else
      {
        puts (SERVER_NAME);
        puts (COPYRIGHT);
      }

    if (*background == '1')
      {
        const char
           *background_args [] = { "-s", NULL };

        puts ("Moving into the background");
        if (process_server (NULL, NULL, argc, argv, background_args) != 0)
          {
            puts ("Backgrounding failed.  Giving up.");
            exit (EXIT_FAILURE);
          }
      }

    /*  Initialise the SMT kernel                                            */
    smt_init ();
    server_name = "Xitami";

    /*  Load the agents we want to use                                       */
    if (*CONFIG ("lrwp:enabled") == '1')
        xilrwp_init ();                 /*  LRWP service agent               */
    if (*CONFIG ("security:admin") == '1')
        xiadmin_init ();                /*  Administration agent             */
    if (*CONFIG ("server:supervisor") == '1')
        xisuper_init ();                /*  Supervisor agent                 */
    xierror_init ();                    /*  Error-simulation agent           */
    xiredir_init ();                    /*  Redirection agent                */
    xiddns_init ();                     /*  Dynamic DNS registration         */
    xiimap_init ();                     /*  Image mapping agent              */
    xixlog_init ();                     /*  Extended logging agent           */
    xixssi_init ();                     /*  Internal SSI processor           */
    xixxml_init ();                     /*  Internal XML processor           */
    smthttp_init (rootdir, cgidir);     /*  HTTP agent, required             */
    smtftpc_init (ftproot);             /*  FTP service agent                */
    smtpipe_init (CONFIG ("server:pipedef"));  /*  Transfer pipe agent       */

    smt_exec_full ();                   /*  Run SMT until completed          */
    smt_term ();

    /*  Deallocate configuration symbol table                                */
    sym_delete_table (config);

    /*  Check that all memory was cleanly released                           */
    mem_assert ();

    return (EXIT_SUCCESS);
}
