#define WPDirectory	"./"

#define MAXLINE		256
#define BUFLEN		256 
 
#define OK 		200
#define E404		404
#define E501		501

#define TXT_C "text/plain"
#define HTML_C "text/html"
#define JPG_C "image/jpg"
#define JPEG_C "image/jpeg"
#define GIF_C "image/gif"
#define PNG_C "image/png"
#define CSS_C "text/css"
#define PDF_C "application/pdf"


void SD_parse(char *rq, int fd);
void s_header(FILE *fp, char *context_type);
void Err_501(int fd);
void Err_404(char *item, int fd);

void s_dir(char *dir, int fd);

char *get_context(char *arg);
int is_cgi(char *f);
void r_prg(char *prog, int fd);
void f_cat(char *f, int fd);

