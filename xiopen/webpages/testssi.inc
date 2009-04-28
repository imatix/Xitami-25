<HR>
The local date is:            <!--#echo var="DATE_LOCAL"--><BR>
The GMT date is:              <!--#echo var="DATE_GMT"--><BR>
The version of the server is: <!--#echo var="SERVER_SOFTWARE"--><BR>
The CGI gateway version is:   <!--#echo var="GATEWAY_INTERFACE"--><BR>
The server name is:           <!--#echo var="SERVER_NAME"--><BR>
This file is called:          <!--#echo var="DOCUMENT_NAME"--><BR>
This file's URI is:           <!--#echo var="DOCUMENT_URI"--><BR>
This file was last modified:  <!--#echo var="LAST_MODIFIED" --><BR>
The size of the SSI file is   <!--#fsize virtual="/testssi.ssi"--><BR>
testssi.ssi was last modified <!--#flastmod virtual="/testssi.ssi"--><BR>
<HR>
Output of CGI program: <!--#exec cgi="/cgi-bin/testcgi.exe?arguments"--><BR>
<HR>
You are using <!--#echo var="HTTP_USER_AGENT"--><BR>
You came from <!--#echo var="HTTP_REFERER"-->
<HR>
