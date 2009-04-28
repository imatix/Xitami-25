/*  ----------------------------------------------------------------<Prolog>-
    Name:       xicorstd.d
    Title:      Core for standard Xitami

    Generated:  2004/07/22 from ximodel.gsl, using GSLgen.
 ------------------------------------------------------------------</Prolog>-*/

/*  Define the agents we want to use                                         */
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
