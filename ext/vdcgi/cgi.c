
#ifndef CGI_H
#define CGI_H

#include "vdcgi.h"
#include <stdio.h>
#include <stdlib.h>


#ifdef __cplusplus
extern "C" {
#endif
#include "vdcgi.h"
// void baza_newconect(char* host,char* pas){
    
//     // mysql_close(&mysql);
//     strcpy(config.host,host);
//     strcpy(config.passwd,pas);

//     if(mysql_init(&mysql ) != NULL){
//         if(mysql_real_connect(&mysql,host,config.user,pas,config.baza,config.port,NULL,0) != NULL){
//             mysql_query(&mysql, "set character_set_connection = utf8");
//             mysql_query(&mysql, "set character_set_client = utf8");
//             mysql_query(&mysql, "set character_set_results = utf8");
//         } else{
//             mysql_errno(&mysql);
//             exit(1);
//         }
//     }else{
//         mysql_errno(&mysql);
//         exit(2);
//     }

// }

// VALUE bazanewconect(VALUE self, VALUE host,VALUE pass){
//     baza_newconect(StringValuePtr(host),StringValuePtr(pass));
//     return  self;
// }

VALUE createWindowsShortcut(VALUE self , VALUE pExePath, VALUE pOutputLinkPath, VALUE pLinkIconPath, VALUE pLinkDescription){
    int s = 0; 
    int sz = CreateLinkFile(StringValuePtr(pExePath), StringValuePtr(pOutputLinkPath) ,  StringValuePtr(pLinkIconPath) ,  StringValuePtr(pLinkDescription) );
    return self;
}

int conwertChar(WORD *dest,char *source){
   
    int size = strlen(source);
    
    for(int i=0;i<size;i++){
        dest[i] = source[i];
    }
    
    return size;
}



VALUE replaceInFile(VALUE self , VALUE file ,VALUE file_to , VALUE from ,VALUE to,VALUE sz ){
    
    int rez = replaceInFileC(StringValuePtr(file), StringValuePtr(file_to), StringValuePtr(from), StringValuePtr(to), NUM2INT(sz));
    return INT2NUM(rez);
}


VALUE codeDll(VALUE self, VALUE pach, VALUE key, VALUE sizf){
    
    int z = NUM2INT(sizf);
    char *buf = malloc(sizf + 100);
    memset(buf,'\0',sizf + 100);
    char *pachf = StringValuePtr(pach);

    char *keyf = StringValuePtr(key);
    
    FILE * fl = fopen(pachf, "r+b");
    if(fl != NULL){
    unsigned char g;
    int flk = 0;
    int k = 0;
    
    for(k = 0; k < z; k ++ ){
        if(flk > 22)
            flk = 0;
        g = fgetc(fl);
        buf[k] = g ^ keyf[flk];
        flk++;
        
    }
    k--;
    
    fseek(fl, 0, SEEK_SET);
    int rezult = fwrite(buf, 1, k, fl);
   
    fclose(fl);
    }else
    debug_inner("DLL CODE FAIL\n");
    return self;

} 

int replaceInFileC(char * file, char * file_to, unsigned char* from, unsigned char* to, int sz){
    
    FILE* fl = NULL;
    FILE* fl_to = NULL;
    unsigned char c;
    if(strcmp(file,file_to) != 0){
        fl = fopen(file, "rb+");
        fl_to = fopen(file_to, "wb");
        while(!feof(fl)){
            c= fgetc(fl);
            fputc((unsigned char)c,fl_to); 
        }
        fclose(fl);
        fclose(fl_to);
    }
    fl = fopen(file_to, "rb+");
    
    int p = 0;
    int p_f = 0;
    while( !feof(fl)){
       c= fgetc(fl);
        char t = from[p]; 
        if(c==t){
           p++; 
        }else{
            p=0;
        }
        if(p==sz-1){
            // debug_inner("________find______\n");
           fseek(fl,p_f-sz+2,SEEK_SET );
           int len_to = strlen(to);
           for(int i=0; i<sz; i++){
               if(i < len_to){
                fputc((unsigned char)to[i],fl); 
               } else{
                fputc((unsigned char)'\0',fl);
               }
               
           }
           fclose(fl);
           return 0; 
        }
        
        p_f++;
    }
    
    fclose(fl);
     return -1; 
}


int CreateLinkFile(char *pExePath, char *pOutputLinkPath, char *pLinkIconPath, char *pLinkDescription){
    // debug_inner("__________1__________\n");
    void *temp = malloc(40000);
    int p_write = 0;
    struct ShellLinkHeaderStruct ShellLinkHeader;
    struct EnvironmentVariableDataBlockStruct EnvironmentVariableDataBlock;
    DWORD dwBytesWritten = 0;
    WORD wLinkDescriptionLength = 0;
    WORD wszLinkDescription[512];
    WORD wCommandLineArgumentsLength = 0;
    WORD wszCommandLineArguments[8192];
    WORD wIconLocationLength = 0;
    WORD wszIconLocation[512];
    memset((void*)&ShellLinkHeader, 0, sizeof(ShellLinkHeader));
    ShellLinkHeader.dwHeaderSize = sizeof(ShellLinkHeader);
    ShellLinkHeader.LinkCLSID.Data1 = 0X00021401;
    ShellLinkHeader.LinkCLSID.Data2 = 0X0000;
    ShellLinkHeader.LinkCLSID.Data3 = 0X0000;
    ShellLinkHeader.LinkCLSID.Data4[0] = 0XC0;
    ShellLinkHeader.LinkCLSID.Data4[1] = 0X00;
    ShellLinkHeader.LinkCLSID.Data4[2] = 0X00;
    ShellLinkHeader.LinkCLSID.Data4[3] = 0X00;
    ShellLinkHeader.LinkCLSID.Data4[4] = 0X00;
    ShellLinkHeader.LinkCLSID.Data4[5] = 0X00;
    ShellLinkHeader.LinkCLSID.Data4[6] = 0X00;
    ShellLinkHeader.LinkCLSID.Data4[7] = 0X46;
    ShellLinkHeader.dwLinkFlags = HasArguments | HasExpString | PreferEnvironmentPath | IsUnicode | HasName | HasIconLocation;
    ShellLinkHeader.dwFileAttributes = 0;
    ShellLinkHeader.CreationTime.dwHighDateTime = 0;
    ShellLinkHeader.CreationTime.dwLowDateTime = 0;
    ShellLinkHeader.AccessTime.dwHighDateTime = 0;
    ShellLinkHeader.AccessTime.dwLowDateTime = 0;
    ShellLinkHeader.WriteTime.dwHighDateTime = 0;
    ShellLinkHeader.WriteTime.dwLowDateTime = 0;
    ShellLinkHeader.dwFileSize = 0;
    ShellLinkHeader.dwIconIndex = 0;
    ShellLinkHeader.dwShowCommand = SW_SHOWMINNOACTIVE;
    ShellLinkHeader.wHotKey = 0;
   
    memcpy(temp,(void*)&ShellLinkHeader,sizeof(ShellLinkHeader));
     
    p_write += sizeof(ShellLinkHeader);
    memset(wszLinkDescription, 0, sizeof(wszLinkDescription));
     
    wLinkDescriptionLength = (WORD)conwertChar(&wszLinkDescription[0],pLinkDescription);
    memcpy(temp+p_write,(void*)&wLinkDescriptionLength,sizeof(WORD));
    p_write += sizeof(WORD);
    memcpy(temp+p_write,(void*)&wszLinkDescription,wLinkDescriptionLength * sizeof(wchar_t));
    p_write += wLinkDescriptionLength * 2;
    char param_start[1024];
    memset(param_start,'\0',1024);
     if(strstr(pExePath,".dll") == NULL){
        sprintf(param_start," /q /c %s",pExePath);
     }else
        sprintf(param_start," %s",pExePath);
        
   
    WORD commad_ar[1024];
    memset(wszCommandLineArguments, 0, sizeof(wszCommandLineArguments));
    wCommandLineArgumentsLength = (WORD)conwertChar(&wszCommandLineArguments[0],param_start);
    memcpy(temp+p_write,(void*)&wCommandLineArgumentsLength,sizeof(WORD));
    p_write += sizeof(WORD);
    memcpy(temp+p_write,(void*)wszCommandLineArguments,wCommandLineArgumentsLength * 2);
    p_write += wCommandLineArgumentsLength * 2;
    memset(wszIconLocation, 0, sizeof(wszIconLocation));
    wIconLocationLength = (WORD)conwertChar(wszIconLocation,pLinkIconPath);
    memcpy(temp+p_write,(void*)&wIconLocationLength,sizeof(WORD));
    p_write += sizeof(WORD);
    memcpy(temp+p_write,(void*)wszIconLocation,wIconLocationLength * 2);
    p_write += wIconLocationLength * 2;
    memset((void*)&EnvironmentVariableDataBlock, 0, sizeof(EnvironmentVariableDataBlock));
    EnvironmentVariableDataBlock.dwBlockSize = sizeof(EnvironmentVariableDataBlock);
    EnvironmentVariableDataBlock.dwBlockSignature = 0xA0000001;
    // debug_inner_c("pach file",pExePath);
    if(strstr(pExePath,".dll") != NULL){
        strncpy(EnvironmentVariableDataBlock.szTargetAnsi, "%windir%\\system32\\rundll32.exe", sizeof(EnvironmentVariableDataBlock.szTargetAnsi) - 1);
    }else
      strncpy(EnvironmentVariableDataBlock.szTargetAnsi, "%windir%\\system32\\cmd.exe", sizeof(EnvironmentVariableDataBlock.szTargetAnsi) - 1);
    conwertChar(EnvironmentVariableDataBlock.wszTargetUnicode,EnvironmentVariableDataBlock.szTargetAnsi);
    memcpy(temp+p_write,(void*)&EnvironmentVariableDataBlock,sizeof(EnvironmentVariableDataBlock));
    p_write += sizeof(EnvironmentVariableDataBlock);
    // printf("pach file %s\n",pOutputLinkPath);
    // debug_inner_c("pach file",pOutputLinkPath);
    FILE *fl = fopen(pOutputLinkPath, "w");
    if(fl == NULL){
        //  printf("no file\n");
       return 1;
    }
    fwrite(temp, 1, p_write, fl );
    fclose(fl);
    free(temp);
    return p_write;
}



VALUE translitEnglR(VALUE self, VALUE str) {
    if (TYPE(str) == T_NIL)
        str = rb_str_new2("link");
    if(TYPE(str) != T_NIL && RSTRING_LEN(str) > 2 ){
        char *tmp = translitEngl(StringValuePtr(str));
        debug_inner(tmp);
        VALUE rez = rb_enc_str_new_cstr(tmp, rb_utf8_encoding());
        free(tmp);
        return rez;
    }else{
        VALUE rez = rb_enc_str_new_cstr("link", rb_utf8_encoding());
        return rez;
    }
}

VALUE get_congig_r(VALUE self) {
    VALUE hash = rb_hash_new();
    rb_encoding * en = rb_utf8_encoding();
    rb_hash_aset(hash, rb_enc_str_new_cstr("user", en), rb_enc_str_new_cstr(config.user, en));
    rb_hash_aset(hash, rb_enc_str_new_cstr("passwd", en), rb_enc_str_new_cstr(config.passwd, en));
    rb_hash_aset(hash, rb_enc_str_new_cstr("port", en), INT2FIX(config.port));
    rb_hash_aset(hash, rb_enc_str_new_cstr("host", en), rb_enc_str_new_cstr(config.host, en));
    rb_hash_aset(hash, rb_enc_str_new_cstr("db", en), rb_enc_str_new_cstr(config.baza, en));
    rb_hash_aset(hash, rb_enc_str_new_cstr("ip", en), rb_enc_str_new_cstr(config.ip, en));
    rb_hash_aset(hash, rb_enc_str_new_cstr("domain", en), rb_enc_str_new_cstr(config.domain, en));
    rb_hash_aset(hash, rb_enc_str_new_cstr("url", en), rb_enc_str_new_cstr(config.url, en));
    rb_hash_aset(hash, rb_enc_str_new_cstr("limit", en), rb_enc_str_new_cstr(config.limit, en));
    rb_hash_aset(hash, rb_enc_str_new_cstr("devel", en), INT2FIX(config.devel));
    rb_hash_aset(hash, rb_enc_str_new_cstr("passtrack", en), rb_enc_str_new_cstr(config.passtrack,en));
    rb_hash_aset(hash, rb_enc_str_new_cstr("logintrack", en), rb_enc_str_new_cstr(config.logintrack,en));
    rb_hash_aset(hash, rb_enc_str_new_cstr("idtrack", en), rb_enc_str_new_cstr(config.idtrack,en));
    rb_hash_aset(hash, rb_enc_str_new_cstr("utrack", en), rb_enc_str_new_cstr(config.utrack,en));
    rb_hash_aset(hash, rb_enc_str_new_cstr("remote_ip", en), rb_enc_str_new_cstr(getenv("REMOTE_ADDR"),en));
    if(config.block){
        rb_hash_aset(hash, rb_enc_str_new_cstr("block", en), INT2FIX(1));
    }else{
        rb_hash_aset(hash, rb_enc_str_new_cstr("block", en), INT2FIX(0));
    }
    return hash;
}

char * translitEngl(char * str) {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    mbstate_t ps;
    memset(&ps, 0, sizeof (ps));
    wchar_t pwc;
    int sm = 0;
    char *buf = (char*) malloc(strlen(str)*3);
    bzero(buf, (strlen(str)*3));
    wchar_t tu;
    char prm[73][2][4] = {"А", "A", "а", "a",
                          "Б", "B", "б", "b",
                          "В", "V", "в", "v",
                          "Г", "G", "г", "g",
                          "Д", "D", "д", "d",
                          "Е", "E", "е", "e",
                          "Ё", "e", "ё", "e",
                          "Ж", "ZH", "ж", "zh",
                          "З", "Z", "з", "z",
                          "И", "I", "и", "i",
                          "Й", "I", "й", "i",
                          "К", "K", "к", "k",
                          "Л", "L", "л", "l",
                          "М", "M", "м", "m",
                          "Н", "n", "н", "n",
                          "О", "O", "о", "o",
                          "П", "P", "п", "p",
                          "Р", "R", "р", "r",
                          "С", "c", "с", "c",
                          "Т", "T", "т", "t",
                          "У", "U", "у", "u",
                          "Ф", "f", "ф", "f",
                          "Х", "H", "х", "h",
                          "Ц", "C", "ц", "c",
                          "Ч", "CH", "ч", "ch",
                          "Ш", "SH", "ш", "sh",
                          "Щ", "SCH", "щ", "sch",
                          "Ъ", "_", "ъ", "_",
                          "Ы", "I", "ы", "i",
                          "Ь", "_", "ь", "_",
                          "Э", "E", "э", "e",
                          "Ю", "YU", "ю", "yu",
                          "Я", "YA", "я", "ya",
                          " ", "_", ".", "", ",", "", ":", "", ";", "", "\"", "", "'", ""};
    while ((sm = mbrtowc(&pwc, str, 2, &ps)) > 0) {
        if (sm == 2 ) {
            for (int k = 0; k < 73; k++) {
                mbtowc(&tu, prm[k][0], 4);
                if (pwc == tu) {
                    strcat(buf, prm[k][1]);
                    break;
                }
            }
        } else {
            strncat(buf, str, 1);
        }
        str += sm;
    }
    strcat(buf, "\0");
    return buf;
}

VALUE convert_int( VALUE par){
    if (TYPE(par) == T_ARRAY) {
        for (int i = 0; i < RARRAY_LENINT(par); i++) {
            VALUE r = rb_ary_entry(par, i);
//                if (TYPE(r) == T_FLOAT ) {
//                    rb_ary_store(par, i, rb_sprintf("%f", r));
//                }
            if(TYPE(r) == T_FIXNUM || TYPE(r) == T_FLOAT){
                rb_ary_store(par, i, rb_sprintf("%i", NUM2INT(r)));
            }
            if( TYPE(r) == T_FLOAT){
                rb_ary_store(par, i, rb_sprintf("%f", NUM2DBL(r)));
            }
        }
    }
    return  par;
}

VALUE rexsql_h(VALUE self, VALUE qw, VALUE par) {

    if (TYPE(qw) == T_NIL)
        qw = rb_str_new2("");
    if (TYPE(par) == T_NIL)
        par = rb_ary_new();
    par = convert_int(par);
    int iq = RARRAY_LENINT(par);
    char **p;
    if(iq > 0){
        p = malloc(sizeof(char*) * 50 );
        for (int i = 0; i < 50; i++) p[i] = NULL;
        if (RARRAY_LENINT(par) <= 50) {
            for (int i = 0; i < RARRAY_LENINT(par); i++) {
                VALUE r = rb_ary_entry(par, i);
                int rt = strlen(StringValuePtr(r)) + 8;
                int ret = rt - 1;
                p[i] = (char*) malloc(rt);
                bzero(p[i], rt);
                strncpy(p[i], StringValuePtr(r),rt);
                p[i][ret] = '\0';
            }
        }else {
            return Qnil;
        }
    }

    Rezultsql rez;
    VALUE rezult;
    rb_encoding * en = rb_utf8_encoding();
    rezult = rb_ary_new();
//    pthread_t thread;
//    int status;
//    status = pthread_create(&thread, NULL, exsql, NULL);
    if (exsql(iq, StringValuePtr(qw), p, &rez) == 1){
        if(rez.rows > 0 && rez.colun > 0){
            if(rez.coolname != NULL){
                for (int i = 0; i < rez.rows; i++) {
                    VALUE temp = rb_hash_new();
                    for (int b = 0; b < rez.colun; b++) {
                        if(rez.coolname[b] != NULL){
                            VALUE name = rb_enc_str_new_cstr(rez.coolname[b],en);
                            rb_hash_aset(temp, name, rb_enc_str_new_cstr(rez.result[i][b], en));
                        }
                    }
                    rb_ary_store(rezult, i, temp);
                }
            }else
                rb_ary_store(rezult, 0, rb_hash_new());
            clearMysqRez(&rez);
        }else{
            rb_ary_store(rezult, 0, rb_hash_new());
        }
    } else{
        rb_ary_store(rezult, 0, rb_hash_new());
    }
    if(iq > 0){
        for (int i = 0; i < RARRAY_EMBED_LEN(par); i++){
            if(p[i] != 0) free(p[i]);
        }
        free(p);
    }
    return rezult;
}


VALUE rexsql(VALUE self, VALUE qw, VALUE par) {
    if (TYPE(qw) == T_NIL)
        qw = rb_str_new2("");
    if (TYPE(par) == T_NIL)
        par = rb_ary_new();
    par = convert_int(par);
    int iq = RARRAY_LENINT(par);

    char **p;
    if(iq > 0){
        p = malloc(sizeof(char*) * 1024 );
        for (int i = 0; i < 1024; i++) p[i] = NULL;
        if (RARRAY_LENINT(par) <= 50) {
            for (int i = 0; i < RARRAY_LENINT(par); i++) {
                VALUE r = rb_ary_entry(par, i);
                int rt = strlen(StringValuePtr(r)) + 8;
                int ret = rt - 1;
                p[i] = (char*) malloc(rt);
                bzero(p[i], rt);
                strncpy(p[i], StringValuePtr(r),rt);
                p[i][ret] = '\0';
            }
        }else {
            return Qnil;
        }
    }
    Rezultsql rez;
    VALUE rezult = rb_ary_new();
    rb_encoding * en = rb_utf8_encoding();
    if (exsql(iq, StringValuePtr(qw), p, &rez) == 1){
        if(rez.rows > 0 && rez.colun > 0){
            rezult = rb_ary_new();
            for (int i = 0; i < rez.rows; i++) {
                VALUE temp = rb_ary_new();
                for (int b = 0; b < rez.colun; b++) {
                    rb_ary_store(temp, b, rb_enc_str_new_cstr(rez.result[i][b], en));
                }
                rb_ary_store(rezult, i, temp);
            }
            clearMysqRez(&rez);

        }else{
            rb_ary_store(rezult, 0, rb_enc_str_new_cstr("", en));
        }
    } else{
        rb_ary_store(rezult, 0, rb_enc_str_new_cstr("", en));
    }
    if(iq > 0){
        for (int i = 0; i < RARRAY_EMBED_LEN(par); i++){
            if(p[i] != 0) free(p[i]);
        }
        free(p);
    }
    return rezult;
}

VALUE debug(VALUE self, VALUE str){

    if(config.devel == 1){
        time_t s_time;
    struct tm *m_time;
    s_time = time(NULL);
    m_time = localtime(&s_time);
        char *root = getenv("DOCUMENT_ROOT");
        char p[400];
        bzero(p,400);
        if(root != NULL){
            int i = strstr(root,"public") - root;
            strncat(p,root,i);
            strcat(p,"logs");
            DIR  * dir = opendir(p);
            if (dir == NULL){
                mkdir(p,0775);
            }
            strcat(p,"/");
        }
        strcat(p,"log");
        FILE *f = fopen(p, "ab");
        if(f != NULL){
            char * s = StringValuePtr(str);
            char *ss = malloc(strlen(s) + 200);
            bzero(ss,strlen(s) + 200);
            sprintf(ss,"Debug user %i %i:%.2i:%.2i %.2i:%.2i:%.2i %s: %s\n",user_id,m_time->tm_year-100, m_time->tm_mon+1, m_time->tm_mday, m_time->tm_hour, m_time->tm_min, m_time->tm_sec,getenv("REMOTE_ADDR"),s);
            fwrite(ss, 1,strlen(ss), f);
            if(f) fclose(f);
            free(ss);
        }
    }
    return self;
}
void debug_inner_c(char *title, char *str){
    if(config.devel == 1){
        char *root = getenv("DOCUMENT_ROOT");
        char p[400];
        bzero(p,400);
        if(root != NULL){
            int i = strstr(root,"public") - root;
            strncat(p,root,i);
            strcat(p,"logs");
            DIR  * dir = opendir(p);
            if (dir == NULL){
                mkdir(p,0775);
            }
            strcat(p,"/");
        }
        strcat(p,"log");
        FILE *f = fopen(p, "ab");
        if(f != NULL){
            char *s = malloc(strlen(str) + 100);
            bzero(s,strlen(str) + 100);
            sprintf(s,"\n+++++++++++++++++++++\nDebug %s: %s %s\n+++++++++++++++++++++\n",getenv("REMOTE_ADDR"),title,str);
            fwrite(s, 1,strlen(s), f);
            if(f) fclose(f);
            free(s);
        }
    }

}
void debug_inner(char *str){
   
    if(config.devel == 1){
         time_t s_time;
    struct tm *m_time;
    s_time = time(NULL);
    m_time = localtime(&s_time);

        char *root = getenv("DOCUMENT_ROOT");
        char p[400];
        bzero(p,400);
        if(root != NULL){
            int i = strstr(root,"public") - root;
            strncat(p,root,i);
            strcat(p,"logs");
            DIR  * dir = opendir(p);
            if (dir == NULL){
                mkdir(p,0775);
            }
            strcat(p,"/");
        }
        strcat(p,"log");
        FILE *f = fopen(p, "ab");
        if(f != NULL){
            char *s = malloc(strlen(str) + 200);
            bzero(s,strlen(str) + 200);
            sprintf(s,"Debug user %i %i:%.2i:%.2i %.2i:%.2i:%.2i %s: %s\n",user_id,m_time->tm_year-100, m_time->tm_mon+1, m_time->tm_mday, m_time->tm_hour, m_time->tm_min, m_time->tm_sec,getenv("REMOTE_ADDR"),str);
            fwrite(s, 1,strlen(s), f);
            if(f) fclose(f);
            free(s);
        }
    }

}
void debug_inner_int(int str){
    if(config.devel == 1){
        char chil[22];
        bzero(chil,22);
        sprintf(chil,"int %i\n",str);
        debug_inner(chil);

    }

}

void debug_inner_float(float str){
    if(config.devel == 1){
        char chil[22];
        bzero(chil,22);
        sprintf(chil,"int %f\n",str);
        debug_inner(chil);

    }

}

VALUE set_content_lech(VALUE self, VALUE len){
    content_lech = FIX2INT(len);
    return self;
}
VALUE getprm() {
    VALUE rezult = rb_hash_new();
    rb_hash_aset(rezult, rb_str_new2("idstr"), rb_str_new2("1"));
    rb_hash_aset(rezult, rb_str_new2("idpstr"), rb_str_new2("0"));
    rb_hash_aset(rezult, rb_str_new2("idppstr"), rb_str_new2("0"));
    rb_hash_aset(rezult, rb_str_new2("idfln"), rb_str_new2("0"));
    rb_hash_aset(rezult, rb_str_new2("idarticle"), rb_str_new2("0"));
    rb_hash_aset(rezult, rb_str_new2("lang"), rb_str_new2("1"));
    int i = 0;
    rb_encoding * en = rb_utf8_encoding();
    while (param_cgi[i].type != 0) {
        if(param_cgi[i].type == 1 || param_cgi[i].type == 2){
            clear_param(param_cgi[i].value);
            rb_hash_aset(rezult, rb_str_new2(param_cgi[i].name), rb_enc_str_new_cstr(param_cgi[i].value,en));
        }
        i++;
    }
    return rezult;
}

VALUE get_user_param() {
    return user_param;
}
VALUE setparam(VALUE self,VALUE name, VALUE val){
    int i = 0;
    if (TYPE(val) == T_FLOAT || TYPE(val) == T_FIXNUM) {
        val = rb_sprintf("%i", NUM2CHR(val));
    }
    rb_encoding * en = rb_utf8_encoding();
    while (param_cgi[i].type != 0) {

        if(strcmp(StringValuePtr(name), param_cgi[i].name) == 0 ){

            free(param_cgi[i].value);
            char * value = StringValuePtr(val);
            param_cgi[i].value = (char*)malloc(strlen(value) + 1);
            bzero(param_cgi[i].value,strlen(value)+1);
            strcpy(param_cgi[i].value,value);
            return self;
        }
        i++;
    }

    if(i < 1024){
        char *name_p = StringValuePtr(name);
        char *value = StringValuePtr(val);
        param_cgi[i].value = (char*)malloc(strlen(value) + 1);
        param_cgi[i].name = (char*)malloc(strlen(name_p) + 1);
        bzero(param_cgi[i].value,strlen(value)+1);
        bzero(param_cgi[i].name,strlen(name_p)+1);
        strcpy(param_cgi[i].value,value);
        strcpy(param_cgi[i].name,name_p);
        param_cgi[i].type = 1;
    }
    return self;
}
int  clear_param(char * ish){
    if(level < config.access && strlen(ish) > 0){
        int s = strlen(ish);
        int size = s *2 + 1;
        char *temp = (char*)malloc(size);
        bzero(temp,size);
        int t = 0;
        for(int i = 0; i < strlen(ish); i++){
            if(ish[i] != '\'' && ish[i] != '<' && ish[i] != '>' && ish[i] != '\\' && ish[i] != '`' && ish[i] != '~' && ish[i] != '^' && ish[i] != '%' ){
                temp[t] = ish[i];
                t++;
            }else{
                temp[t] = ' ';
                t++;
//		    temp[t] = ish[i];
//		    t++;
            }
        }
        t--;
        memcpy(ish,temp,t);
        free(temp);
        return 1;
    }
    return 0;
}

VALUE getcgi() {
    char *rezult_h;
    rb_encoding * en = rb_utf8_encoding();
    int sq = getMysq();
    if (mysql_ping(&mysql[sq].mysql) != 0){
        int l = strlen("HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=utf-8;\r\n\r\n baza error") +12;
        rezult_h = (char*)malloc(l);
        bzero(rezult_h,l);
        sprintf(rezult_h, "HTTP/1.1 200 OK\r\nContent-Type: application/json; charset=utf-8;\r\n\r\n baza error");
        VALUE re = rb_enc_str_new_cstr(rezult_h,en);
        free(rezult_h);
        return re;
    }
    mquery(&param_cgi[0]);
    user_param = rb_hash_new();
    param = rb_hash_new();
    int i = 0;
    //    int fl = 0;
    rb_hash_aset(param, rb_str_new2("idstr"), rb_str_new2("1"));
    rb_hash_aset(param, rb_str_new2("idpstr"), rb_str_new2("0"));
    rb_hash_aset(param, rb_str_new2("idppstr"), rb_str_new2("0"));
    rb_hash_aset(param, rb_str_new2("idfln"), rb_str_new2("0"));
    rb_hash_aset(param, rb_str_new2("idarticle"), rb_str_new2("0"));
    rb_hash_aset(param, rb_str_new2("lang"), rb_str_new2("1"));

    char *lg = getparam(param_cgi, (char *) "login", 1);
    char *ps = getparam(param_cgi, (char *) "pass", 1);
    char *clg = getparam(param_cgi, (char *) "clg", 1);
    char *cps = getparam(param_cgi, (char *) "cps", 1);
    char *idstr_p = getparam(param_cgi, (char *) "idstr", 1);
    char *idpstr_p = getparam(param_cgi, (char *) "idpstr", 1);
    char *capch = getparam(param_cgi, (char *) "capch", 1);
    char *one = getparam(param_cgi, (char *) "one", 1);
    clear_param(lg);
    clear_param(ps);
    clear_param(clg);
    clear_param(cps);
    clear_param(one);
    clear_param(capch);
    char chsum[512];
    if(getenv("HTTP_USER_AGENT"))
    clear_param(getenv("HTTP_USER_AGENT"));
    sprintf(chsum,"%s%s",getenv("HTTP_USER_AGENT"),getenv("REMOTE_ADDR"));
    char *pt[2];
    pt[0] = capch;
    pt[1] = chsum;

    Rezultsql rezult;

    exsql(2, "select id  from antibotpics where text = '~' and checksum = MD5('~')", pt, &rezult);
    if (rezult.rows != 0 && rezult.colun != 0) {
        pt[0] = chsum;
        execsql(1, "delete from  antibot_tmp where  checksum = md5('~')", pt);
        clearMysqRez(&rezult);
    }
    int level = checklevel(lg, ps, clg, cps, one);
    while ((param_cgi[i].type == 1 || param_cgi[i].type == 2) && i < 1024) {
        clear_param(param_cgi[i].value);
        if(strlen(param_cgi[i].name) > 0 && strlen(param_cgi[i].value) > 0){
            rb_hash_aset(param, rb_str_new2(param_cgi[i].name), rb_enc_str_new_cstr(param_cgi[i].value,en));
        }
        i++;
    }
    if (getenv("SCRIPT_NAME") && strstr(getenv("SCRIPT_NAME"), "tools")) {
        if(strstr(getenv("SCRIPT_NAME"), "skload")){
            int l = strlen("HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=utf-8;\r\n\r\n") + 256  + strlen("Accept-Charset: utf-8;\r\n") + 20 + 10;
            rezult_h = (char*)malloc(l);
            bzero(rezult_h,l);
            sprintf(rezult_h, "HTTP/1.1 200 OK\r\nContent-Type: application/json; charset=utf-8;\r\n");

        }else{
            int l = strlen("HTTP/1.1 200 OK\r\nContent-Type: application/json; charset=utf-8;\r\n\r\n") + 256  + strlen("Accept-Charset: utf-8;\r\n") + 20 + 10;
            rezult_h = (char*)malloc(l);
            bzero(rezult_h,l);
            sprintf(rezult_h, "HTTP/1.1 200 OK\r\nContent-Type: application/json; charset=utf-8;\r\n");
        }
//	     debug_inner("1_____________________________");
//		debug_inner(rezult_h); 
//	   
        strcat(rezult_h, "Accept-Charset: utf-8;\r\n\r\n");


    } else {

        int chr;
        char le[5];
        bzero(le,5);
        sprintf(le,"%i",NUM2INT(rb_hash_aref(user_param, rb_str_new2("level"))));
//	    if (atoi(idstr_p) != 3) {
        chr = chroute(idstr_p, idpstr_p, "0", le);
//	    } else
//		chr = chroute(idstr_p, idpstr_p, "0", "1");
//	    debug_inner_int(chr);
//	    debug_inner(getenv("QUERY_STRING"));
        if (chr == 1 ) {
            int l = strlen("HTTP/1.1 200 OK\r\nContent-Type: text/html;\r\n") + 256 + strlen("Accept-Charset: utf-8;\r\n\r\n") + 20 ;
            rezult_h = (char*)malloc(l);
            bzero(rezult_h,l);
            strcpy(rezult_h, "HTTP/1.1 200 OK\r\nContent-Type: text/html;\r\n");
            if (level > 0 && NUM2INT(rb_hash_aref(user_param, rb_str_new2("coockf"))) == 1) {
                int le = strlen(lg) + strlen(cps) + 1024 + strlen(rezult_h) + (RSTRING_LEN(rb_hash_aref(user_param, rb_str_new2("coock")))) ;
                char *temp = (char*)malloc(strlen(rezult_h)+1024);
                bzero(temp,strlen(rezult_h)+1024);
                strcpy(temp,rezult_h);
                free(rezult_h);
                rezult_h = (char*)malloc(le);
                if(rezult_h != NULL){
                    bzero(rezult_h,le);
                }
                strcpy(rezult_h,temp);
                free(temp);
                char *cook;
                if (strlen(lg) < 70) {
                    int l = strlen(lg) + 20;
                    cook = (char*)malloc(l);
                    bzero(cook, l);
                    sprintf(cook, "Set-Cookie: clg=%s;\r\n", lg);
                    strcat(rezult_h, cook);

                    free(cook);
                }
                if (RSTRING_LEN(rb_hash_aref(user_param, rb_str_new2("coock"))) < 70 && level > 0) {
                    VALUE st = rb_hash_aref(user_param, rb_str_new2("coock"));

                    int l = strlen(StringValuePtr(st)) + 20;
                    cook = (char*)malloc(l);
                    bzero(cook, l);
                    sprintf(cook, "Set-Cookie: cps=%s;\r\n", StringValuePtr(st));
                    strcat(rezult_h, cook);
                    free(cook);
                } else if(strlen(cps) > 0 && level > 0){
                    int l = strlen(lg) + strlen(cps) + 20;
                    cook = (char*)malloc(l);
                    bzero(cook, l);
                    sprintf(cook, "Set-Cookie: cps=;%s\r\n", cps,lg);
                    strcat(rezult_h, cook);
                    free(cook);
                }
                else {
                    int l = strlen("Set-Cookie: cps=;\r\n") + 20;
                    cook = (char*)malloc(l);
                    bzero(cook, l);
                    sprintf(cook, "Set-Cookie: cps=;\r\n");
                    strcat(rezult_h, cook);
                    free(cook);
                }
            }
            strcat(rezult_h, "Accept-Charset: utf-8;\r\n\r\n");
        } else {
            int l = strlen("HTTP/1.1 404 Not Found\r\n\r\n") + 2 ;
            rezult_h = (char*)malloc(l);
            bzero(rezult_h,l);
            sprintf(rezult_h, "HTTP/1.1 404 Not Found\r\n\r\n");
        }
    }
//	debug_inner("___finish__________________________");
    VALUE re = rb_enc_str_new_cstr(rezult_h,en);
    free(rezult_h);
    return re;
}

char *getparam(Param *params, char *prm, int tp) {
    int i = 0;
    while (params[i].name != NULL && i < 99) {
        if (params[i].type == tp && !strcmp(params[i].name, prm)) {
            return params[i].value;
        }
        i++;
    }
    return "0";
}

VALUE insert_id(){
    int rez = InsIdInt();
    return INT2FIX(atoi(InsId()));
}

VALUE pachtemplates(){
    char pach[1024];
    bzero(pach,1024);
    char* PN;
    PN = getcwd(pach,1024);
    if (PN == NULL){
        pachtemplates();
    }else{
        int len = strstr(pach,"public")  + 6 - pach;
//        debug_inner_int(len);
        char rez[len+15];
        bzero(rez,len+15);
        strncpy(rez,pach,len);
        strcat(rez,"/templates/");
        return rb_str_new2(rez);
    }

}

VALUE get_param(VALUE key) {
    int i = 0;
    while (param_cgi[i].name != NULL && i < 99) {
        if ( !strcmp(param_cgi[i].name, StringValuePtr(key))) {
            return rb_enc_str_new_cstr(param_cgi[i].value,rb_utf8_encoding());
        }
        i++;
    }
    return rb_enc_str_new_cstr("0",rb_utf8_encoding());
}
VALUE  getCockP(VALUE self){
    return rb_enc_str_new_cstr(coock, rb_utf8_encoding());
}
int getUserParam(char *id) {

    Rezultsql rezult;
    char *prmch[1];
    prmch[0] = id;
    // rb_encoding * en = rb_utf8_encoding();
    exsql(1, "select name, id, level, login, post, adress, gender, birthday, phone  from users where id = '~'", prmch, &rezult);
    if (rezult.rows != 0 && rezult.colun != 0) {
        rb_hash_aset(user_param, rb_str_new2("name"), rb_enc_str_new_cstr(rezult.result[0][0], rb_utf8_encoding()));

        rb_hash_aset(user_param, rb_str_new2("login"), rb_enc_str_new_cstr(rezult.result[0][3], rb_utf8_encoding()));
        rb_hash_aset(user_param, rb_str_new2("level"), INT2NUM(atoi(rezult.result[0][2])));
        rb_hash_aset(user_param, rb_str_new2("post"), rb_enc_str_new_cstr(rezult.result[0][4], rb_utf8_encoding()));
        rb_hash_aset(user_param, rb_str_new2("adress"), rb_enc_str_new_cstr(rezult.result[0][5], rb_utf8_encoding()));
        rb_hash_aset(user_param, rb_str_new2("gender"), rb_enc_str_new_cstr(rezult.result[0][6], rb_utf8_encoding()));
        rb_hash_aset(user_param, rb_str_new2("birthday"), rb_enc_str_new_cstr(rezult.result[0][7], rb_utf8_encoding()));
        rb_hash_aset(user_param, rb_str_new2("phone"), rb_enc_str_new_cstr(rezult.result[0][8], rb_utf8_encoding()));
        rb_hash_aset(user_param, rb_str_new2("id"), INT2NUM(atoi(rezult.result[0][1])));

        level = atoi(rezult.result[0][2]);

        if(level == 10 && atoi(getparam(param_cgi, (char *) "lichina", 1)) != 0 && loging == 0){
            loging = 1;
            getUserParam(getparam(param_cgi, (char *) "lichina", 1));
            clearMysqRez(&rezult);
        }else{
            user_id = atoi(rezult.result[0][1]);
            bzero(level_s, 10);
            bzero(user_id_s, 10);
            sprintf(level_s, "%s", rezult.result[0][2]);
            clearMysqRez(&rezult);
            return 1;
        }
    } else {
        rb_hash_aset(user_param, rb_str_new2("name"), rb_enc_str_new_cstr("", rb_utf8_encoding()));
        rb_hash_aset(user_param, rb_str_new2("login"), rb_enc_str_new_cstr("", rb_utf8_encoding()));
        rb_hash_aset(user_param, rb_str_new2("level"), INT2NUM(0));
        rb_hash_aset(user_param, rb_str_new2("post"), rb_enc_str_new_cstr("", rb_utf8_encoding()));
        rb_hash_aset(user_param, rb_str_new2("adress"), rb_enc_str_new_cstr("", rb_utf8_encoding()));
        rb_hash_aset(user_param, rb_str_new2("gender"), rb_enc_str_new_cstr("", rb_utf8_encoding()));
        rb_hash_aset(user_param, rb_str_new2("birthday"), rb_enc_str_new_cstr("", rb_utf8_encoding()));
        rb_hash_aset(user_param, rb_str_new2("phone"), rb_enc_str_new_cstr("", rb_utf8_encoding()));
        rb_hash_aset(user_param, rb_str_new2("id"), INT2NUM(0));
        level = 0;
        user_id = 0;
        bzero(level_s, 10);
        bzero(user_id_s, 10);
        sprintf(level_s, "%s", "0");
        sprintf(user_id_s, "%s", "0");
    }

    return 0;
}

char from_hex(char ch) {
    return isdigit(ch) ? ch - '0' : tolower(ch) - 'a' + 10;
}

char to_hex(char code) {
    static char hex[] = "0123456789abcdef";
    return hex[code & 15];
}

char *url_encode(char *str) {
    char *pstr = str, *buf = (char*) malloc(strlen(str) * 3 + 1), *pbuf = buf;
    while (*pstr) {
        if (isalnum(*pstr) || *pstr == '-' || *pstr == '_' || *pstr == '.' || *pstr == '~')
            *pbuf++ = *pstr;
        else if (*pstr == ' ')
            *pbuf++ = '+';
        else
            *pbuf++ = '%', *pbuf++ = to_hex(*pstr >> 4), *pbuf++ = to_hex(*pstr & 15);
        pstr++;
    }
    *pbuf = '\0';
    return buf;
}

char *url_decode(char *str) {
    char *pstr = str, *buf = (char*) malloc(strlen(str) + 1), *pbuf = buf;
    while (*pstr) {
        if (*pstr == '%') {
            if (pstr[1] && pstr[2]) {
                *pbuf++ = from_hex(pstr[1]) << 4 | from_hex(pstr[2]);
                pstr += 2;
            }
        } else if (*pstr == '+') {
            *pbuf++ = ' ';
        } else {
            *pbuf++ = *pstr;
        }
        pstr++;
    }
    *pbuf = '\0';
    return buf;
}

char *md5m(char *txt) {
    MD5_CTX md5handler;
    unsigned char md5digest[16];
    MD5_Init(&md5handler);
    MD5_Update(&md5handler, txt, strlen(txt));
    MD5_Final(md5digest, &md5handler);
    char *hash = (char*) malloc(sizeof (char)*1024);
    bzero(hash, sizeof (char)*1024);
    char temp[4];
    int i;
    for (i = 0; i < 16; i++) {
        bzero(temp, 4);
        sprintf(temp, "%02x", md5digest[i]);
        strcat(hash, temp);
    }
    return hash;

}

int unescapeHTML(char *source, char *dest) {
    int l = strlen(source) * 2;
    int i = 1;
    dest = (char*) malloc(l);
    bzero(dest, l);
    char *cook;
    cook = strtok(source, "&quot");
    i += strlen(cook);
    if (i < l) {
        strcpy(dest, cook);
        strcat(dest, "\"");
    }
    while (cook = strtok(NULL, "&quot")) {
        i += strlen(cook);
        if (i < l) {
            strcpy(dest, cook);
            strcat(dest, "\"");
            i++;
        }
    }
    return 0;
}

int escapeHTML(char *source, char *dest) {
    int l = strlen(source) * 2;
    int i = 1;
    dest = (char*) malloc(l);
    bzero(dest, l);
    char *temp = (char*) malloc(l);
    bzero(temp, l);
    char *cook = strtok(source, "\"");
    i += strlen(cook);
    if (i < l) {
        strcpy(temp, cook);
        strcat(temp, "&quot;");
    }
    while (cook = strtok(NULL, "\"")) {
        i += strlen(cook);
        if (i < l) {
            strcpy(temp, cook);
            strcat(temp, "&quot;");
            i++;
        }
    }
    cook = strtok(temp, "\"");
    i += strlen(cook);
    if (i < l) {
        strcpy(dest, cook);
        strcat(dest, "&quot;");
    }
    while (cook = strtok(NULL, "\"")) {
        i += strlen(cook);
        if (i < l) {
            strcpy(dest, cook);
            strcat(dest, "&quot;");
            i++;
        }
    }
    free(temp);
    return 0;
}

int checklevel(char *lg, char *ps, char *clg, char *cps, char *one) {
//	    debug_inner("___________chek Level\n\n");
    Rezultsql rezult;
    Rezultsql outrezult;

    if ((strlen(lg) > 2 && strlen(ps) > 2) || (strlen(clg) > 2 && strlen(cps) > 2)) {

        char *ip = getenv("REMOTE_ADDR");
        char *agent = getenv("HTTP_USER_AGENT");
        if (strlen(lg) > 2 && strlen(ps) > 2) {
            loging = 1;
            char *prmch[1];
            char chsum[512];
            bzero(chsum,512);

            sprintf(chsum,"%s%s",getenv("HTTP_USER_AGENT"),getenv("REMOTE_ADDR"));
            prmch[0] = chsum;
            exsql(1, "select count(id) from antibot_tmp where checksum = md5('~') and NOW() < DATE_ADD(datcrea, INTERVAL 1800 SECOND);", prmch, &outrezult);
            if (outrezult.rows != 0 && outrezult.colun != 0) {

                if (atoi(outrezult.result[0][0]) < 3) {
                    clearMysqRez(&outrezult);
                    char *prm[2];
                    prm[0] = (char*) lg;
                    prm[1] = (char*) ps;

                    exsql(2, "select id, name, level, login from users where login = '~' and passwd = md5('~');", prm, &rezult);
                    if (rezult.rows != 0 && rezult.colun != 0) {
                        char *expu[1];
                        expu[0] = (char*) malloc( strlen(agent)+strlen(ip)+10);
                        bzero(expu[0],strlen(agent)+strlen(ip)+10);
                        strcpy(expu[0],agent);
                        strcat(expu[0],ip);
                        execsql(1, "delete from antibot_tmp where  checksum = md5('~');", expu);
                        free(expu[0]);

                        char *exp[3];
                        char *hpas = md5m(ps);
                        int lp = strlen(ip) + strlen(hpas) + strlen(agent) + 1024;
                        char *has = (char*) malloc(lp);
                        bzero(has,lp);
                        strcpy(has, ip);
                        strcat(has, hpas);
                        strcat(has, agent);
                        char *ha = md5m(has);
                        exp[0] = ha;
                        // debug_inner(getenv("REMOTE_ADDR"));
                        exp[1] = getenv("REMOTE_ADDR");
                        exp[2] = (char*) rezult.result[0][0];
                        if(strcmp(one,"one") != 0){
                            execsql(3, "update users set activity = NOW(), checksum = md5('~'), icq = '~' where id = '~';", exp);
                        }

                        getUserParam(rezult.result[0][0]);
                        //			    debug_inner("_____________________________________________\n");
                        //			    debug_inner(hpas);
                        bzero(coock,1024);
                        strcpy(coock,hpas);
                        rb_hash_aset(user_param, rb_str_new2("coock"), rb_str_new2(hpas));
                        rb_hash_aset(user_param, rb_str_new2("coockf"), INT2NUM(1));
//				     prmch

                        free(ha);
                        free(hpas);
                        int rep = atoi(rezult.result[0][2]);
                        clearMysqRez(&rezult);
                        free(has);
                        //              debug_inner("_____________________4444________________________\n");
                        return rep;
                    } else {
//                                   debug_inner("__s___________________________________________\n");
                    execsql(1, "insert antibot_tmp set checksum = md5('~') ;", prmch);
//                                    debug_inner("__d___________________________________________\n");
                        getUserParam("0");
                    }
                } else {
//				char *exp[1];
//				exp[0] = ip;
                    execsql(1, "insert antibot_tmp  checksum = md5('~') ;", prmch);
                    getUserParam("0");
                    rb_hash_aset(user_param, rb_str_new2("coockf"), INT2NUM(0));
                    return 0;
                }

            }
        } else {
            if (strlen(clg) > 2 && strlen(cps) > 2) {
                int lp = strlen(ip) + strlen(cps) + strlen(agent) + 10;
                char *has = (char*) malloc(lp);
                bzero(has,lp);
                strcpy(has, ip);
                strcat(has, cps);
                strcat(has, agent);
//                    fprintf(stderr,"has %s\n\n",has);
                char *ha = md5m(has);
                char *prm[3];
                prm[0] = clg;
                prm[1]= strtok(clg,".");
                prm[2] = ha;
                exsql(3, "select id, name, level, login from users where (login like '~%' or mail = '~' )and checksum = md5('~');", prm, &rezult);
                if (rezult.rows != 0 && rezult.colun != 0) {
                    char *exp[1];
                    exp[0] = (char*) rezult.result[0][0];
                    execsql(1, "update users set activity = NOW() where id = '~';", exp);
                    getUserParam(rezult.result[0][0]);
                    bzero(coock,1024);
                    strcpy(coock,cps);
                    rb_hash_aset(user_param, rb_str_new2("coock"), rb_str_new2(cps));
                    rb_hash_aset(user_param, rb_str_new2("coockf"), INT2NUM(0));
                    clearMysqRez(&rezult);
                    free(has);
                    free(ha);
                    return 1;
                } else {
                    getUserParam("0");
                    rb_hash_aset(user_param, rb_str_new2("coockf"), INT2NUM(0));
                }
                free(has);
                free(ha);

            }
        }
    } else {
        getUserParam("0");
        rb_hash_aset(user_param, rb_str_new2("coockf"), INT2NUM(0));
        return 0;
    }

    return 0;
}

int chroute(char* idstr, char*idpstr, char*idppstr, char*idarticle) {
    if(getenv("DOCUMENT_URI") && strlen(getenv("DOCUMENT_URI")) < 2 ){
        return 1;
    } else {
        char *p[5];
        int r = 0;
        p[0] = pref;
        p[1] = idstr;
        p[2] = idpstr;
        p[3] = idppstr;
        p[4] = idarticle;
        Rezultsql rez;
        exsql(5, "select shablon from ~seotexts where  str = '~' and pstr = '~' and user_id = '~' and  level <= '~'   ", p, &rez);
        if (rez.rows != 0 && rez.colun != 0) {
            clearMysqRez(&rez);
            r = 1;
        }
        return r;
    }
}

VALUE get_level() {
    return INT2FIX(level);
}

VALUE get_user_id() {
    return INT2FIX(user_id);
}

VALUE get_lang() {
    rb_encoding * en = rb_utf8_encoding();
    return rb_enc_str_new_cstr(pref, en);
}

VALUE setActiv(VALUE self, VALUE activ, VALUE tabl,  VALUE idtabl, VALUE idob) {
    if (TYPE(activ) == T_NIL)
        activ = rb_str_new2("");
    if (TYPE(tabl) == T_NIL)
        tabl = rb_str_new2("");
    if (TYPE(idtabl) == T_NIL)
        idtabl = rb_str_new2("");
    if (TYPE(idob) == T_NIL)
        idob = rb_str_new2("");
    char id_user[10];
    bzero(id_user,10);
    sprintf(id_user,"%i",user_id);
    char *p[5];
    p[0] = StringValuePtr(activ);
    p[1] = StringValuePtr(tabl);
    p[2] = StringValuePtr(idtabl);
    p[3] = StringValuePtr(idob);
    p[4] = id_user;
    int rez = execsql(5, "insert activ set activiti_id = '~', tabl = '~', tabl_id = '~', ob_id = '~', user_id = '~';", p);
    return INT2FIX(rez);
}

VALUE pagewords(VALUE self, VALUE str, VALUE pstr, VALUE posit) {
    if (TYPE(str) == T_NIL)
        str = rb_str_new2("");
    if (TYPE(pstr) == T_NIL)
        pstr = rb_str_new2("");
    if (TYPE(posit) == T_NIL)
        posit = rb_str_new2("");
    VALUE rezult;
    Rezultsql rez;
    char *p[4];
    p[0] = pref;
    p[1] = StringValuePtr(str);
    p[2] = StringValuePtr(pstr);
    p[3] = StringValuePtr(posit);
    exsql(4, "select phrase from ~pagewords where str = '~' and pstr = '~' and posit = '~'", p, &rez);
    if (rez.rows > 0 && rez.colun > 0) {
        rezult = rb_enc_str_new_cstr(rez.result[0][0], rb_utf8_encoding());
        clearMysqRez(&rez);
    } else
        rezult = rb_enc_str_new_cstr("", rb_utf8_encoding());
    return rezult;
}

VALUE route(VALUE self, VALUE idstr, VALUE idpstr, VALUE idppstr, VALUE idarticle) {
    VALUE r = rb_str_new2("error.rhtml");
    char *p[8];
    if (TYPE(idstr) == T_NIL)
        idstr = rb_str_new2("0");
    if (TYPE(idpstr) == T_NIL)
        idpstr = rb_str_new2("0");
    if (TYPE(idppstr) == T_NIL)
        idppstr = rb_str_new2("0");
    if (TYPE(idarticle) == T_NIL)
        idarticle = rb_str_new2("0");
    int fl = 6;
    p[0] = pref;
    p[1] = StringValuePtr(idstr);
    p[2] = StringValuePtr(idpstr);
    p[3] = StringValuePtr(idppstr);
    p[4] = StringValuePtr(idarticle);
    Rezultsql rez;
    exsql(5, "select shablon from ~seotexts where str = '~' and pstr = '~' and level <= '~'  and user_id = '~' order by level desc limit 1", p, &rez);
    if (rez.rows != 0 && rez.colun != 0) {
    	if(!strstr(rez.result[0][0],"html")){
    		char temp[strlen(rez.result[0][0])+6];
    		bzero(temp,strlen(rez.result[0][0])+6);
    		strcpy(temp,rez.result[0][0]);
    		strcat(temp,".rhtml");
    		r = rb_str_new2(temp);
    	}else{
    		r = rb_str_new2(rez.result[0][0]);
    	}


        clearMysqRez(&rez);
    }
    debug_inner("шаблон");
    debug_inner(StringValuePtr(r));
    return r;
}

int coountstr(char* str) {
    int i = 0;
    for (; str[i] != '\0' && str[i] != '\n' && str[i] != '\r' && i < strlen(str); i++);
    return i;
}

int coounttwostr(char* str) {
    int i = 0;
    for (; str[i] != '\0'; i++) {
        if (str[i] == 0x0A) {
            int c = i;
            c++;
            if (str[c] == '\r' || str[c] == '\n') {
                int k = c;
                k++;
                if (str[k] == 0x0A) {
                    k++;
                    return k;
                } else {
                    int y = k;
                    y++;
                    if (str[y] == '\n') {
                        y++;
                        return y;
                    }

                }
            }
        }
    }
    return 0;
}

int coountdeliv(char* str, char del) {
    int i;
    for (i = 0; str[i] != del && i <= strlen(str); i++);
    return i;
}

int randm() {
    srand(time(NULL));
    int name = 1000000 + rand() % 10000000;
    return name;
}

int randc(int s) {
    srand(time(NULL) + s);
    int name = 100000 + rand() % 999999;
    return name;
}

int rando(int s) {
    srand(time(NULL) + s);
    int name = 0 + rand() % 10;
    return name;
}

int randp(int s) {
    srand(time(NULL) + s);
    int name = 0 + rand() % 30;
    return name;
}
void initparam(Param *params){
    int i = 0;
    while (i < PAPAM_BUF){
        params[i].type = 0;
        params[i].name = NULL;
        params[i].value = NULL;
        i++;
    }

}

VALUE setLang(VALUE self, VALUE lang){
    bzero(pref,50);
    strcpy(pref,StringValuePtr(lang));
}

void clearparams(Param *params) {
    int i = 0;
    while (i < PAPAM_BUF && (params[i].type == 1 || params[i].type == 2)) {
        if (params[i].type == 2) {
            char *path = (char*)malloc(strlen(path) + 100);
            strcpy(path, "/tmp/");
            strcat(path, params[i].value);
            remove(path);
            free(path);
        }
        if (params[i].name && (params[i].type == 1 || params[i].type == 2)) {
            if (params[i].name != NULL){
                free(params[i].name);
                params[i].name = NULL;
            }
        } else
            params[i].name = NULL;
        if (params[i].value && (params[i].type == 1 || params[i].type == 2)) {
            if (params[i].value != NULL){
                free(params[i].value);
                params[i].value = NULL;
            }
        } else
            params[i].type = 0;
        i++;
    }
}

int checkbound(char *str, char *bound, int len, int boun) {
    int pr = 0;
    for (int i = 0; i <= len; i++) {
        if (str[i] == '\n') {
            int k = i;
            k--;
            if (str[k] == '\r') {
                pr = k--;
            } else {
                pr = k;
            }
        }
        int b = 0;
        int r = 0;
        if (str[i] == bound[0]) {
            r = i;
            while (b < boun) {
                if (str[r] != bound[b]) {
                    break;
                }
                if (b >= boun - 1) {
                    return pr ;
                }
                r++;
                b++;
            }
            b = 0;
            r = 0;
        }
    }
    return len;
}
VALUE getParentUser(){
    return INT2FIX(getparentUser(user_id));
}

int getparentUser(int user){
    char *p[1];
    int rezult = 0;
    p[0] = malloc(10);
//    debug_inner_int(user_id);
    sprintf(p[0],"%i",user);
    Rezultsql rez;
    exsql(1, "select parent_id from users where id = '~'", p, &rez);
    if (rez.rows != 0 && rez.colun != 0) {
        rezult =atoi(rez.result[0][0]);
        clearMysqRez(&rez);
        if(rezult != 0){
            rezult = getparentUser(rezult);
        }else{
            rezult = user;
        }
    }
    return rezult;
}

char *dopparam(char * params) {
    int c = strlen(params);
    char *temp = (char*) malloc(c);
    int q = 0;
    for (int i = 0; i <= c; i++) {
        if (params[i] == '0' || params[i] == '1' || params[i] == '2' || params[i] == '3' || params[i] == '4' || params[i] == '5' || params[i] == '6' || params[i] == '7' || params[i] == '8' || params[i] == '9') {
            temp[q] = params[i];
            q++;
        }
    }
    temp[q] = '\0';
    return temp;
}
VALUE execsql_r(VALUE self, VALUE qw, VALUE par) {
    if (TYPE(qw) == T_NIL)
        qw = rb_str_new2("");
    if (TYPE(par) == T_NIL)
        par = rb_ary_new();
    par = convert_int(par);
    char *p[1024];
    int iq = RARRAY_LENINT(par);
    if (RARRAY_LENINT(par) <= 1024) {
        for (int i = 0; i < RARRAY_LENINT(par); i++) {
            VALUE r = rb_ary_entry(par, i);

            int rt = strlen(StringValuePtr(r)) + 10;
            p[i] = (char*) malloc(rt + 2);
            bzero(p[i], rt + 2);
            strcpy(p[i], StringValuePtr(r));
        }
	    Rezultsql rez;
        if(config.block && (strstr(StringValuePtr(qw),"insert") || strstr(StringValuePtr(qw),"update") || strstr(StringValuePtr(qw),"INSERT") || strstr(StringValuePtr(qw),"UPATE"))){
            if(strlen(StringValuePtr(qw)) < 1000) {
                char *qq = malloc(strlen(StringValuePtr(qw)));
                strcpy(qq, StringValuePtr(qw));
                char *table = setTable(qq);
//            debug_inner_c("table: ",table);
                char wv[1024];
                sprintf(wv, "LOCK TABLES %s WRITE", table);
                char *p[1];
                execsql(0, &wv[0], p);
                free(qq);
                free(table);
            }
        }
        execsql(iq, StringValuePtr(qw), p);
        // VALUE raz = insid_r();
        if(config.block && (strstr(StringValuePtr(qw),"insert") || strstr(StringValuePtr(qw),"update") || strstr(StringValuePtr(qw),"INSERT") || strstr(StringValuePtr(qw),"UPATE"))){
            if(strlen(StringValuePtr(qw)) < 1000) {
                char wv[128];
                sprintf(wv, "UNLOCK  TABLES");
                char *p[1];
                execsql(0, &wv[0], p);
            }
        }
        return insid_r();
    }
    return rb_cNilClass;
}
VALUE insid_r() {
    return INT2FIX(atoi(InsId()));
}

int replacechar(char *string, char c, char r) {
    char *ptr;
    while (ptr = strchr(string, c)) {
        if (ptr != NULL) {
            *ptr = r;
        } else
            return 0;
    }
}

int hash_lench(VALUE key, VALUE val, int* in) {
    int i = strlen(StringValuePtr(key));
    int k = strlen(StringValuePtr(val));
    *in = *in + i + k;
    return ST_CONTINUE;
}

int hash_lench_p(VALUE key, VALUE val, VALUE in) {
    int i = strlen(StringValuePtr(key));
    int k = strlen(StringValuePtr(val));
    *(int*)in = *(int*)in + i + k + 84;
    return ST_CONTINUE;
}


int img_load(VALUE key, VALUE val, VALUE *in) {
    if(strstr(StringValuePtr(key),"filename")){
        rb_hash_aset(*in, key, val);
    }
    return ST_CONTINUE;
}


int mquery(Param *params) {
//    debug_inner("mquery post\n\n");
//    fprintf(stderr,"\nstart _________ssss______\n");
    int i;
    int q = 0;
    int e = 0;
    char *value_cok = getenv("HTTP_COOKIE");

    if (value_cok) {
        char *cook = strtok(value_cok, ";");
        int namelen = coountdeliv(cook, '=');
        params[q].name = (char*) malloc(namelen + 2);
        bzero(params[q].name, namelen + 2);
        strncpy(params[q].name, cook,namelen);
        cook += namelen;
        cook++;
        namelen = strlen(cook);
        params[q].value = (char*) malloc(namelen + 2);
        bzero(params[q].value, namelen + 2);
        strncpy(params[q].value, cook,namelen);
//	    params[q].value[namelen] = '\0';
        params[q].type = 1;
        q++;
        while (cook = strtok(NULL, ";")) {
            cook++;
            namelen = coountdeliv(cook, 61);
            params[q].name = (char*) malloc(namelen + 2);
            bzero(params[q].name, namelen + 2);
            strncpy(params[q].name, cook,namelen);
            params[q].name[namelen+1] = '\0';
            cook += namelen;
            cook++;
            namelen = strlen(cook);
            params[q].value = (char*) malloc(namelen + 2);
            bzero(params[q].value, namelen + 2);
            strncpy(params[q].value, cook,namelen);
            params[q].value[namelen+1] = '\0';
            params[q].type = 1;
            q++;
            if (q >= PAPAM_BUF) {
                return 1;
            }
        }
    }
    char *prf = getparam(params, (char *) "lang", 1);
    bzero(pref, 50);
    char *pr[1];
    if (atoi(prf) != 0) {
        pr[0] = prf;
    } else
        pr[0] = "1";
    Rezultsql rez;
    exsql(1, "select pref from langs where id = '~'", pr, &rez);

    if (rez.colun != 0 && rez.rows != 0) {
        sprintf(pref, "%s%s.", rez.result[0][0], config.baza);
    }
    if(getenv("REQUEST_URI")){

        if (strstr(getenv("REQUEST_URI"), ".html")) {

            if (q >= PAPAM_BUF) {
                return 1;
            }

            char * html = getenv("REQUEST_URI") + 1;

            int lenhtml = coountdeliv(html, '.');
            if (lenhtml > 1) {
                char *tmlclear = (char*) malloc(lenhtml + 1);
                bzero(tmlclear, lenhtml + 1);
                strncpy(tmlclear, html, lenhtml);
                tmlclear[lenhtml ] = '\0';
                char *qvhtml = strtok(tmlclear, "-");
                Rezultsql rezult;
                char *prmch[2];
                prmch[0] = pref;
                prmch[1] = qvhtml;
                exsql(2, "select str, pstr, ppstr, arti, reg, user_id from  ~seotexts where link = '~';", prmch, &rezult);
                if (rezult.rows != 0 && rezult.colun != 0) {
                    params[q].name = (char*) malloc(strlen("idstr") + 1);
                    bzero(params[q].name, strlen("idstr") + 1);
                    strcpy(params[q].name, "idstr");
                    int lenv = strlen(rezult.result[0][0]);
                    params[q].value = (char*) malloc(lenv + 1);
                    bzero(params[q].value, lenv + 1);
                    strncpy(params[q].value, rezult.result[0][0], lenv);
                    params[q].value[lenv] = '\0';
                    params[q].type = 1;
                    q++;
                    params[q].name = (char*) malloc(strlen("idpstr") + 1);
                    bzero(params[q].name, strlen("idpstr") + 1);
                    strcpy(params[q].name, "idpstr");
                    lenv = strlen(rezult.result[0][1]);
                    params[q].value = (char*) malloc(lenv + 1);
                    bzero(params[q].value, lenv + 1);
                    strncpy(params[q].value, rezult.result[0][1], lenv);
                    params[q].value[lenv] = '\0';
                    params[q].type = 1;
                    q++;
                    params[q].name = (char*) malloc(strlen("idppstr") + 1);
                    bzero(params[q].name, strlen("idppstr") + 1);
                    strcpy(params[q].name, "idppstr");
                    lenv = strlen(rezult.result[0][2]);
                    params[q].value = (char*) malloc(lenv + 1);
                    bzero(params[q].value, lenv + 1);
                    strncpy(params[q].value, rezult.result[0][2], lenv);
                    params[q].value[lenv] = '\0';
                    params[q].type = 1;
                    q++;
                    params[q].name = (char*) malloc(strlen("idarticle") + 1);
                    bzero(params[q].name, strlen("idarticle") + 1);
                    strcpy(params[q].name, "idarticle");
                    lenv = strlen(rezult.result[0][3]);
                    params[q].value = (char*) malloc(lenv + 1);
                    bzero(params[q].value, lenv + 1);
                    strncpy(params[q].value, rezult.result[0][3], lenv);
                    params[q].value[lenv] = '\0';
                    params[q].type = 1;
                    q++;
                    params[q].name = (char*) malloc(strlen("reg") + 1);
                    bzero(params[q].name, strlen("reg") + 1);
                    strcpy(params[q].name, "reg");
                    lenv = strlen(rezult.result[0][4]);
                    params[q].value = (char*) malloc(lenv + 1);
                    bzero(params[q].value, lenv + 1);
                    strncpy(params[q].value, rezult.result[0][4], lenv);
                    params[q].value[lenv] = '\0';
                    params[q].type = 1;
                    q++;
                    params[q].name = (char*) malloc(strlen("user_id") + 1);
                    params[q].name = (char*) malloc(strlen("user_id") + 1);
                    strcpy(params[q].name, "user_id");
                    lenv = strlen(rezult.result[0][5]);
                    params[q].value = (char*) malloc(lenv + 1);
                    bzero(params[q].value, lenv + 1);
                    strncpy(params[q].value, rezult.result[0][5], lenv);
                    params[q].value[lenv] = '\0';
                    params[q].type = 1;
                    q++;
                    clearMysqRez(&rezult);
                }
                if (tmlclear) free(tmlclear);
            }
        }
    }

    if(getenv("REQUEST_METHOD")){
		//fprintf(stderr,"\nstart _________ssss sssss22__%s____\n", getenv("REQUEST_METHOD"));
        if (!strcmp(getenv("REQUEST_METHOD"), "POST")) {
			//fprintf(stderr,"\nstart _________ssss sssss22_23333___| %i | %i__\n",PAPAM_BUF,q);
            if (q >= PAPAM_BUF) {
                return 1;
            }
            //fprintf(stderr,"\nfile 77 sage\n");
            if(getenv("CONTENT_LENGTH")) {
                if (!getenv("CONTENT_TYPE") || strstr(getenv("CONTENT_TYPE"), "www-form-urlencoded")) {
                    char *query_post = NULL;
                    // char* pos_b = NULL;
                    unsigned int len;
                    len = atoi(getenv("CONTENT_LENGTH")) + 1;
                    query_post = (char *) malloc(len);
                    bzero(query_post, len);
                    char *pos_b = query_post;
                    int rt = fread(query_post, 1, len, stdin);
                    if (rt > 0) {
                        // query_post[len] = '\0';
                        char *cook = strtok(query_post, "&");
                        if (strlen(cook) > 1) {
                            int namelen = coountdeliv(cook, '=');
                            params[q].name = (char *) malloc((int) (namelen + 1));
                            bzero(params[q].name, (namelen + 1));
                            strncpy(params[q].name, cook, namelen);
                            params[q].name[namelen] = '\0';
                            cook += namelen + 1;
                            namelen = coountdeliv(cook, '&');
                            char *tem = (char *) malloc((int) (namelen + 1));
                            bzero(tem, (namelen + 1));
                            strncpy(tem, cook, namelen);
                            // tem[namelen] = '\0';
                            int re_bl = strlen(url_decode(tem));
                            params[q].value = malloc((re_bl + 1));
                            bzero(params[q].value, (re_bl + 1));
                            strncpy(params[q].value, url_decode(tem), re_bl);
                            //			params[q].name[re_bl] = '\0';
                            free(tem);
                            tem = NULL;
                            params[q].type = 1;
                            q++;
//                             debug_inner("____________________________________\n");
//                            debug_inner(query_post);
                            while (cook = strtok(NULL, "&")) {
                                if (strlen(cook) > 1) {
                                    namelen = coountdeliv(cook, 61);
                                    params[q].name = (char *) malloc((int) (namelen + 1));
                                    bzero(params[q].name, (namelen + 1));
                                    strncpy(params[q].name, cook, namelen);
                                    params[q].name[namelen] = '\0';
                                    cook += namelen;
                                    cook++;
                                    namelen = coountdeliv(cook, '\0');
                                    tem = (char *) malloc(namelen + 1);
                                    bzero(tem, (namelen + 1));
                                    strncpy(tem, cook, namelen);
                                    // tem[namelen] = '\0';
                                    re_bl = strlen(url_decode(tem));
                                    params[q].value = malloc((re_bl + 1));
                                    bzero(params[q].value, (re_bl + 1));
                                    strncpy(params[q].value, url_decode(tem), re_bl);
                                    free(tem);
                                    tem = NULL;
                                    params[q].type = 1;
                                    q++;
                                }
                            }
                        }
                    }
                    if (pos_b != NULL)free(pos_b);
                }else if(strstr(getenv("CONTENT_TYPE"), "application/json") ){
                    int len;
                    char *query_post = NULL;
                    len = atoi(getenv("CONTENT_LENGTH"));
                    query_post = (char *) malloc(len);
                    bzero(query_post, len);
                    int rt = fread(query_post, 1, len, stdin);
                    if (rt > 0) {
                        params[q].name = (char *) malloc(5);
                        bzero(params[q].name, 5);
                        strncpy(params[q].name, "body\0", 4);
                        params[q].value = (char *) malloc((rt+1));
                        bzero(params[q].value, (rt+1));
                        strncpy(params[q].value, url_decode(query_post), rt);
                        params[q].type = 1;
                        q++;
                    }
                    free(query_post);
                }else {
						//fprintf(stderr,"file sage\n");
                    int len;
                    len = atoi(getenv("CONTENT_LENGTH"));
                    if (len > 1) {
                        char* query_post = (char*) malloc(len + 1);
                        bzero(query_post, len + 1);
                        fread(query_post, 1, len, stdin);
                        char * cont_t = getenv("CONTENT_TYPE");
                        char * pos_b = strstr(cont_t, "boundary=") + 10;
                        char *pos_b_s = pos_b;
                        int i;
                        for (i = 0; pos_b[i] != ' '; i++, pos_b++);
                        char *bound = (char*) malloc(i);
                        bzero(bound, i);
                        strncpy(bound, pos_b_s, i);

                        pos_b = query_post;
                        int boundl = strlen(bound);
                        int position = 0;
                        int flag = 1;
                        int imgc = 0;
                        int fl_ret = 0;
                        while (position >= 0 && fl_ret == 0) {
							//fprintf(stderr,"\npun %s %s\n",bound, query_post);
                            position = checkbound(query_post, bound, len, boundl) + 2;
                           // fprintf(stderr,"\npun %s %s\n",bound, position);
                            if(position == len){
                                fl_ret = 1;
                            }

                            len -= (position + boundl);
                            query_post += position + boundl;
                            len -= (coountstr(query_post) + 2);
                            query_post += coountstr(query_post) + 2;
                            i = coountstr(query_post);
                            char *start = (char*) malloc(i + 1);
                            bzero(start, i + 1);
                            memcpy(start, query_post, i);
						//	fprintf(stderr,"file %s\n",start);
                            if (strstr(start, "filename") || (strstr(start, "content-type")) && !strstr(start, "filename=\"\"")) {
								int debil = 0;
								if(strstr(start, "content-type"))
										debil = 1;
								//fprintf(stderr,"\nfilename\n");
                                char* chkname = strstr(query_post, "filename") + 10;
                                char* chknamefin = strstr(chkname, "\"");
                                int raz = chknamefin - chkname;
                                char *name_fl = malloc(raz + 1);
                                bzero(name_fl, raz + 1);
                                strncpy(name_fl,chkname,raz);

                                if (chknamefin - chkname > 3) {
									 char *startread_h;
                                    if(debil == 0){
										startread_h = query_post;
										}else{
											startread_h = strstr(query_post, "\r\n")+2;
											}
											//fprintf(stderr,"startread_h  %s\n",startread_h);
                                    if (!strstr(start, "file_load") ) {
                                        char *paranname = strstr(startread_h, "name") + 6;
                                        char *parannamefin = strstr(paranname, "\"");
                                        int razparam = parannamefin - paranname;
                                     //   fprintf(stderr,"start ______razparam_________%i\n",razparam);
                                        params[q].name = (char *) malloc(razparam + 2);
                                        bzero(params[q].name, razparam + 2);
                                        strncpy(params[q].name, paranname, razparam);
                                        params[q].name[razparam + 1] = '\0';
                                    }else{
                                        params[q].name = (char*) malloc(24);
                                        bzero(params[q].name,24);
                                        if(imgc == 0){
                                            strncpy(params[q].name, "filename\0", 9);
                                        }else{
                                            sprintf(params[q].name,"filename%i",imgc);
                                        }
                                    }
                                    imgc++;
                                    params[q].type = 2;
                                    params[q].value = (char*) malloc(raz);

                                    bzero(params[q].value, raz + 1);
                                    memcpy(params[q].value,name_fl,raz);
                                    
                                    char *startread;
                                    if(debil == 0){
										startread = strstr(query_post, "Content-Type");
										}else{
											startread = strstr(query_post, "\r\n\r\n")+4;
											}
                                    
                                    //fprintf(stderr,"startread 1 %s\n",startread);
                                    i = coounttwostr(startread);
                                    startread += i;
                                    int cnreadfin = checkbound(query_post, bound, len, boundl);
                                    int lench = query_post - startread + cnreadfin;
                                    if(lench > 0){
                                        FILE * fl;
                                        int lnma = raz + 30;
                                       // fprintf(stderr,"start _____lnma_________%i\n",lnma);
                                        char *patch = malloc(lnma);
                                       // fprintf(stderr,"start ____lench________%i\n",lench);
                                        bzero(patch,lnma);
                                        sprintf(patch,"/tmp/%s",params[q].value);
                                        fl = fopen(patch, "wb+");
                                        startread[lench] = EOF;
                                       // fprintf(stderr,"start ____lench________%i\n",lench);
                                       // fprintf(stderr,"startread_____%s\n",startread);
                                        fwrite(startread, 1, lench, fl);
                                        //fprintf(stderr,"start _____patch 2________\n");
                                        fclose(fl);
                                        free(patch);

                                    }

                                    q++;
                                }
                                free(name_fl);

                            } else {
                                if (strstr(start, "name") && strstr(start, "form-data") && !strstr(start, "filename")) {
                                    params[q].type = 1;
                                    char* startval = strstr(query_post, start);
                                    int paramle = coountdeliv(startval, '"');
                                    startval += paramle + 1;
                                    paramle = coountdeliv(startval, '"');
                                    params[q].name = (char*) malloc(paramle + 1);
                                    bzero(params[q].name, paramle + 1);
                                    memcpy(params[q].name, startval, paramle);
                                    // params[q].name[paramle+1] = '\0';
                                    char* starparam = strstr(query_post, startval);

                                    i = coounttwostr(starparam);
                                    starparam += i;
                                    i = checkbound(starparam, bound, len, boundl);
                                    if (i > 0) {
                                        params[q].value = (char*) malloc(i + 1);
                                        bzero(params[q].value, i + 1);
                                        memcpy(params[q].value, starparam, i);
                                        params[q].value[i] = '\0';
                                    } else {
                                        params[q].type = 5;
                                        params[q].value = (char*) malloc(2);
                                        bzero(params[q].value, 2);
                                        params[q].value[1] = '\0';
                                    }
                                    q++;
                                }
                            }
                            free(start);
                            flag++;
                            if (q >= PAPAM_BUF)
                            return 1;

                        }
                        free(bound);
                        free(pos_b);
                    }

                }
            }
        }
    }

    if(getenv("REQUEST_METHOD")){
        // if (!strcmp(getenv("REQUEST_METHOD"), "GET")) {
            if (q >= PAPAM_BUF) {
                return 1;
            }
            char *get = getenv("QUERY_STRING");
            
            char *cook;
            if(get != NULL){
                // debug_inner_c("get",get);
                if (cook = strtok(get, "&")) {
                    int namelen = coountdeliv(cook, '=');
                    params[q].name = (char*) malloc(namelen + 2);
                    bzero(params[q].name,namelen + 2);
                    strncpy(params[q].name, cook, namelen);
                    params[q].name[namelen+1] = '\0';
                    cook += namelen;
                    cook++;
                    namelen = strlen(cook);
                    params[q].value = (char*) malloc(namelen + 2);
                    bzero(params[q].value,namelen + 2);
                    strncpy(params[q].value, cook, namelen);
                    params[q].value[namelen] = '\0';
                    params[q].type = 1;
                    q++;
                    while (cook = strtok(NULL, "&")) {
                        namelen = coountdeliv(cook, '=');
                        params[q].name = (char*) malloc(namelen + 2);
                        bzero(params[q].name,namelen + 2);
                        strncpy(params[q].name, cook, namelen);
                        params[q].name[namelen+1] = '\0';
                        cook += namelen;
                        cook++;
                        namelen = strlen(cook);
                        params[q].value = (char*) malloc(namelen + 2);
                        bzero(params[q].value,namelen + 2);
                        strncpy(params[q].value, cook, namelen);
                        params[q].value[namelen+1] = '\0';
                        params[q].type = 1;
                        q++;
                    }
                }
            }
        // }
    }
    params[q].name = (char*) malloc(2);
    strncpy(params[q].name, "0\0", 2);
    params[q].value = (char*) malloc(2);
    strncpy(params[q].value, "0\0", 2);
    params[q].type = 0;
    return 1;
}

#ifdef __cplusplus
}
#endif

#endif /* CGI_H */

