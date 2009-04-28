/*  ----------------------------------------------------------------<Prolog>-
    Name:       xicorpro.i
    Title:      Core for Xitami/Pro

    Generated:  2004/07/22 from ximodel.gsl, using GSLgen.
 ------------------------------------------------------------------</Prolog>-*/

    /*  Initialise the SMT kernel                                            */
    smt_init ();
    server_name = "Xitami/Pro";

    /*  Load the agents we want to use                                       */
    if (*CONFIG ("ssl-http:enabled"))
        smtssl_init ();                 /*  SSL interface                    */
    if (*CONFIG ("lrwp:enabled"))
        xilrwp_init ();                 /*  LRWP service agent               */
    if (*CONFIG ("security:admin"))
        xiadmin_init ();                /*  Administration agent             */
    if (*CONFIG ("server:supervisor"))
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
