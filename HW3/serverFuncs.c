#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <wait.h>
#include <signal.h>
#include "server_constants.h"


void SD_parse(char *rq, int fd)
{
 	char cmd[BUFSIZ], arg[BUFSIZ];
 	struct stat info;

 	strcpy(arg,WPDirectory);
 	if(sscanf(rq,"%s %s",cmd,arg+strlen(WPDirectory))!=2) { return ; }
 	if(strcmp(cmd,"GET")!=0){ 
 	 	fprintf(stderr, "ClientRQ:%s \n", "501");
 		Err_501(fd);
 	}
 	else if(stat(arg,&info)==-1){ //not_exit(arg)){
 		fprintf(stderr, "ClientRQ:%s \n", "404");
 		Err_404(arg,fd);
 	}
 	else if(stat(arg,&info)!=-1 && S_ISDIR(info.st_mode)  ){//(is_dir(arg)){
 		fprintf(stderr, "ClientRQ:%s \n", "direct");
 		s_dir(arg,fd);
	}
 	else if(is_cgi(arg)){
 		fprintf(stderr, "ClientRQ:%s \n", "CGI");
 		r_prg(arg,fd);
 		
 	}
 	else{
 		fprintf(stderr, "ClientRQ:%s \n", " else");
 		f_cat(arg,fd);
 	}
}

void s_header(FILE *fp, char *context_type)
{
	fprintf(fp, "HTTP/1.1 200 OK\r\n");
	if(context_type)
		fprintf(fp, "Context-type: %s\r\n",context_type);
}

void Err_501(int fd)
{
	FILE *fp=fdopen(fd,"w");
	fprintf(fp,"HTTP/1.1 501 Not Implemented\r\n");
	fprintf(fp,"Context-type: text/html\r\n");
	fprintf(fp,"\r\n");
	fprintf(fp,"<html><head><title>Error 501</title></head><body><h1>Error 501</h1><p>That command is not yet Implemented</p></body></html>\r\n");
	fclose(fp);
}

void Err_404(char *item, int fd)
{
	FILE *fp=fdopen(fd,"w");
	fprintf(fp,"HTTP/1.1 404 Not Found\r\n");
	fprintf(fp,"Context-type: text/html\r\n");
	fprintf(fp,"\r\n");
	fprintf(fp,"<html><head><title>Error 404</title></head><body><h1>Error 404</h1><p>%s was Not Found</p></body></html>\r\n",item);
	fclose(fp);
}

void s_dir(char *dir, int fd)
{
	FILE *fp;
	fp=fdopen(fd,"w");
	s_header(fp,TXT_C);
	fprintf(fp,"\r\n");
	fflush(fp);
	dup2(fd,1);
	dup2(fd,2);
	close(fd);
	execlp("ls","ls","-l",dir,NULL);
	perror(dir);
	exit(1);
}

char *get_context(char *arg)
{
	char *fext;
	char *context= TXT_C;
	
	fext=strrchr(arg,'.');
	if(fext == NULL)
	{	return "";	}
	

	if(strcmp(fext,".html")==0)
	{	context=HTML_C;	}
	else if(strcmp(fext,".gif")==0)
	{	context=GIF_C;	}
	else if(strcmp(fext,".jpg")==0)
	{	context=JPG_C;	}
	else if(strcmp(fext,".jpeg"))
	{	context=JPEG_C;	}

	return context;

}
int is_cgi(char *arg)
{

	char *fext;
	fext=strrchr(arg,'.');
	if(fext == NULL)
	{ return 0; }

	if(strcmp(fext, ".cgi")==0)
	{ return 1; }
	else
	{ return 0; }

}

void r_prg(char *prog, int fd)
{
	FILE *fp;
	fp=fdopen(fd,"w");
	s_header(fp,NULL);
	fflush(fp);
	dup2(fd,1);
	dup2(fd,2);
	close(fd);
	execl(prog,prog,NULL);
	perror(prog);
}

void f_cat(char *arg, int fd)
{

	char *extension=get_context(arg);
	char *context= TXT_C;
	FILE *fpsock, *fpfile;
	int  c;

	fpsock=fdopen(fd,"w");
	fpfile=fopen(arg,"r");
	if(fpsock!=NULL&&fpfile!=NULL){
		s_header(fpsock,context);
		fprintf(fpsock,"\r\n");
		while((c=getc(fpfile))!=EOF){
			putc(c,fpsock);
		}
		
	}
	fclose(fpfile);
	fclose(fpsock);
	exit(0);
}






