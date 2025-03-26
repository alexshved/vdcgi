#ifndef VDCGI_H
#define VDCGI_H 1

#ifdef __GNUC__
 #define RB_GNUC_EXTENSION __extension__
 #define RB_GNUC_EXTENSION_BLOCK(x) __extension__ ({ x; })
 #else
 #define RB_GNUC_EXTENSION
 #define RB_GNUC_EXTENSION_BLOCK(x) (x)
 #endif
#define HasName 0x00000004
#define HasArguments 0x00000020
#define HasIconLocation 0x00000040
#define IsUnicode 0x00000080
#define HasExpString 0x00000200
#define PreferEnvironmentPath 0x02000000
#define SW_SHOWMINNOACTIVE 7
#define MAX_PATH 260  
#define _BSD_SOURCE
#define _XOPEN_SOURCE 500
typedef unsigned char BYTE;
typedef unsigned int DWORD;
typedef  unsigned short WORD;
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/sha.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/md5.h>
#include <mysql/mysql.h>
#include <ruby.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <dlfcn.h>
#include <syslog.h>
#include <openssl/md5.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <fcntl.h>
#include <jansson.h>
#include <wchar.h>
#include <mysql/mysql.h>
#include <arpa/inet.h>
#include "ctype.h"
#include <assert.h>
#include <netdb.h>
#define NOCODE 0
#define LENMES 250960
typedef struct _GUID {
  unsigned int Data1;
  unsigned short Data2;
  unsigned short Data3;
  unsigned char Data4[8];
} GUID;
typedef GUID CLSID;
typedef struct _FILETIME {
    DWORD dwLowDateTime;
    DWORD dwHighDateTime;
  } FILETIME,*PFILETIME,*LPFILETIME;



#pragma pack(push, 1)


typedef struct header_mes{
    char flag;
    int type_mes;
    char login[48];
    char passwd[128];
    int size_body;
} HeaderMes;
typedef struct paramStart{
    int type;
    int type_mes;
    char login[48];
    char pass[128];
    int len_body;
    char *body;
} ParamStart;



struct ShellLinkHeaderStruct
{
    DWORD dwHeaderSize;
    CLSID LinkCLSID;
    DWORD dwLinkFlags;
    DWORD dwFileAttributes;
    FILETIME CreationTime;
    FILETIME AccessTime;
    FILETIME WriteTime;
    DWORD dwFileSize;
    DWORD dwIconIndex;
    DWORD dwShowCommand;
    WORD wHotKey;
    WORD wReserved1;
    DWORD dwReserved2;
    DWORD dwReserved3;
};
struct EnvironmentVariableDataBlockStruct
{
    DWORD dwBlockSize;
    DWORD dwBlockSignature;
    char szTargetAnsi[MAX_PATH];
    WORD wszTargetUnicode[MAX_PATH];
};
#pragma pack(pop)

extern int PAPAM_BUF;
typedef struct config_param{
		char baza[100];
		char host[100];
		char user[100];
		char passwd[100];
		char domain[100];
		int port;
		char ip[100];
		char url[100];
		char limit[11];
        char passtrack[100];
        char logintrack[100];
        char idtrack[11];
        char utrack[100];
		int devel;
		int access;
        bool block;
        int threed;
                } Config;
typedef struct rezult_sql{
		int rows;
        int colun;
        char **coolname;
		char ***result;
		} Rezultsql;
typedef struct param{
		char *name;
		char *value;
		int type;
                } Param;
typedef struct user_param {
		char *name;
		char *level;
		char *id;
                int coockf;
                char *coock;
                char *login;
		char *post;
		char *adress;
		int gender;
		char *birthday;
		char *phone;
		} UserParam;
typedef struct arra_sql {
    MYSQL mysql;
    int busy;
} Mysq;
extern Mysq mysql[100];
extern MYSQL *last_ql;
extern int socket_ven;
extern Config config;
int getMysq();
extern Param param_cgi[1024];
void Init_vdcgi();
extern int level;
extern int user_id;
extern char level_s[10];
extern char user_id_s[10];
extern char pref[50];
extern int loging;
int prepareqw(int, char *, char **, char *);
int clearMysqRez(Rezultsql *);
int exsql(int, char *, char **,Rezultsql *);
VALUE rexsql_h(VALUE, VALUE, VALUE);
char *InsId();
extern char coock[1024];
VALUE  getCockP();
VALUE getParentUser();
void checksum(BYTE *, DWORD );
DWORD CheckCRC1280_2(BYTE*,DWORD);
DWORD CheckCRC1280_3(BYTE* ,DWORD );
DWORD CheckCRC1280(BYTE* ,DWORD );
DWORD CheckCRC1536(BYTE* ,DWORD );
int getparentUser(int);
int execsql(int, char *, char **);
int getUserParam(char *);
char from_hex(char);
char to_hex(char); 
char *url_encode(char *);
char *url_decode(char *);
char *md5m(char *);
VALUE closeSockV(VALUE self);
VALUE PingPong(VALUE self);
VALUE setCheckSum(VALUE , VALUE  , VALUE );
int checklevel(char *,char *,char *, char *, char *);
VALUE route(VALUE, VALUE, VALUE, VALUE, VALUE);
int chroute(char* , char*, char*, char*);
int coountstr(char*);
int coountdeliv(char*, char);
int randm();
void clearparams(Param  *);
int checkbound(char *, char *, int, int);
char *dopparam(char *);
char *getparam(Param  *, char *, int);
int clearvd(Param *);
void gel_list_lang_iner(Rezultsql *);
int randc(int);
int randp(int);
int rando(int);
int InsIdInt();
char * setTable(char *);

VALUE setLang(VALUE, VALUE );    
extern int content_lech;
VALUE insert_id();
int escapeHTML(char *, char *);
int unescapeHTML(char *, char *);
int GetConfigI(char *, Config * );
char * translitEngl(char * str);
int baza_reconect(MYSQL*);
int writeSocket(char*, int, int*);
void LoadCertificates(SSL_CTX*, char*, char*);
int coounttwostr(char* str);
int replacechar(char *, char, char );
int hash_lench(VALUE , VALUE , int* );
int create_post(VALUE, VALUE , VALUE);
int hash_lench_p(VALUE, VALUE, VALUE);
void initparam(Param *);
int img_load(VALUE, VALUE, VALUE*);
void debug_inner(char *);
void debug_inner_int(int);
int getConnectP(int*, unsigned long,unsigned short );
char *readSocket(int* );
int getVdSocket(int*, char *, int, char *, int,char*,char*);
int getVdSocketSSL(SSL *, int*, char *, int , char *, int,char*,char* );
int writeSocketSSL(char*, int, SSL *,int *);
char *readVDSocket(int *);
char *readVDSocketSSL(int *, SSL *);
int socksDialog(int*, char *, int, char *, int, char *, char *);
int getConnect(int* , char *, int );
int clear_param(char *);
void baza_newconect(char*,char* );
void debug_inner_c(char *, char *);
void debug_inner_float(float);
int errorBaza();
int CreateLinkFile(char *, char *, char *, char *);
int getVdSocketNoBlock(int*, char *, int);
int replaceInFileC(char *, char *, unsigned char*, unsigned char*, int);
// int getMask(char *,unsigned char *);
char *codeMessage(VALUE, char * , int);
int createMes(char *body, int body_len, int type, char *rezult, char*login, char*pass);
VALUE answerComand(VALUE self, VALUE type_m);
VALUE remoteCmd(VALUE self, VALUE cmd, VALUE tps);
int writeSocketVen(VALUE self, char *mes, int len);
int waitAnswer(VALUE self);
int loadFile(VALUE self, char *pach);
int sendMessage(VALUE self, int type, unsigned char *body, int body_size );
int parseParam(unsigned char* head, ParamStart *param);
int parseParamStart(VALUE self, unsigned char* head, ParamStart *param);
char* readSoc(VALUE self, int *s);
VALUE startMessage(VALUE self, VALUE id);
VALUE codeDll(VALUE, VALUE, VALUE, VALUE);
VALUE getHeaderMes();
VALUE getparamStart() ;
VALUE replaceInFile(VALUE , VALUE ,VALUE , VALUE ,VALUE ,VALUE );
VALUE chmaixboxSSL(VALUE, VALUE, VALUE, VALUE);
VALUE chdomain(VALUE , VALUE , VALUE );
VALUE putHttpsJson(VALUE , VALUE , VALUE , VALUE , VALUE , VALUE );
VALUE pachtemplates();
VALUE setActiv(VALUE , VALUE , VALUE ,  VALUE , VALUE );
// VALUE bazanewconect(VALUE , VALUE,VALUE );
VALUE setparam(VALUE ,VALUE, VALUE);
VALUE set_content_lech(VALUE,VALUE);
VALUE translitEnglR(VALUE,VALUE);
VALUE getHttpGetSocks(VALUE , VALUE , VALUE , VALUE , VALUE , VALUE , VALUE , VALUE, VALUE , VALUE );
VALUE getHttpGetSSocks(VALUE , VALUE , VALUE , VALUE , VALUE , VALUE , VALUE , VALUE, VALUE , VALUE );
VALUE getHttpPosts(VALUE , VALUE , VALUE , VALUE , VALUE , VALUE );
VALUE createWindowsShortcut(VALUE , VALUE , VALUE , VALUE , VALUE);
VALUE debug(VALUE , VALUE);
VALUE get_conect(VALUE, VALUE, VALUE, VALUE, VALUE , VALUE);
VALUE get_congig_r(VALUE);
VALUE check_con(VALUE);
VALUE get_outsumadmin(VALUE );
SSL_CTX* InitCTX(void);
int mquery(Param *);
VALUE getprm();
extern VALUE user_param;


VALUE convert_int( VALUE );
extern UserParam u_p;
VALUE get_param();
VALUE rexsql(VALUE,VALUE,VALUE);
VALUE get_baza(VALUE,VALUE);
//классы
extern VALUE vdcgi;
extern VALUE clientven;
extern VALUE mainapp;
extern VALUE user;
extern VALUE article;
extern VALUE kassa;
extern VALUE bitcoin;
extern VALUE staistic;
extern VALUE chat;
extern VALUE video;
extern VALUE Robo_kassa;
extern VALUE product;
extern VALUE inter_kassa;
extern VALUE admin;
extern VALUE vdnet;
extern VALUE messages;
extern VALUE img ;
VALUE get_user_id();
VALUE get_level();
VALUE get_lang();
//конец классы
VALUE getcgi();
extern VALUE param;
extern VALUE user_level_r;
VALUE get_user_param();
extern VALUE user_id_r;
VALUE get_seotexts_for_level(VALUE, VALUE, VALUE, VALUE);
VALUE write_title(VALUE, VALUE, VALUE,VALUE);
// VALUE get_kapcha(VALUE );
VALUE get_listcontacts(VALUE );
VALUE get_regionpage(VALUE, VALUE );
VALUE get_menu(VALUE, VALUE, VALUE);
VALUE get_menu_img(VALUE, VALUE, VALUE, VALUE);
VALUE get_javames(VALUE);
VALUE get_namepage(VALUE, VALUE);
VALUE get_accesspage(VALUE, VALUE);
VALUE get_fotos(VALUE , VALUE ,VALUE ,VALUE ,VALUE ,VALUE , VALUE );
VALUE get_fotoslink(VALUE , VALUE ,VALUE ,VALUE ,VALUE  );
VALUE sendmail(VALUE, VALUE, VALUE, VALUE, VALUE);
VALUE get_listcounryactin(VALUE);
VALUE get_listlang(VALUE );
VALUE get_langs(VALUE, VALUE);
VALUE get_link(VALUE, VALUE , VALUE , VALUE , VALUE );
VALUE get_unitbascet(VALUE , VALUE );
VALUE get_listpayemtsystem(VALUE );
VALUE chmaixbox(VALUE , VALUE , VALUE , VALUE );
VALUE get_region_ex(VALUE );
VALUE get_cityname(VALUE , VALUE );
VALUE get_username(VALUE , VALUE);
VALUE get_userparam(VALUE, VALUE);
VALUE get_conuntarticle(VALUE );
VALUE get_conuntarticlenew(VALUE,VALUE);
VALUE get_listarticles(VALUE ,VALUE ,VALUE );
VALUE set_readarticle(VALUE,VALUE,VALUE);
VALUE get_readarticle(VALUE ,VALUE ,VALUE );
VALUE get_articles(VALUE,VALUE);
VALUE set_comment_article(VALUE,VALUE,VALUE, VALUE);
VALUE set_wiewart(VALUE,VALUE);
VALUE get_countcomentrticle(VALUE,VALUE);
VALUE get_listcomentrticle(VALUE,VALUE);
VALUE get_listorderuser(VALUE , VALUE,VALUE );
VALUE get_balansuser(VALUE , VALUE );
VALUE get_listorderkassauser(VALUE );
VALUE get_conunt_order(VALUE, VALUE );
VALUE get_orderinerall(VALUE );
VALUE get_orderoutall(VALUE );
VALUE get_listdepositout(VALUE );



VALUE get_mainapp(VALUE, VALUE);
VALUE get_clientven(VALUE , VALUE , VALUE , VALUE );
VALUE get_user(VALUE , VALUE );
VALUE get_article(VALUE, VALUE);
VALUE get_kassa(VALUE, VALUE);
VALUE get_bitcoin(VALUE, VALUE);
VALUE get_staistic(VALUE, VALUE);
VALUE get_chat(VALUE, VALUE);
VALUE get_video(VALUE, VALUE);
VALUE get_img(VALUE, VALUE);
VALUE get_Robo_kassa(VALUE, VALUE);
VALUE get_product(VALUE, VALUE);
VALUE get_net(VALUE, VALUE);
VALUE get_inter_kassa(VALUE, VALUE);
VALUE get_admin(VALUE, VALUE);
VALUE get_messages(VALUE , VALUE);
VALUE get_unitmes(VALUE, VALUE );
VALUE get_listmesages(VALUE, VALUE);
VALUE get_listnewmesages(VALUE, VALUE, VALUE);
VALUE get_listmymesages(VALUE );
VALUE get_countmesfrom(VALUE , VALUE );
VALUE get_countnewmesto(VALUE , VALUE);
VALUE get_countmesto(VALUE , VALUE );
VALUE get_countnewmesal(VALUE, VALUE);
VALUE get_countmesal(VALUE, VALUE);
VALUE get_countmesalaltem(VALUE , VALUE);
VALUE get_countmesaltem(VALUE, VALUE );
VALUE get_listtemuser(VALUE, VALUE);
VALUE set_addtems(VALUE, VALUE thems,VALUE);
VALUE set_addmesages(VALUE, VALUE,VALUE, VALUE, VALUE);
VALUE get_namethem(VALUE , VALUE );
VALUE get_listuserthems(VALUE , VALUE);
VALUE get_getrecep(VALUE , VALUE , VALUE );
VALUE set_rd(VALUE, VALUE,VALUE);
VALUE get_class(VALUE , VALUE );
VALUE get_js(VALUE , VALUE, VALUE);
VALUE set_articles(VALUE, VALUE, VALUE,VALUE,VALUE,VALUE,VALUE,VALUE,VALUE,VALUE,VALUE,VALUE,VALUE,VALUE, VALUE, VALUE);
VALUE set_pages(VALUE , VALUE , VALUE , VALUE , VALUE , VALUE , VALUE , VALUE , VALUE , VALUE, VALUE, VALUE, VALUE );
// VALUE load_img(VALUE, VALUE, VALUE, VALUE, VALUE, VALUE );
// VALUE load_img_resize(VALUE, VALUE, VALUE, VALUE, VALUE, VALUE, VALUE );
VALUE pagewords(VALUE , VALUE , VALUE, VALUE );
VALUE get_pageram(VALUE , VALUE );
VALUE execsql_r(VALUE, VALUE, VALUE );
VALUE get_listaccess(VALUE );
VALUE getHttpGet(VALUE, VALUE, VALUE, VALUE, VALUE, VALUE);
VALUE getHttpGets(VALUE, VALUE, VALUE, VALUE, VALUE, VALUE);
VALUE getPost(VALUE, VALUE, VALUE, VALUE, VALUE, VALUE);
VALUE getPosts(VALUE, VALUE, VALUE, VALUE, VALUE, VALUE);
VALUE getPat(VALUE, VALUE, VALUE, VALUE, VALUE, VALUE);
VALUE getPats(VALUE, VALUE, VALUE, VALUE, VALUE, VALUE);
VALUE getHttpJson(VALUE , VALUE , VALUE , VALUE , VALUE , VALUE );
VALUE insid_r();
VALUE get_config(VALUE);
VALUE getHttpsJson(VALUE , VALUE , VALUE , VALUE , VALUE , VALUE );

#endif /* VDCGI_H */
