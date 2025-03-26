
#include "vdcgi.h"
#include <unistd.h>
#define h_addr  h_addr_list[0]
#ifndef VDNET_H
#define VDNET_H

#ifdef __cplusplus
extern "C" {
#endif


VALUE putHttpsJson(VALUE selt, VALUE url, VALUE prt, VALUE script, VALUE header, VALUE json) {
        //	fprintf(stderr,"jaon\n\n\n");
        VALUE re;
        int socet_fd;
        int port = atoi(StringValuePtr(prt));
        char *crip = StringValuePtr(script);
        char *prm = StringValuePtr(json);
        char *ur = StringValuePtr(url);
        SSL_library_init();
        SSL_CTX *ctx = InitCTX();
        SSL *ssl = SSL_new(ctx);
        if(getVdSocketNoBlock(&socet_fd,ur, port) != -1){
            //     debug_inner("start rad sock11 \n");
            if (SSL_set_fd(ssl, socet_fd) == 0)
                ERR_print_errors_fp(stderr);
            start_ssl_jj:    
            if (SSL_connect(ssl) == -1) {
                int er = SSL_get_error(ssl, -1);
                if(er == SSL_ERROR_WANT_READ || er == SSL_ERROR_WANT_WRITE){
                    usleep(500);
                    goto start_ssl_jj;
                }else{
                ERR_print_errors_fp(stderr);
                close(socet_fd);
                rb_encoding * en = rb_utf8_encoding();
                VALUE rezult =  rb_enc_str_new_cstr("FALSE", en);
                ERR_print_errors_fp(stderr);
                return rezult;     
                }
            } else {
                int lenh = 1024;
                char *hed = (char*)malloc(1024);

                bzero(hed, 1023);
                char *hedd;
                sprintf(hed, "PUT /%s HTTP/1.1\r\nHost: %s\r\n", crip, ur);
                strcat(hed, "User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:50.0) Gecko/20100101 Firefox/50.0\r\nPragma: no-cache\r\nCache-Control: no-cache\r\nConnection: Close\r\nContent-Type: application/json;charset=utf-8\r\n");
                for (int i = 0; i < RARRAY_LENINT(header); i++) {
                    VALUE r = rb_ary_entry(header, i);
                    strcat(hed, StringValuePtr(r));
                    strcat(hed, "\r\n");
                }
                int lhead = strlen(hed) + strlen(prm) + 100;
                if(lhead > 1024){
                    if((hedd = realloc( hed, lhead)) != NULL ){
                        // free(hed);
                        hed = hedd;
                    }
                }
                int cnl = strlen(prm) + 2;
                char conl[50];
                bzero(conl,50);
                sprintf(conl,"Content-Length: %i\r\n\r\n",cnl);
                strcat(hed, conl);
                strcat(hed,prm);
                strcat(hed, "\r\n");

                if (writeSocketSSL(hed, strlen(hed), ssl, &socet_fd) != -1) {
                    char * buf = readVDSocketSSL(&socet_fd,ssl);
                    close(socet_fd);
                    re = rb_enc_str_new_cstr(buf, rb_utf8_encoding());
                    free(buf);
                }
                free(hed);
            }
        }
        return re;

    }


VALUE getHttpsJson(VALUE selt, VALUE url, VALUE prt, VALUE script, VALUE header, VALUE json) {
//	fprintf(stderr,"jaon\n\n\n");
    VALUE re;
    int socet_fd;
    int port = atoi(StringValuePtr(prt));
    char *crip = StringValuePtr(script);
    char *prm = StringValuePtr(json);
    char *ur = StringValuePtr(url);
    SSL_library_init();
    SSL_CTX *ctx = InitCTX();
    SSL *ssl = SSL_new(ctx);
    if(getVdSocket(&socet_fd,ur, port, "", 0, "", "") != -1){
//     debug_inner("start rad sock11 \n");
        if (SSL_set_fd(ssl, socet_fd) == 0)
            ERR_print_errors_fp(stderr);
        start_ssl_j:    
        if (SSL_connect(ssl) == -1) {
            int er = SSL_get_error(ssl, -1);
            if(er == SSL_ERROR_WANT_READ || er == SSL_ERROR_WANT_WRITE){
                usleep(500);
                goto start_ssl_j;
            }else{
               ERR_print_errors_fp(stderr);
               close(socet_fd);
               rb_encoding * en = rb_utf8_encoding();
               VALUE rezult =  rb_enc_str_new_cstr("FALSE", en);
               ERR_print_errors_fp(stderr);
               return rezult;     
            }
        } else {
            int lenh = 1024;
            char *hed = (char*)malloc(1024);

            bzero(hed, 1023);
            char *hedd;
            sprintf(hed, "POST /%s HTTP/1.1\r\nHost: %s\r\n", crip, ur);
            strcat(hed, "User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:50.0) Gecko/20100101 Firefox/50.0\r\nPragma: no-cache\r\nCache-Control: no-cache\r\nConnection: Close\r\nContent-Type: application/json;charset=utf-8\r\n");
            for (int i = 0; i < RARRAY_LENINT(header); i++) {
                VALUE r = rb_ary_entry(header, i);
                strcat(hed, StringValuePtr(r));
                strcat(hed, "\r\n");
            }
            int lhead = strlen(hed) + strlen(prm) + 100;
            if(lhead > 1024){
                if((hedd = realloc( hed, lhead)) != NULL ){
                    // free(hed);
                    hed = hedd;
                }
            }
            int cnl = strlen(prm) + 2;
            char conl[50];
            bzero(conl,50);
            sprintf(conl,"Content-Length: %i\r\n\r\n",cnl);
            strcat(hed, conl);
            strcat(hed,prm);
            strcat(hed, "\r\n");
            if (writeSocketSSL(hed, strlen(hed), ssl, &socet_fd) != -1) {
                char * buf = readVDSocketSSL(&socet_fd,ssl);
                close(socet_fd);
                re = rb_enc_str_new_cstr(buf, rb_utf8_encoding());
                free(buf);
            }
            free(hed);
        }
    }
    return re;

}
    

    VALUE getHttpJson(VALUE selt, VALUE url, VALUE prt, VALUE script, VALUE header, VALUE json) {
	// fprintf(stderr,"jaon\n\n\n");
	VALUE re = T_NIL;
	int socet_fd;
	int port = atoi(StringValuePtr(prt));
	char *crip = StringValuePtr(script);
	char *prm = StringValuePtr(json);
	char *ur = StringValuePtr(url);
	if(getVdSocketNoBlock(&socet_fd,ur, port) != -1){
        // debug_inner("start scoket \n\n");
	   int lhead = 0;
	    char *hed = (char*)malloc(1024);
	    bzero(hed, 1023);
	    char *hedd;
	    sprintf(hed, "POST /%s HTTP/1.0\nHost: %s\r\n", crip, ur);
	    strcat(hed, "User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:50.0) Gecko/20100101 Firefox/50.0\r\nPragma: no-cache\r\nCache-Control: no-cache\r\nConnection: Close\r\nContent-Type: application/json;charset=utf-8\r\n");
	    for (int i = 0; i < RARRAY_LENINT(header); i++) {
		VALUE r = rb_ary_entry(header, i);
		strcat(hed, StringValuePtr(r));
		strcat(hed, "\r\n");
	   }
	      
	    lhead = strlen(hed) + strlen(prm) + 100;
	    if(lhead > 1024){
		if((hedd = realloc( hed, lhead)) != NULL ){
		    // free(hed);
		    hed = hedd;
		}
	   }
	    int cnl = strlen(prm) + 2;
	    char conl[50];
	    bzero(conl,50);
	    sprintf(conl,"Content-Length: %i\r\n\r\n",cnl);
	    strcat(hed, conl);
	    strcat(hed,prm);
	    strcat(hed, "\r\n");
        
        int write_sock = writeSocket(hed, strlen(hed), &socet_fd);
        
	    if ( write_sock >= strlen(hed)) {
            char * buf = readVDSocket(&socet_fd);
            re = rb_enc_str_new_cstr(buf, rb_utf8_encoding());
            free(buf);
            close(socet_fd);
            return re;
	    }else{
            debug_inner("write socket fail");
		    return re;
	    }
	}
	return re;
	
    }


VALUE getHttpGetSSocks(VALUE selt, VALUE url, VALUE prt, VALUE script, VALUE header, VALUE param, VALUE sockeusrl, VALUE socksport, VALUE socklogin, VALUE sockpass) {

    SSL_library_init();
    SSL_CTX *ctx = InitCTX();
    SSL *ssl = SSL_new(ctx);
    VALUE re = rb_cNilClass;
    int socet_fd;
    int port = atoi(StringValuePtr(prt));
    char *crip = StringValuePtr(script);
    char *prm = StringValuePtr(param);
    char *ur = StringValuePtr(url);
    char *sockeu = StringValuePtr(sockeusrl);
    int portsock = atoi(StringValuePtr(socksport));
    char *socklog = StringValuePtr(socklogin);
    char *sockpas = StringValuePtr(sockpass);
    fd_set rfds, wfds;
    struct timeval tv;
    if(getVdSocketNoBlock(&socet_fd,ur, port) != -1){

        if (SSL_set_fd(ssl, socet_fd) == 0)
            ERR_print_errors_fp(stderr);
        start_ssl_s:    
        if (SSL_connect(ssl) == -1) {
            int er = SSL_get_error(ssl, -1);
            if(er == SSL_ERROR_WANT_READ || er == SSL_ERROR_WANT_WRITE){
                usleep(500);
                goto start_ssl_s;
            }else{
               ERR_print_errors_fp(stderr);
               close(socet_fd);
               rb_encoding * en = rb_utf8_encoding();
               VALUE rezult =  rb_enc_str_new_cstr("FALSE", en);
               ERR_print_errors_fp(stderr);
               return rezult;     
            }
        } else {
            int lenh = 1024;
            int lhead = 0;
            char hed[1024];
            bzero(hed, lenh);
            if (strlen(prm) == 0) {
                sprintf(hed, "GET /%s HTTP/1.1\r\nHost: %s\r\n", crip, ur);
            } else
                sprintf(hed, "GET /%s?%s HTTP/1.1\nHost: %s\r\n", crip, prm, ur);
            strcat(hed, "User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:50.0) Gecko/20100101 Firefox/50.0\r\nAccept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\nConnection: close\r\n");
            lhead = strlen(hed);
            for (int i = 0; i < RARRAY_LENINT(header); i++) {
                VALUE r = rb_ary_entry(header, i);
                lhead += strlen(StringValuePtr(r));
                strcat(hed, StringValuePtr(r));
                strcat(hed, "\r\n");
                lhead += 2;
            }
            strcat(hed, "\r\n");

//            fprintf(stderr,"hed %s\n\n",hed);
            if (writeSocketSSL(hed, strlen(hed), ssl, &socet_fd) != -1) {
                char * buf = readVDSocketSSL(&socet_fd,ssl);
//                fprintf(stderr,"buf %s\n\n",buf);
                close(socet_fd);
                re = rb_enc_str_new_cstr(buf, rb_utf8_encoding());
                free(buf);
            }
        }
    }
    SSL_free(ssl);
    SSL_CTX_free(ctx);
    return re;
}



    VALUE getHttpGetSocks(VALUE selt, VALUE url, VALUE prt, VALUE script, VALUE header, VALUE param, VALUE sockeusrl, VALUE socksport, VALUE socklogin, VALUE sockpass) {
	VALUE re;
	int port = atoi(StringValuePtr(prt));
	char *crip = StringValuePtr(script);
	char *prm = StringValuePtr(param);
	char *ur = StringValuePtr(url);
	char *sockeu = StringValuePtr(sockeusrl);
	int portsock = atoi(StringValuePtr(socksport));
	char *socklog = StringValuePtr(socklogin);
	char *sockpas = StringValuePtr(sockpass);
//	struct timeval tv;
//	fd_set rfds, wfds;
	int socet_fd;
	int reaauh = getVdSocketNoBlock(&socet_fd,ur, port);
	if(reaauh != -1){
	    int lenh = 1024;
	    char hed[1024];
	    bzero(hed, 1024);
	    if (strlen(prm) == 0) {
		sprintf(hed, "GET /%s HTTP/1.1\r\nHost: %s\r\n", crip, ur);
	    } else
		sprintf(hed, "GET /%s?%s HTTP/1.1\nHost: %s\r\n", crip, prm, ur);
	    strcat(hed, "User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:50.0) Gecko/20100101 Firefox/50.0\r\nAccept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\nConnection: close\r\n");
	    for (int i = 0; i < RARRAY_LENINT(header); i++) {
		VALUE r = rb_ary_entry(header, i);
		strcat(hed, StringValuePtr(r));
		strcat(hed, "\r\n");
	    }
	    strcat(hed, "\r\n");

	    if (writeSocket(hed, strlen(hed), &socet_fd) != -1) {
		    char * buf = readVDSocket(&socet_fd);
            re = rb_enc_str_new_cstr(buf, rb_utf8_encoding());
            free(buf);
            close(socet_fd);
	       return re;
	    }else{
		    return re;
	    }
	}
	return re;
    }

    VALUE getHttpGet(VALUE selt, VALUE url, VALUE prt, VALUE script, VALUE header, VALUE param) {
        // debug_inner("______________reclock_________________\n");
	VALUE re;
	int port = atoi(StringValuePtr(prt));
	char *crip = StringValuePtr(script);
	char *prm = StringValuePtr(param);
	char *ur = StringValuePtr(url);
	int socet_fd;
	if(getVdSocketNoBlock(&socet_fd,ur, port) != -1){
       
	    int lenh = 1024;
        
	    char hed[1024];
	    bzero(hed, 1024);
	    if (strlen(prm) == 0) {
		sprintf(hed, "GET /%s HTTP/1.1\r\nHost: %s\r\n", crip, ur);
	    } else
		sprintf(hed, "GET /%s?%s HTTP/1.1\r\nHost: %s\r\n", crip, prm, ur);
	    strcat(hed, "User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:50.0) Gecko/20100101 Firefox/50.0\r\nAccept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\nConnection: close\r\n");
	    for (int i = 0; i < RARRAY_LENINT(header); i++) {
		VALUE r = rb_ary_entry(header, i);
		strcat(hed, StringValuePtr(r));
		strcat(hed, "\r\n");
	    }
	    strcat(hed, "\r\n");
	    if ( writeSocket(hed, strlen(hed), &socet_fd) != -1) {
		char * buf = readVDSocket(&socet_fd);
//            debug_inner(buf);
		re = rb_enc_str_new_cstr(buf, rb_utf8_encoding());
//         re =  rb_str_new_cstr(buf);
		free(buf);
	     close(socet_fd);
        
	    return re;
	    }else{
            
		return re;
	    }
	}
    
	return re;
	
    }
    
    VALUE getHttpGets(VALUE selt, VALUE url, VALUE prt, VALUE script, VALUE header, VALUE param) {

	SSL_library_init();
	SSL_CTX *ctx = InitCTX();
	SSL *ssl = SSL_new(ctx);
	VALUE re = rb_cNilClass;
	int socet_fd;
	int port = atoi(StringValuePtr(prt));
	char *crip = StringValuePtr(script);
	char *prm = StringValuePtr(param);
	char *ur = StringValuePtr(url);
	fd_set rfds, wfds;
	struct timeval tv;
	if(getVdSocketNoBlock(&socet_fd,ur, port) != -1){
//        debug_inner("start rad sock11 \n");

   	    if (SSL_set_fd(ssl, socet_fd) == 0){
           
            ERR_print_errors_fp(stderr);
        }
		start_ssl:    
	    if (SSL_connect(ssl) == -1) {
            int er = SSL_get_error(ssl, -1);
            if(er == SSL_ERROR_WANT_READ || er == SSL_ERROR_WANT_WRITE){
                usleep(500);
                goto start_ssl;
            }else{
               ERR_print_errors_fp(stderr);
               close(socet_fd);
               rb_encoding * en = rb_utf8_encoding();
               VALUE rezult =  rb_enc_str_new_cstr("FALSE", en);
               ERR_print_errors_fp(stderr);
               return rezult;     
            }
        //     printf("_________0_____\n");
		// ERR_print_errors_fp(stderr);
	    } else {
            // printf("_________2_____\n");
		int lenh = 1024;
		int lhead = 0;
		char hed[1024];
		bzero(hed, 1024);
		if (strlen(prm) == 0) {
		    sprintf(hed, "GET /%s HTTP/1.1\r\nHost: %s\r\n", crip, ur);
		} else
		    sprintf(hed, "GET /%s?%s HTTP/1.1\r\nHost: %s\r\n", crip, prm, ur);
		strcat(hed, "User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:50.0) Gecko/20100101 Firefox/50.0\r\nAccept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\nConnection: close\r\n");
		lhead = strlen(hed);
		for (int i = 0; i < RARRAY_LENINT(header); i++) {
		    VALUE r = rb_ary_entry(header, i);
		    lhead += strlen(StringValuePtr(r));
		    strcat(hed, StringValuePtr(r));
		    strcat(hed, "\r\n");
		    lhead += 2;
		}
		strcat(hed, "\r\n");
//            debug_inner(hed);

		if (writeSocketSSL(hed, strlen(hed), ssl, &socet_fd) != -1) {
            
		    char * buf = readVDSocketSSL(&socet_fd,ssl);
             
		    close(socet_fd);
		    re = rb_enc_str_new_cstr(buf, rb_utf8_encoding());
		    free(buf);
		}
	    }
	}
        SSL_free(ssl);
        SSL_CTX_free(ctx);
        return re;
    }

VALUE chmaixboxSSL(VALUE selt, VALUE doamin, VALUE port, VALUE to){
        if (TYPE(doamin) == T_NIL)
            doamin = rb_str_new2("");
        if (TYPE(port) == T_NIL)
            port = INT2FIX(0);
        if (TYPE(to) == T_NIL)
            to = rb_str_new2("");
        SSL_library_init();
        SSL_CTX *ctx = InitCTX();
        SSL *ssl = SSL_new(ctx);    
        char *doamin_c = StringValuePtr(doamin);
        int port_c = FIX2INT(port);
        char *to_c = StringValuePtr(to);
        int socet_fd;
        char mail[1024];
        bzero(mail,1024);
        //  printf("start 0\n");
        if(getVdSocketNoBlock(&socet_fd,doamin_c, port_c) != -1) {
            // printf("start 1\n");
        if (SSL_set_fd(ssl, socet_fd) == 0){
            close(socet_fd);
            rb_encoding * en = rb_utf8_encoding();
            VALUE rezult =  rb_enc_str_new_cstr("FALSE", en);
            ERR_print_errors_fp(stderr);
            return rezult;
            }
            //  printf("start 2\n");
            start_ssl_M:
            if (SSL_connect(ssl) == -1) {
               
                int er = SSL_get_error(ssl, -1);
                    if(er == SSL_ERROR_WANT_READ || er == SSL_ERROR_WANT_WRITE){
                        usleep(500);
                        goto start_ssl_M;
                    }else{

                    ERR_print_errors_fp(stderr);
                    close(socet_fd);
                    rb_encoding * en = rb_utf8_encoding();
                    VALUE rezult =  rb_enc_str_new_cstr("FALSE", en);
                    ERR_print_errors_fp(stderr);
                    return rezult;
                    }
                } else {
                // printf("start 3\n");
                sprintf(mail,"EHLO %s\n",doamin_c);
                writeSocketSSL(mail, strlen(mail), ssl, &socet_fd);
                char *ansver = readVDSocketSSL(&socet_fd,ssl);
                //  printf("req %s answ %s\n",mail,ansver);
                if(strstr(ansver,"220")){
                    free(ansver);
                    bzero(mail,1024);
                    sprintf(mail,"MAIL FROM:<admin@%s>\n",config.domain);
                    writeSocketSSL(mail, strlen(mail), ssl, &socet_fd);
                    ansver = readVDSocketSSL(&socet_fd,ssl);
                    // printf("req2 %s answ %s\n",mail,ansver);
                    if(strstr(ansver,"250")){
                        free(ansver);
                        bzero(mail,1024);
                        sprintf(mail,"RCPT TO: <%s>\n",to_c);
                        writeSocketSSL(mail, strlen(mail), ssl, &socet_fd);
                        ansver = readVDSocketSSL(&socet_fd,ssl);
                        
                        if(strstr(ansver,"250")){
                            rb_encoding * en = rb_utf8_encoding();
                            VALUE rezult =  rb_enc_str_new_cstr("SUCCESS", en);
                            free(ansver);
                            close(socet_fd);
                            SSL_free(ssl);
                            SSL_CTX_free(ctx);
                            return rezult;
                        }else{
                            rb_encoding * en = rb_utf8_encoding();
                            VALUE rezult =  rb_enc_str_new_cstr(ansver, en);
                            free(ansver);
                            close(socet_fd);
                            SSL_free(ssl);
                            SSL_CTX_free(ctx);
                            return rezult;
                        }
                    }else{
                        rb_encoding * en = rb_utf8_encoding();
                        VALUE rezult =  rb_enc_str_new_cstr(ansver, en);
                        free(ansver);
                        close(socet_fd);
                        SSL_free(ssl);
                        SSL_CTX_free(ctx);
                        return rezult;
                    }
            
                }else{
                    close(socet_fd);
                    rb_encoding * en = rb_utf8_encoding();
                    VALUE rezult =  rb_enc_str_new_cstr(ansver, en);
                    free(ansver);
                    return rezult;
                }
            
            }
            
        }else{
            rb_encoding * en = rb_utf8_encoding();
            VALUE rezult =  rb_enc_str_new_cstr("FALSE", en);
            return rezult;
        }
}

VALUE chdomain(VALUE selt, VALUE doamin, VALUE port){
        if (TYPE(doamin) == T_NIL)
            doamin = rb_str_new2("");
        if (TYPE(port) == T_NIL)
            port = INT2FIX(0);
        
        char *doamin_c = StringValuePtr(doamin);
        int port_c = FIX2INT(port);
        int socet_fd;
        char mail[1024];
        bzero(mail,1024);
       int rez = getVdSocketNoBlock(&socet_fd,doamin_c, port_c);
       if(rez == 1)
            close(socet_fd);
        return  INT2NUM(rez);   
          
}


    VALUE chmaixbox(VALUE selt, VALUE doamin, VALUE port, VALUE to){
        if (TYPE(doamin) == T_NIL)
            doamin = rb_str_new2("");
        if (TYPE(port) == T_NIL)
            port = INT2FIX(0);
        if (TYPE(to) == T_NIL)
            to = rb_str_new2("");
        char *doamin_c = StringValuePtr(doamin);
        int port_c = FIX2INT(port);
        char *to_c = StringValuePtr(to);
        int socet_fd;
        char mail[1024];
        bzero(mail,1024);

        if(getVdSocketNoBlock(&socet_fd,doamin_c, port_c) != -1) {
        // if(getVdSocket(&socet_fd,doamin_c, port_c, "", 0, "", "") != -1) {
            sprintf(mail,"EHLO %s\n",doamin_c);
            // printf("req 1 %s\n",mail);
            writeSocket(mail, strlen(mail), &socet_fd);
            char *ansver = readVDSocket(&socet_fd);
            // printf("answer 1 %s\n",ansver);
            if(strstr(ansver,"220")){
                free(ansver);
                bzero(mail,1024);
                sprintf(mail,"MAIL FROM:<admin@%s>\n",config.domain);
                //  printf("req 2 %s\n",mail);
                writeSocket(mail, strlen(mail), &socet_fd);
                ansver = readVDSocket(&socet_fd);
                // printf("answer 2 %s\n",ansver);
                if(strstr(ansver,"250")){
                    free(ansver);
                    bzero(mail,1024);
                    sprintf(mail,"RCPT TO: <%s>\n",to_c);
                    //  printf("req 3 %s\n",mail);
                    writeSocket(mail, strlen(mail), &socet_fd);
                    ansver = readVDSocket(&socet_fd);
                    // printf("answer 3 %s\n",ansver);
                    if(strstr(ansver,"250")){
                        rb_encoding * en = rb_utf8_encoding();
                        VALUE rezult =  rb_enc_str_new_cstr("SUCCESS", en);
                        free(ansver);
                        close(socet_fd);
                        return rezult;
                    }else{
                        rb_encoding * en = rb_utf8_encoding();
                        VALUE rezult =  rb_enc_str_new_cstr(ansver, en);
                        free(ansver);
                        close(socet_fd);
                        return rezult;
                    }
                }else{
                    rb_encoding * en = rb_utf8_encoding();
                    VALUE rezult =  rb_enc_str_new_cstr(ansver, en);
                    free(ansver);
                    close(socet_fd);
                    return rezult;
                }
                close(socet_fd);
            }else{
                rb_encoding * en = rb_utf8_encoding();
                VALUE rezult =  rb_enc_str_new_cstr(ansver, en);
                free(ansver);
                return rezult;
            }
        }else{
            rb_encoding * en = rb_utf8_encoding();
            VALUE rezult =  rb_enc_str_new_cstr("FAIL", en);
            return rezult;
        }
    }

    int create_post(VALUE key, VALUE val, VALUE header){
	strcat((char*)header,"--sjdlIosjslo---\r\n");
	strcat((char*)header,"Content-Disposition: form-data; name=\"");
	strcat((char*)header,StringValuePtr(key));
	strcat((char*)header,"\"\r\n\r\n");
	strcat((char*)header,StringValuePtr(val));
	strcat((char*)header,"\r\n");
	return 0;
    }
    
    VALUE getPost(VALUE selt, VALUE url, VALUE prt, VALUE script, VALUE header, VALUE param) {
	VALUE re;
	int socet_fd;
	int port = atoi(StringValuePtr(prt));
	char *crip = StringValuePtr(script);
//	char *prm = StringValuePtr(param);
	char *ur = StringValuePtr(url);
	if(getVdSocketNoBlock(&socet_fd,ur, port) != -1){
	    int lenh = 0;
	    rb_hash_foreach(param, hash_lench_p, (VALUE)&lenh) ;
	    lenh += strlen(crip);
	    lenh += 1024;
	    lenh += 256 ;
	    char *hed = (char*)malloc(lenh);
	    bzero(hed, lenh);
	    int lhead = 0;  
	    char bound[50];
	    bzero(bound, 50);
	    strcpy(bound,"--sjdlIosjslo---");
	    sprintf(hed, "POST /%s HTTP/1.1\r\nHost: %s\r\nContent-Type: multipart/form-data; boundary=sjdlIosjslo---\r\n", crip, ur);
	    strcat(hed, "User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:50.0) Gecko/20100101 Firefox/50.0\r\n");
	    lhead = strlen(hed);
	    for (int i = 0; i < RARRAY_LENINT(header); i++) {
		VALUE r = rb_ary_entry(header, i);
		strcat(hed, StringValuePtr(r));
		strcat(hed, "\r\n");
	    }
	    int lb = 0;
	    rb_hash_foreach(param, hash_lench_p, (VALUE)&lb);
	    lb += 128;
	    char *post = (char*)malloc(lb);
	    bzero(post,(lb));
	    rb_hash_foreach(param, create_post, (VALUE)post);
//	    strcat(post,"\r\n");
	    strcat(post,bound);
	    strcat(post,"\r\n");
	    strcat(hed, "Content-Length: ");
	    char lbc[20];
	    bzero(lbc,20);
	    sprintf(lbc,"%i",strlen(post) );
	    strcat(hed, lbc);
	    strcat(hed, "\r\nConnection: Close\r\n\r\n");
	    strcat(hed,post);
	    free(post);
	    strcat(hed, "\r\n");

	    lhead = strlen(hed);
	    if (writeSocket(hed, lhead, &socet_fd) != -1) {
		char * buf = readVDSocket(&socet_fd);
        // debug_inner_c("read sock", buf);
		re = rb_enc_str_new_cstr(buf, rb_utf8_encoding());
		free(buf);
		close(socet_fd);
	    return re;
	    }else{
		return re;
	    }
	}
	return re;
	
    }

 VALUE getHttpPosts(VALUE selt, VALUE url, VALUE prt, VALUE script, VALUE header, VALUE param) {
        SSL_library_init();
        SSL_CTX *ctx = InitCTX();
        SSL *ssl = SSL_new(ctx);
        VALUE re;
        int socet_fd;
        int port = atoi(StringValuePtr(prt));
        char *crip = StringValuePtr(script);
        char *prm = StringValuePtr(param);
        char *ur = StringValuePtr(url);
        if(getVdSocketNoBlock(&socet_fd,ur, port) != -1){
//            debug_inner("start rad sock11 \n");
            if (SSL_set_fd(ssl, socet_fd) == 0)
                ERR_print_errors_fp(stderr);
            start_ssl_pj:    
            if (SSL_connect(ssl) == -1) {
                int er = SSL_get_error(ssl, -1);
                if(er == SSL_ERROR_WANT_READ || er == SSL_ERROR_WANT_WRITE){
                    usleep(500);
                    goto start_ssl_pj;
                }else{
                ERR_print_errors_fp(stderr);
                close(socet_fd);
                rb_encoding * en = rb_utf8_encoding();
                VALUE rezult =  rb_enc_str_new_cstr("FALSE", en);
                ERR_print_errors_fp(stderr);
                return rezult;     
                }
            } else {
//                debug_inner("start posn\n");
                int lenh = 1024;
                int lhead = 0;
                int le_param = strlen(prm);
                char lep[12];
                bzero(lep,12);
                sprintf(lep,"%i",le_param);
                char hed[1024+le_param];
                bzero(hed, 1024+le_param);
                sprintf(hed, "POST /%s HTTP/1.1\r\nHost: %s\r\n", crip, ur);
                strcat(hed, "User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:50.0) Gecko/20100101 Firefox/50.0\r\nContent-Type: application/x-www-form-urlencoded\r\nAccept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\nConnection: close\r\n");
                strcat(hed, "Content-Length: ");
                strcat(hed, lep);
                strcat(hed, "\r\n");
                lhead = strlen(hed);

                for (int i = 0; i < RARRAY_LENINT(header); i++) {
                    VALUE r = rb_ary_entry(header, i);
                    lhead += strlen(StringValuePtr(r));
                    strcat(hed, StringValuePtr(r));
                    strcat(hed, "\r\n");
                    lhead += 4;
                }
                strcat(hed, "\r\n");
                strcat(hed,prm);
                strcat(hed,"\r\n");
//                debug_inner("head \n");
//                debug_inner(hed);
                if (writeSocketSSL(hed, strlen(hed), ssl, &socet_fd) != -1) {
                    char * buf = readVDSocketSSL(&socet_fd,ssl);
                    close(socet_fd);
                    re = rb_enc_str_new_cstr(buf, rb_utf8_encoding());
                    free(buf);
                }
            }
        }
        return re;
    }

    VALUE getPosts(VALUE selt, VALUE url, VALUE prt, VALUE script, VALUE header, VALUE param) {
        return selt;
    }

    VALUE getPat(VALUE selt, VALUE url, VALUE prt, VALUE script, VALUE header, VALUE param) {
	return selt;
    }

    VALUE getPats(VALUE selt, VALUE url, VALUE prt, VALUE script, VALUE header, VALUE param) {
	return selt;
    }


#ifdef __cplusplus
}
#endif

#endif /* VDNET_H */

