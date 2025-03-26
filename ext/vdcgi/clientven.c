// #ifndef CLIENTVEN_H
// #define CLIENTVEN_H

#include "vdcgi.h"


#ifdef __cplusplus
extern "C" {
#endif
#include <netdb.h>


int get_conect_ven(char *host, int port){
    // debug_inner("net");
    // debug_inner(host);
    // debug_inner_int(port);
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof sin);
    sin.sin_family = AF_INET;
	sin.sin_port = htons((unsigned short) port);
	sin.sin_addr.s_addr = inet_addr(host);
    int socet_fd = -1;
    socet_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    fcntl(socet_fd, F_SETFL, O_NONBLOCK);
     if (socet_fd < 0) return -1;
     int z = 0;
     loop_s:
     if (connect(socet_fd, (struct sockaddr *) &sin, sizeof (sin)) != 0) {
           if (errno == EINPROGRESS) {
                // fprintf(stderr, "wait\n\n");
            } else {
    		     if(z < 3){
                    z++;
                    usleep(250);
                    goto loop_s;
                  }else 
                    return -1;
            }
	    } else {
            debug_inner("start conect");
            debug_inner_int(socet_fd);
		    return socet_fd;
	    }
        if(z < 3){
             z++;
             usleep(250);
            goto loop_s;
        }else 
        return -1;
	    
   

}




VALUE check_con(VALUE self){
    
    return rb_iv_get(self,"@socketv");
    // debug_inner_int(NUM2INT(rb_iv_get(self,"@socketv")));
}

VALUE getHeaderMes() {
    VALUE rezult = rb_hash_new();
    rb_hash_aset(rezult, rb_str_new2("flag"), INT2NUM(0));
    rb_hash_aset(rezult, rb_str_new2("type_mes"), INT2NUM(0));
    rb_hash_aset(rezult, rb_str_new2("login"), rb_str_new2(""));
    rb_hash_aset(rezult, rb_str_new2("passwd"), rb_str_new2(""));
    rb_hash_aset(rezult, rb_str_new2("size_body"), INT2NUM(0));
    return rezult;
}
VALUE getparamStart() {
    VALUE rezult = rb_hash_new();
    rb_hash_aset(rezult, rb_str_new2("type"), INT2NUM(0));
    rb_hash_aset(rezult, rb_str_new2("type_mes"), INT2NUM(0));
    rb_hash_aset(rezult, rb_str_new2("login"), rb_str_new2(""));
    rb_hash_aset(rezult, rb_str_new2("pass"), rb_str_new2(""));
    rb_hash_aset(rezult, rb_str_new2("len_body"), INT2NUM(0));
    rb_hash_aset(rezult, rb_str_new2("body"), rb_str_new2(""));
    return rezult;
}


VALUE get_conect(VALUE self, VALUE vd, VALUE ip, VALUE port, VALUE login, VALUE pass){
    rb_iv_set(self,"@conect", vd);
    int s = get_conect_ven(StringValuePtr(ip), NUM2INT(port));
    rb_iv_set(self,"@socketv", INT2NUM(s));
    rb_iv_set(self,"@HeaderMes", getHeaderMes());
    rb_iv_set(self,"@paramStart", getparamStart());
    rb_iv_set(self,"@flag_key", INT2NUM(0));
    rb_iv_set(self,"@login", login);
    rb_iv_set(self,"@pass", pass);

    
    return self;
}

// int getMask(char *bufheader,unsigned char *buff){
//     int ofset = 2;
//     int sh = getShortLen(bufheader);
//     if(sh==126) ofset = 4;
//     if(sh>126) return -1;
//     strncpy(buff,&bufheader[ofset],4);
//     return 0;
// }

char *codeMessage(VALUE self, char * message, int sz){
    VALUE key_o = rb_iv_get(self,"@keyven");
    char *key = StringValuePtr(key_o);
    // printf("cde key\n");
    // for(int i = 0; i<256;i++)
    //      printf("%c",key[i]);
    // printf("\n");     
    int ts;
    int posit_key;
    char *rezult = malloc(sz);
    if(NOCODE == 1){
        memcpy(rezult,message,sz);
        return rezult;
    }
    for(ts =0, posit_key = 0; ts < sz;ts++,posit_key++) {
        if(posit_key >=256)
            posit_key = 0;
        rezult[ts] = message[ts] ^ key[posit_key];

    }
    return rezult;
}

int createMes(char *body, int body_len, int type, char *rezult, char*login, char*pass) {
    
    HeaderMes header;
    int f = 0;
    if (type == 0){
        f |= (1 << 0);
    }
    f |= (1 << 2);
    
    header.flag = f;
    header.type_mes = type;
    header.size_body = body_len;
    
    memset(header.login,'\0',48);
    memset(header.passwd,'\0',128);
    memcpy(header.login,login,strlen(login));
    memcpy(header.passwd,pass,strlen(pass));
    memcpy(rezult,&header,sizeof(HeaderMes));
    
    int head_pos = sizeof(HeaderMes);
    memcpy(rezult+head_pos,body,body_len);
    
    return 0;

}


VALUE answerComand(VALUE self, VALUE type_m){
    int socet_fd = NUM2INT(rb_iv_get(self,"@socketv"));
    int type_mes = NUM2INT(type_m);
    int cnt_c = 0;
    int read_size = 0;
//            printf("cnt_c atart %i",cnt_c);
    read_size = 0;
    ParamStart param;
    while(cnt_c < 10) {
        char *read_b = readSoc(self, &read_size);
        printf("read_b %i\n",read_size);
        if(read_size == -1){
            rb_str_new2("socet_error");
        }else if (read_size > 0) {
            if(parseParamStart(self, read_b, &param) == -1)
                return Qnil;
            printf("param.type_mes: %i type_mes:%i\n",param.type_mes,type_mes);    
            if(param.type_mes == type_mes){
                
                char *mes = codeMessage(self, param.body, param.len_body);
                // printf("param.body: %s \nparam.len_body:%i\n",param.body,param.len_body);
                return rb_str_new2(mes);
            }else if(param.type_mes == 10){
                sendMessage(self, 11, "pong", strlen("pong")) ;
            }
        }
        cnt_c++;
        free(read_b);
        usleep(250);
    }
    read_size = 0;
    return Qnil;
}

VALUE remoteCmd(VALUE self, VALUE cmd, VALUE tps){
    int tp = NUM2INT(tps) ;
    char *cmdv = StringValueCStr(cmd);
    
    int rezult = sendMessage(self, tp, cmdv, strlen(cmdv)) ;
    
    // free(mes);
    return INT2NUM(rezult);
}

VALUE startMessage(VALUE self, VALUE id){
    // printf("read start 1 \n");
    char *id_u = StringValueCStr(id);
    int size_i = 0;

    sendMessage(self, 0, id_u, strlen(id_u) );
    // printf("read start 1 \n");
    int read_size = 0;
    char *read_b;
    ParamStart param;
    VALUE rezult = T_NIL;
    int z = 0;
    while(read_size == 0 && z < 60) {
        read_size = 0;
        read_b = readSoc(self, &read_size);
        if (read_size > 0) {
            if(parseParamStart(self,read_b, &param) == -1)
                break;
            // fprintf(stderr,"param socket %i | %i | %i | %s\n", param.type, param.type_mes, param.len_body, param.body);
            rezult = rb_str_new2(param.body);

            free(param.body);
            
        }else{
            z++;
        }
        free(read_b);
        usleep(250);
    }
    return rezult;
    
}

int writeSocketVen(VALUE self, char *mes, int len){
    int socet_fd = NUM2INT(rb_iv_get(self,"@socketv"));
    // printf("writeSocketVen_______%i___%i________\n",socet_fd,len);
    fd_set wfds;
	struct timeval tv;
	int start_len = len;
	int r = 0;
	int max_fd = -1;
	if (socet_fd > max_fd) max_fd = socet_fd;
	
	loop_w:
	FD_ZERO(&wfds);
	FD_SET(socet_fd, &wfds);
	tv.tv_sec = 3;
	tv.tv_usec = 500;
	
	select(max_fd + 1, NULL, &wfds, NULL, &tv);
	if (FD_ISSET(socet_fd, &wfds)) {
		
		int s = send(socet_fd, mes, len, 0);
		// printf("writeS_______%s___________\n",s);
		if(s == -1){
            if(errno == EAGAIN && r<start_len){
                goto loop_w;
            }else if(errno == EPIPE)
                return -1;
			return r;
        }
		if(s > -1){
			r += s;
		}
	    if(r<start_len){
			len -= s;
			mes += s;
			goto loop_w;
		}
			
	   
	}
    return r;

    
}


VALUE PingPong(VALUE self){
    int zi = 0;
    int size_read = 0;
    ParamStart param;
    while(zi < 4){
        size_read = 0;
        char *ans = readSoc(self, &size_read);
        if(size_read > 0){
            parseParamStart(self, ans, &param);
            if(param.type_mes == 10){
                int rezult = sendMessage(self, 11, "pong", strlen("pong")) ;
                free(ans);
                return INT2NUM(rezult);
            }

        }else if(size_read == -1)
            return INT2NUM(-1);
        zi++;
        free(ans);
        usleep(250);
    }
   
    return INT2NUM(-1);
}


int waitAnswer(VALUE self){
    int zi = 0;
    int size_read = 0;
    ParamStart param;
    while(zi < 40){
        size_read = 0;
        char *ans = readSoc(self, &size_read);
        if(size_read > 0){
            parseParamStart(self, ans, &param);
            if(param.type_mes == 31){
                free(ans);
                return 0;
            }

        }
        zi++;
        free(ans);
        usleep(250);
    }
    int k ;
    return -1;
}

int loadFile(VALUE self, char *pach){
   
    FILE *fl = fopen(pach, "r");

    if(fl != NULL){
        char*buf= malloc(4000-sizeof(HeaderMes) );
        int c;
        int size = 0;
        while (feof(fl) == 0){
            fgetc(fl);
            size++;
        }
        size--;
//        printf("file size %i\n",size);
        fseek(fl,0,SEEK_SET);
        int size_read = 0;
        while(size_read<size){
            int read_block = 0;
            memset(buf,'\0',4000-sizeof(HeaderMes));
            int c;
            while(size_read<size && read_block < 4000-sizeof(HeaderMes) ){

                buf[read_block] = fgetc(fl);
                read_block++;
                size_read++;
            }
            if(read_block>0){
                if(sendMessage(self, 30, buf, read_block ) > 0){
                    if(waitAnswer(self) == -1)
                        return -2;
                }else{
                    return -1;
                }
            }
        }
        free(buf);
    }else{
        return -3;
    }
    return 0;
}


int sendMessage(VALUE self, int type, unsigned char *body, int body_size ){
    
   
    char *message = malloc(sizeof(HeaderMes)+body_size+1);
    char *body_code;
    //  printf("len body %i flag %i\n",body_size,NUM2INT(rb_iv_get(self,"@flag_key")));
    if(NUM2INT(rb_iv_get(self,"@flag_key")) > 0){
        body_code = codeMessage(self, body, body_size);
    }
    if(type == 0 || type == 11){
        VALUE ss = rb_iv_get(self,"@login");
        VALUE pp = rb_iv_get(self,"@pass");
        char *login = StringValuePtr(ss);
        char *pass = StringValuePtr(pp);
        
        // printf("_____login:%s____pass:%s_______\n",login,pass);
        // printf("createMes body %s body_size %i type %i login %s pass %s\n",body,body_size,type, login, pass);
        createMes(body, body_size, type, message,login,pass);
        // printf("message1 %s\n",message);
    }else{
//        printf("body_code %s",body_code);
        createMes(body_code, body_size, type, message,"","");
        free(body_code);
    }
    // printf("message %s\n size %i\n",message+sizeof(HeaderMes), sizeof(HeaderMes)+body_size+1);
    int rezult_k = writeSocketVen(self, message, sizeof(HeaderMes)+body_size+1);
//    int rezult_k = send(*fd,message,sizeof(HeaderMes)+body_size+1,0);
    free(message);
    return rezult_k;

}

int parseParam(unsigned char* head, ParamStart *param){
    // ParamStart *param = malloc(sizeof(ParamStart));
   
    unsigned char head_mes[185];
    memset(head_mes,'\0',185);
    // rb_iv_set(VALUE obj, char *name, VALUE value);
    
    
    if ((head[0] & (1 << 0)) && (head[0] & (1 << 1))){
        param->type = 0;
       

    }else if(head[0] & (1 << 1) && !(head[0] & (1 << 0))){
        param->type = 1;
    }else if((head[0] & (1 << 0)) && (head[0] & (1 << 2))){
        param->type = 2;
    }else if(!(head[0] & (1 << 0)) && (head[0] & (1 << 2))){
        param->type = 3;
    }
    HeaderMes header;
    memcpy(&header,head,sizeof(HeaderMes));
    // VALUE rezult = rb_hash_new();
    param->type_mes = header.type_mes;
    strcpy(param->login, header.login);
    strcpy(param->pass, header.passwd);
    param->len_body =  header.size_body;
    
    return 0;
}

int parseParamStart(VALUE self, unsigned char* head, ParamStart *param){
    unsigned char head_mes[185];
    // printf("head %s",head);
    memset(head_mes,'\0',185);
    if ((head[0] & (1 << 0)) && (head[0] & (1 << 1))){
        param->type = 0;
    }else if(head[0] & (1 << 1) && !(head[0] & (1 << 0))){
        param->type = 1;
    }else if((head[0] & (1 << 0)) && (head[0] & (1 << 2))){
        param->type = 2;
    }else if(!(head[0] & (1 << 0)) && (head[0] & (1 << 2))){
        param->type = 3;
    }
    // printf("head 2");
    HeaderMes header;
    memcpy(&header,head,sizeof(HeaderMes));
    param->type_mes = header.type_mes;
    strcpy(param->login, header.login);
    strcpy(param->pass, header.passwd);
    if(header.size_body < 0)
        header.size_body = 0;
    param->len_body =  header.size_body;
    
    param->body = malloc(param->len_body+1);
    memset(param->body,'\0',param->len_body+1);
    int head_p = sizeof(HeaderMes);
    memcpy(param->body,head+head_p,param->len_body);
    if(param->len_body > LENMES || param->len_body < 1)
        return -1;
    if(param->type_mes == 2){
     
        rb_iv_set(self,"@flag_key", INT2NUM(1));
        rb_iv_set(self,"@keyven", rb_str_new(param->body,256));
        
    }
    return 0;
}

VALUE closeSockV(VALUE self){
    // sendMessage(self, 66, "close", strlen("close")) ;
    int socket_fd = NUM2INT(rb_iv_get(self,"@socketv"));
    close(socket_fd);
    return self;
}




char* readSoc(VALUE self, int *s){
    int socket_fd = NUM2INT(rb_iv_get(self,"@socketv"));
    // printf("reas sock %i\n",socket_fd);
    int buf_size = 1024 * 1024;
	char *buf =  malloc(buf_size);
	bzero(buf, buf_size);
	char *tmp =  (char*)malloc(buf_size);
	bzero(tmp, buf_size);
	int lr = 0;
	int kr = 0;
	int l = 0;
    int leh = 0;
	int r = buf_size;
	char *write;
	struct timeval tv;
	fd_set rfds, wfds;
	FD_ZERO(&rfds);
	FD_SET(socket_fd, &rfds);
	int max_fd = -1;
	if (socket_fd > max_fd) max_fd = socket_fd;
	tv.tv_sec = 1;
	tv.tv_usec = 500;
	select(max_fd + 1, &rfds, NULL, NULL, &tv);
    int readMax = 1024 * 1000000;
    int size = 0;
    int size_body = 0;
    char *starone;
    int head_s = 0;
    ParamStart parammessage;
	// debug_inner("star read");
	if (FD_ISSET(socket_fd, &rfds)) {
		// debug_inner("star read 1");
	     do {
            rec_r: 
            bzero(tmp, buf_size);
            l = recv(socket_fd, tmp, buf_size, 0);
            printf("recv %i\n",l);
			if(l == -1 && errno == ECONNREFUSED){
               free(tmp);
                *s = -1;
                return buf; 
            }
               if(l > 0){
                    size += l;
                    lr += l;
                    if (lr >= r) {
                            r += (buf_size * 2);
                            buf = realloc(buf, r);
                    }
                    write = buf + kr;
                    memcpy(write, tmp, l);
                    
                    if(kr == 0 && lr >= sizeof(HeaderMes)){
                        parseParam(buf, &parammessage);
                        size_body = parammessage.len_body + sizeof(HeaderMes);
                    }
                    if(l > 0) {
                        write = buf + kr;
                        memcpy(write, tmp, l);
                        memset(tmp, '\0', buf_size);
                        kr += l;
                    }    


                }
				FD_ZERO(&rfds);
           		FD_SET(socket_fd, &rfds);
				tv.tv_sec = 1;
                tv.tv_usec = 500;
                if(select(max_fd + 1, &rfds, NULL, NULL, &tv)<1){
					// debug_inner("break 1");
					break;
				 }
				if(!FD_ISSET(socket_fd, &rfds)){
					// debug_inner("break 2");
                    break;
                }	
	    } while (l > 0 && size_body > lr ) ;
	}
    free(tmp);
    *s = lr;
    return buf;

}


#ifdef __cplusplus
}
#endif

// #endif 