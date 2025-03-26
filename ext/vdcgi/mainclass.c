
#ifndef MAINCLASS_H
#define MAINCLASS_H

#include "vdcgi.h"


#ifdef __cplusplus
extern "C" {
#endif
#include "vdcgi.h"
    VALUE write_title(VALUE self, VALUE tg, VALUE idstr,VALUE idpstr){
	rb_encoding * en = rb_utf8_encoding();
    VALUE r = rb_enc_str_new_cstr(" ",en);
    if(TYPE(idstr) == T_NIL)
	idstr = rb_str_new2("0");
    if(TYPE(idpstr) == T_NIL)
	idpstr = rb_str_new2("0");
    if(TYPE(tg) == T_NIL)
	   tg = rb_str_new2("");
        char l[10];
        bzero(l,10);
        sprintf(l,"%i",level);
   char *p[5];
    p[0] = StringValuePtr(tg);
    p[1] = pref;
    p[2] = StringValuePtr(idstr);
    p[3] = StringValuePtr(idpstr);
    p[4] = l;
    Rezultsql rez;
    exsql(5, "select ~ from ~seotexts where str = '~' and pstr = '~' and level <= '~' order by level desc", p, &rez);
    if(rez.rows !=0 && rez.colun != 0){
	if(strcmp(rez.result[0][0],"null") != 0){
	    r = rb_enc_str_new_cstr(rez.result[0][0],en);
	}
	clearMysqRez(&rez);
    }
    return r;
    }
   
    VALUE get_listcontacts(VALUE self){
	rb_encoding * en = rb_utf8_encoding();
	VALUE rezult =  rb_hash_new();
	Rezultsql rez;
	char *p[1];
	exsql(0, "select name, adress, phone, mail, icq, skype, director, about, contract, frommail, server, port, login, passwd, sendmail from contacts limit 1", p, &rez);
	if( rez.rows > 0 && rez.colun > 0){
	    rb_hash_aset(rezult, rb_str_new2("name"), rb_enc_str_new_cstr(rez.result[0][0],en));
	    rb_hash_aset(rezult, rb_str_new2("adress"), rb_enc_str_new_cstr(rez.result[0][1],en));
	    rb_hash_aset(rezult, rb_str_new2("phone"), rb_enc_str_new_cstr(rez.result[0][2],en));
	    rb_hash_aset(rezult, rb_str_new2("mail"), rb_enc_str_new_cstr(rez.result[0][3],en));
	    rb_hash_aset(rezult, rb_str_new2("icq"), rb_enc_str_new_cstr(rez.result[0][4],en));
	    rb_hash_aset(rezult, rb_str_new2("skype"), rb_enc_str_new_cstr(rez.result[0][5],en));
	    rb_hash_aset(rezult, rb_str_new2("director"), rb_enc_str_new_cstr(rez.result[0][6],en));
	    rb_hash_aset(rezult, rb_str_new2("about"), rb_enc_str_new_cstr(rez.result[0][7],en));
	    rb_hash_aset(rezult, rb_str_new2("contract"), rb_enc_str_new_cstr(rez.result[0][8],en));
	    rb_hash_aset(rezult, rb_str_new2("frommail"), rb_enc_str_new_cstr(rez.result[0][9],en));
	    rb_hash_aset(rezult, rb_str_new2("server"), rb_enc_str_new_cstr(rez.result[0][10],en));
	    rb_hash_aset(rezult, rb_str_new2("port"), rb_enc_str_new_cstr(rez.result[0][11],en));
	    rb_hash_aset(rezult, rb_str_new2("login"), rb_enc_str_new_cstr(rez.result[0][12],en));
	    rb_hash_aset(rezult, rb_str_new2("passwd"), rb_enc_str_new_cstr(rez.result[0][13],en));
	    rb_hash_aset(rezult, rb_str_new2("sendmail"), rb_enc_str_new_cstr(rez.result[0][14],en));
	    clearMysqRez(&rez);
	}
	return rezult;
    }
    VALUE get_regionpage(VALUE self, VALUE id){
	if(TYPE(id) == T_NIL)
	    id = rb_str_new2("0");
	VALUE rezult;
	Rezultsql rez;
	char *p[2];
	p[0] = pref;
	p[1] = StringValuePtr(id);
	exsql(2, "select region_id from ~pages where id = '~'", p, &rez);
	if( rez.rows > 0 && rez.colun > 0){
	    rezult =  INT2FIX(atoi(rez.result[0][0]));
	    clearMysqRez(&rez);
	}
	return rezult;
    }


VALUE get_menu_img(VALUE self,VALUE id,VALUE parent,VALUE img ){
    if(TYPE(id) == T_NIL)
        id = rb_str_new2("0");
    if(TYPE(parent) == T_NIL)
        parent = rb_str_new2("0");
    if(TYPE(img) == T_NIL)
        img = rb_str_new2("1");
    VALUE rezult = rb_ary_new();
    Rezultsql rez;
    char l[10];
    bzero(l,10);
    sprintf(l,"%i",level);
    char *p[7];
    p[0] = pref;
    p[1] =  StringValuePtr(img);
    p[2] = pref;
    p[3] = pref;
    p[4] = l;
    p[5] = StringValuePtr(parent);
    p[6] = StringValuePtr(id);
    if(atoi(StringValuePtr(id)) != 0){
        exsql(7, "select id, title, text_iner, positions, (select link from ~seotexts where str = p.id and pstr = p.parent_id  limit 1) as link, (select  CONCAT('/images/~/page_photos/',parent_id,'/',body) from ~page_photosn where parent_id = p.id and prime != 1 limit 1) as img, parent_id, access  from ~pages p where  access <= '~' and parent_id = '~' and region_id = '~'  order by positions", p, &rez);
    }else{
        exsql(6, "select id, title, text_iner, positions, (select link from ~seotexts where str = p.id and pstr = p.parent_id  limit 1) as link, (select CONCAT('/images/~/page_photos/',parent_id,'/',body) from ~page_photosn where parent_id = p.id and prime != 1 limit 1) as img, parent_id, access  from ~pages p where  access <= '~' and parent_id = '~' and edit = '1'  order by positions", p, &rez);
    }
    if( rez.rows > 0 && rez.colun > 0){
        rb_encoding * en = rb_utf8_encoding();
        for(int i = 0; i < rez.rows; i++){
            VALUE temp = rb_hash_new();
            rb_hash_aset(temp, rb_str_new2("id"), rb_enc_str_new_cstr(rez.result[i][0], en)) ;
            rb_hash_aset(temp, rb_str_new2("title"), rb_enc_str_new_cstr(rez.result[i][1], en)) ;
            rb_hash_aset(temp, rb_str_new2("text_iner"), rb_enc_str_new_cstr(rez.result[i][2], en)) ;
            rb_hash_aset(temp, rb_str_new2("positions"), rb_enc_str_new_cstr(rez.result[i][3], en)) ;
            rb_hash_aset(temp, rb_str_new2("link"), rb_enc_str_new_cstr(rez.result[i][4], en)) ;
            rb_hash_aset(temp, rb_str_new2("img"), rb_enc_str_new_cstr(rez.result[i][5], en)) ;
            rb_hash_aset(temp, rb_str_new2("parent_id"), rb_enc_str_new_cstr(rez.result[i][6], en)) ;

            rb_ary_push(rezult,temp);
        }
        clearMysqRez(&rez);
    }
    return rezult;
}


    VALUE get_menu(VALUE self,VALUE id,VALUE parent ){
	if(TYPE(id) == T_NIL)
	    id = rb_str_new2("0");
	if(TYPE(parent) == T_NIL)
	    parent = rb_str_new2("0");
	VALUE rezult = rb_ary_new(); 
	Rezultsql rez;
	char l[10];
	bzero(l,10);
	sprintf(l,"%i",level);
	char *p[7];
	p[0] = pref;
    p[1] = "1";
	p[2] = pref;
	p[3] = pref;
	p[4] = l;
	p[5] = StringValuePtr(parent);
	p[6] = StringValuePtr(id);
	if(atoi(StringValuePtr(id)) != 0){
	exsql(7, "select id, title, text_iner, positions, (select CASE LENGTH(link)  WHEN 0 THEN link  ELSE CONCAT(link,'.html') END from ~seotexts where str = p.id and pstr = p.parent_id limit 1) as link, (select  CONCAT('/images/~/page_photos/',parent_id,'/',body) from ~page_photosn where parent_id = p.id and prime != 1 limit 1) as img, parent_id, access   from ~pages p where  access <= '~' and parent_id = '~' and region_id = '~'  order by positions", p, &rez);
	}else{
	exsql(6, "select id, title, text_iner, positions, (select CASE LENGTH(link)  WHEN 0 THEN link  ELSE CONCAT(link,'.html') END from ~seotexts where str = p.id and pstr = p.parent_id limit 1) as link, (select CONCAT('/images/~/page_photos/',parent_id,'/',body) from ~page_photosn where parent_id = p.id and prime != 1 limit 1) as img, parent_id, access   from ~pages p where  access <= '~' and parent_id = '~' and edit = '1'  order by positions", p, &rez);
	}
	if( rez.rows > 0 && rez.colun > 0){
	    rb_encoding * en = rb_utf8_encoding();
	    for(int i = 0; i < rez.rows; i++){
		VALUE temp = rb_hash_new();
		
		rb_hash_aset(temp, rb_str_new2("id"), rb_enc_str_new_cstr(rez.result[i][0], en)) ;
		rb_hash_aset(temp, rb_str_new2("title"), rb_enc_str_new_cstr(rez.result[i][1], en)) ;
		rb_hash_aset(temp, rb_str_new2("text_iner"), rb_enc_str_new_cstr(rez.result[i][2], en)) ;
		rb_hash_aset(temp, rb_str_new2("positions"), rb_enc_str_new_cstr(rez.result[i][3], en)) ;
		rb_hash_aset(temp, rb_str_new2("link"), rb_enc_str_new_cstr(rez.result[i][4], en)) ;
		rb_hash_aset(temp, rb_str_new2("img"), rb_enc_str_new_cstr(rez.result[i][5], en)) ;
		rb_hash_aset(temp, rb_str_new2("parent_id"), rb_enc_str_new_cstr(rez.result[i][6], en)) ;
        rb_hash_aset(temp, rb_str_new2("access"), rb_enc_str_new_cstr(rez.result[i][7], en)) ;
		 rb_ary_push(rezult,temp);
	    }
	    clearMysqRez(&rez);
	}
	return rezult;
    }
    
    VALUE get_javames(VALUE self){
	    
	char *rez = (char*)malloc(10000);
	bzero(rez,10000);
	strcat(rez,"1 :{");
	int wr = 0;
	int ex = 10000;
	char *p[1];
	p[0] = pref;
	Rezultsql rezsql;
	rb_encoding * en = rb_utf8_encoding();
	exsql(1, "select file, st, phrase from ~javames where file = 1 ", p, &rezsql);
	if( rezsql.rows > 0 && rezsql.colun > 0){
	    for(int i = 0; i < rezsql.rows; i++){
		if(wr >= ex - 1000){
		    rez = (char*)realloc(rez,(ex + 1000));
		    ex += 1000;
		} 
		strcat(rez,rezsql.result[i][1]);
		strcat(rez,": \"");
		strcat(rez,rezsql.result[i][2]);
		strcat(rez,"\", \n");
		
		wr += strlen(rezsql.result[i][1]);
		wr += strlen(rezsql.result[i][2]);
		wr += 10;
	    }
	
	    clearMysqRez(&rezsql);
	}
	strcat(rez,"0:\"\" },\n 2 : {");
	exsql(1, "select file, st, phrase from ~javames where file = 2 ", p, &rezsql);
	if( rezsql.rows > 0 && rezsql.colun > 0){
	     for(int i = 0; i < rezsql.rows; i++){
	    if(wr >= ex - 1000){
		rez = (char*)realloc(rez,(ex + 1000));
		ex += 1000;
	    } 
	    strcat(rez,rezsql.result[i][1]);
	    strcat(rez,": \"");
	    strcat(rez,rezsql.result[i][2]);
	    strcat(rez,"\", \n");
	    wr += strlen(rezsql.result[i][1]);
	    wr += strlen(rezsql.result[i][2]);
	    wr += 10;
	     }
	    clearMysqRez(&rezsql); 
	}
	strcat(rez,"0:\"\" }");
	VALUE rt = rb_enc_str_new_cstr(rez, rb_utf8_encoding()); 
	free(rez);
	return rt;
    }
    VALUE get_namepage(VALUE self, VALUE id){
	if(TYPE(id) == T_NIL)
	    id = rb_str_new2("0");
	 rb_encoding * en = rb_utf8_encoding();
	VALUE rezult = rb_enc_str_new_cstr("",en);
	Rezultsql rez;
	char *p[2];
	p[0] = pref;
	p[1] = StringValuePtr(id);
	exsql(2, "select title from  ~pages where id = ~", p, &rez);
	if( rez.rows > 0 && rez.colun > 0){
	    rezult = rb_enc_str_new_cstr(rez.result[0][0], en) ;
	    clearMysqRez(&rez);
	}
	return rezult;
    }
    VALUE get_accesspage(VALUE self, VALUE id){
	if(TYPE(id) == T_NIL)
	    id = rb_str_new2("0");
	VALUE rezult;
	Rezultsql rez;
	char l[100];
	bzero(l,100);
	sprintf(l,"%s",pref);
	char *p[2];
	p[0] = l;
	p[1] = StringValuePtr(id);
	exsql(2, "select access from ~pages where id = '~'", p, &rez);
	if( rez.rows > 0 && rez.colun > 0){
	    rezult = INT2FIX(atoi(rez.result[0][0])) ;
	    clearMysqRez(&rez);
	}
	return rezult;
    }
     VALUE get_class(VALUE self, VALUE id){

	 if(TYPE(id) == T_NIL)
	 id = rb_str_new2("0");
	VALUE rezult = rb_ary_new();
	if(TYPE(id) == T_STRING){
	    char *p[1];
	    p[0] = StringValuePtr(id);
	    Rezultsql rez;
	    exsql(1, "SELECT id, class FROM  class  WHERE id_str = '~' ", p, &rez);
	     if( rez.rows > 0 && rez.colun > 0){
		 rb_encoding * en = rb_utf8_encoding();
		    for(int i = 0; i < rez.rows; i++){
			VALUE temp = rb_hash_new();
			rb_hash_aset(temp, rb_str_new2("id"), rb_enc_str_new_cstr(rez.result[i][0], en)) ;
			rb_hash_aset(temp, rb_str_new2("class"), rb_enc_str_new_cstr(rez.result[i][1], en)) ;
			rb_ary_push(rezult,temp);
		    }
		 clearMysqRez(&rez);    
	     }
	}

	return rezult;
     }
    VALUE get_js(VALUE self, VALUE id, VALUE pid){
	if(TYPE(id) == T_NIL)
	    id = rb_str_new2("0");
	VALUE rezult = rb_ary_new();
	if(TYPE(id) == T_STRING){
	char *p[2];
	p[0] = StringValuePtr(id);
	p[1] = StringValuePtr(pid);
	Rezultsql rez;
	exsql(2, "SELECT id, js, css FROM  js  WHERE id_str = '~' and id_pstr = '~'", p, &rez);
	  if( rez.rows > 0 && rez.colun > 0){
	     rb_encoding * en = rb_utf8_encoding();
		for(int i = 0; i < rez.rows; i++){
		    VALUE temp = rb_hash_new();
		    rb_hash_aset(temp, rb_str_new2("id"), rb_enc_str_new_cstr(rez.result[i][0], en)) ;
		    rb_hash_aset(temp, rb_str_new2("js"), rb_enc_str_new_cstr(rez.result[i][1], en)) ;
		    rb_hash_aset(temp, rb_str_new2("css"), rb_enc_str_new_cstr(rez.result[i][2], en)) ;
		    rb_ary_push(rezult,temp);
		}
	     clearMysqRez(&rez);    
	 }
	}
	return rezult;
     }
    
    VALUE get_fotos(VALUE self, VALUE table,VALUE idfoto,VALUE size,VALUE plase,VALUE slider, VALUE microdata){
	if(TYPE(idfoto) == T_NIL)
	    idfoto = rb_str_new2("0");
	if(TYPE(size) == T_NIL)
	    size = rb_str_new2("0");
	if(TYPE(table) == T_NIL)
	    table = rb_str_new2("");
	if(TYPE(plase) == T_NIL)
	    plase = rb_str_new2("");
	if(TYPE(slider) == T_NIL)
	    slider = rb_str_new2("0");
	if(TYPE(microdata) == T_NIL)
	    microdata = rb_str_new2("0");
	VALUE rezult_ar = rb_ary_new();
	char pr[50];
	bzero(pr,50);
	if(!strstr(StringValuePtr(table),"user") && !strstr(StringValuePtr(table),"lang")){
	    strcpy(pr,pref);
	}
	char tablere[124], tablereb[124];
	bzero(tablere,124);
	bzero(tablereb,124);
	sprintf(tablere,"%s%s_photosn",pr,StringValuePtr(table));
	sprintf(tablereb,"%s_photos",StringValuePtr(table));
	Rezultsql rez;
	rb_encoding * en = rb_utf8_encoding();
	char *p[3];
	p[0] = tablere;
	p[1] = StringValuePtr(idfoto);
	p[2] = StringValuePtr(plase);
	if(atoi(StringValuePtr(plase)) != 0){
	    exsql(3, "SELECT body as img, alt, titl FROM  ~  WHERE parent_id = '~' order by prime desc limit ~", p, &rez);
	}else
	    exsql(2, "SELECT body as img, alt, titl FROM  ~  WHERE parent_id = '~' order by prime desc limit 1", p, &rez);
	    char *img = (char*)malloc(1024);
	    if( rez.rows > 0 && rez.colun > 0){
		for(int i = 0; i < rez.rows; i++){
		    int res = strlen(rez.result[0][0]) * 3;
		    if(res >= 800){
			rb_ary_push(rezult_ar, rb_enc_str_new_cstr("<img src=\"/img/no_img.png\" >", en)) ;
		    }else{
			bzero(img,1024);
			if(atoi(StringValuePtr(slider)) != 0){
			    sprintf(img,"<a class=\"highslide\" onclick=\"return hs.expand(this)\" href=\"/images/%s/%s/%s/%s\">",StringValuePtr(slider),tablereb,StringValuePtr(idfoto),rez.result[i][0]);
			}
			strcat(img,"<img ");
			if(atoi(StringValuePtr(microdata)) != 0){
			     strcat(img,"itemprop=\"image\" ");
			}
			strcat(img," alt=''");
			strcat(img,rez.result[i][1]);
			strcat(img," title=''");
			strcat(img,rez.result[i][2]);
			strcat(img," src='/images/");
			strcat(img,StringValuePtr(size));
			strcat(img,"/");
			strcat(img,tablereb);
			strcat(img,"/");
			strcat(img,StringValuePtr(idfoto));
			strcat(img,"/");
			strcat(img,rez.result[i][0]);
			strcat(img,"' >");
			if(atoi(StringValuePtr(slider)) != 0){
			     strcat(img,"</a>"); 
			 }
			rb_ary_push(rezult_ar,rb_enc_str_new_cstr(img, en));
		    }
		}
		
		clearMysqRez(&rez);    
	    }else{
		if(strstr(StringValuePtr(table),"user")){
		    rb_ary_push(rezult_ar, rb_enc_str_new_cstr("<img alt=\"Пользователь пока не загрузил аватарку\" title=\"Пользователь пока не загрузил аватарку\" src=\"/img/noimg.png\" >", en)) ;
		}else{
		   rb_ary_push(rezult_ar, rb_enc_str_new_cstr("<img src=\"/img/no_img.png\" >", en)) ;
		}
		
	    }
	free(img);    
	return rezult_ar;
    }
    VALUE get_fotoslink(VALUE self, VALUE table,VALUE idfoto,VALUE size,VALUE plase){
	if(TYPE(idfoto) == T_NIL)
	    idfoto = rb_str_new2("0");
	if(TYPE(size) == T_NIL)
	    size = rb_str_new2("0");
	if(TYPE(table) == T_NIL)
	    table = rb_str_new2("");
	if(TYPE(plase) == T_NIL)
	    plase = rb_str_new2("");
	VALUE rezult_ar = rb_ary_new();
	char pr[50];
	bzero(pr,50);
	if(!strstr(StringValuePtr(table),"user") && !strstr(StringValuePtr(table),"lang")){
	    strcpy(pr,pref);
	}
	char tablere[124], tablereb[124];
	bzero(tablere,124);
	bzero(tablereb,124);
	sprintf(tablere,"%s%s_photosn",pr,StringValuePtr(table));
	sprintf(tablereb,"%s%s_photos",pr,StringValuePtr(table));
	Rezultsql rez;
	rb_encoding * en = rb_utf8_encoding();
	char *p[3];
	p[0] = tablere;
	p[1] = StringValuePtr(idfoto);
	p[2] = StringValuePtr(plase);
	if(atoi(StringValuePtr(plase)) != 0){
	    exsql(3, "SELECT body as img, alt, titl FROM  ~  WHERE parent_id = '~' order by prime desc limit ~", p, &rez);
	}else
	    exsql(2, "SELECT body as img, alt, titl FROM  ~  WHERE parent_id = '~' order by prime desc limit 1", p, &rez);
	    if( rez.rows > 0 && rez.colun > 0){
		for(int i = 0; i < rez.rows; i++){

		    if(strlen(rez.result[i][0]) < 1024){
		    char img[1024];
		    bzero(img,1024);
		    strcat(img,"/images/");
		    strcat(img,StringValuePtr(size));
		    strcat(img,"/");
		    strcat(img,tablereb);
		    strcat(img,"/");
		    strcat(img,StringValuePtr(idfoto));
		    strcat(img,"/");
		    strcat(img,rez.result[i][0]);
		    rb_ary_push(rezult_ar,rb_enc_str_new_cstr(img, en));
		    }

		}
		clearMysqRez(&rez);    
	    }
	return rezult_ar;
    }
    VALUE sendmail(VALUE self, VALUE to, VALUE them, VALUE message, VALUE frommail){
//    	 fprintf(stderr,"start message\n\n"); 
	if(TYPE(to) == T_NIL)
	    to = rb_str_new2("0");
	if(TYPE(them) == T_NIL)
	    them = rb_str_new2("");
	if(TYPE(message) == T_NIL)
	    message = rb_str_new2("");
	if(TYPE(frommail) == T_NIL)
	    frommail = rb_str_new2("");
	char * to_c = StringValuePtr(to);
	char * them_c = StringValuePtr(them);
	char * message_c = StringValuePtr(message);
//		fprintf(stderr,"message_c %s\n\n",message_c);
	char * frommail_c = StringValuePtr(frommail);
	Rezultsql  rezult;
	Rezultsql  rezult1;
	rezult1.rows = 0;
	char *p[0];
	exsql(0, "select frommail, server, port, login, passwd from contacts ", p,&rezult);
		if(rezult.colun != 0 && rezult.rows != 0){
	    char *torez = StringValuePtr(to);
	    if(strstr(StringValuePtr(to),"@") == 0){
		char *pp[1];
		pp[0] = to_c;
		exsql(1, "select mail from users where id = '~' ", pp,&rezult1);
		if(rezult1.colun != 0 && rezult1.rows != 0){
		    torez = rezult1.result[0][0];
		}
	    }
	    
	    int len = strlen(rezult.result[0][0]) + strlen(torez) + strlen(message_c) + strlen(them_c) + 128;
	    char *cmd = (char*)malloc(len);
	    bzero(cmd,len);
	    sprintf(cmd,"echo '%s' | mail -a 'MIME-Version: 1.0\nContent-type: text/html; charset=utf-8\nContent-Transfer-Encoding: 8bit\n'  -s '%s' -r '%s'  %s",message_c,them_c,rezult.result[0][0],torez);
//	    fprintf(stderr,"cmd %s\n\n",cmd);
	    if(system(cmd)){
		free(cmd);
	    }
	    if(rezult1.rows != 0) clearMysqRez(&rezult1);
	    clearMysqRez(&rezult);
	}
	
	return rb_str_new2("mail_send");
    }
    VALUE get_listcounryactin(VALUE self){
	VALUE rezult = rb_ary_new();
	char *p[1];
	Rezultsql rez;
	rb_encoding * en = rb_utf8_encoding();
	exsql(0, "select country_id, name from countries where country_id in (select country_id from country_activ)", p, &rez);
	 if( rez.rows > 0 && rez.colun > 0){
	    for(int i = 0; i < rez.rows; i++){
		VALUE temp = rb_hash_new();
		rb_hash_aset(temp, rb_str_new2("country_id"), rb_enc_str_new_cstr(rez.result[i][0], en)) ;
		rb_hash_aset(temp, rb_str_new2("name"), rb_enc_str_new_cstr(rez.result[i][1], en)) ;
		rb_ary_push(rezult,temp);
	    }
	    clearMysqRez(&rez);    
	 }
	return rezult;
    }

    void gel_list_lang_iner(Rezultsql *rez){
        char *p[1];
        exsql(0, "select id, name, pref from langs", p, rez);
        rb_encoding * en = rb_utf8_encoding();
        if( rez->rows > 0 && rez->colun > 0){
            for(int i = 0; i < rez->rows; i++){
                VALUE temp = rb_hash_new();
                rb_hash_aset(temp, rb_str_new2("id"), rb_enc_str_new_cstr(rez->result[i][0], en)) ;
                rb_hash_aset(temp, rb_str_new2("name"), rb_enc_str_new_cstr(rez->result[i][1], en)) ;
                rb_hash_aset(temp, rb_str_new2("pref"), rb_enc_str_new_cstr(rez->result[i][2], en)) ;
            }
        }
    }

    VALUE get_listlang(VALUE self){
	VALUE rezult = rb_ary_new();
	char *p[1];
	Rezultsql rez;
	rb_encoding * en = rb_utf8_encoding();
	exsql(0, "select id, name, pref from langs", p, &rez);
	 if( rez.rows > 0 && rez.colun > 0){
	    for(int i = 0; i < rez.rows; i++){
		VALUE temp = rb_hash_new();
		rb_hash_aset(temp, rb_str_new2("id"), rb_enc_str_new_cstr(rez.result[i][0], en)) ;
		rb_hash_aset(temp, rb_str_new2("name"), rb_enc_str_new_cstr(rez.result[i][1], en)) ;
		rb_hash_aset(temp, rb_str_new2("pref"), rb_enc_str_new_cstr(rez.result[i][2], en)) ;
		rb_ary_push(rezult,temp);
	    }
	    clearMysqRez(&rez);    
	 }
	return rezult;
    }
    VALUE get_langs(VALUE self, VALUE id){
	if(TYPE(id) == T_NIL)
	id = rb_str_new2("0");
	VALUE rezult = rb_hash_new();
	char *p[1];
	p[0] = StringValuePtr(id);
	Rezultsql rez;
	rb_encoding * en = rb_utf8_encoding();
	exsql(1, "select id, name, pref from langs where id = '~'", p, &rez);
	 if( rez.rows > 0 && rez.colun > 0){
	    rb_hash_aset(rezult, rb_str_new2("id"), rb_enc_str_new_cstr(rez.result[0][0], en)) ;
	    rb_hash_aset(rezult, rb_str_new2("name"), rb_enc_str_new_cstr(rez.result[0][1], en)) ;
	    rb_hash_aset(rezult, rb_str_new2("pref"), rb_enc_str_new_cstr(rez.result[0][2], en)) ;
	    clearMysqRez(&rez);    
	 }
	return rezult;
    }
    VALUE get_link(VALUE self, VALUE str, VALUE pstr, VALUE ppstr, VALUE reg ){
        rb_encoding * en = rb_utf8_encoding();
        if (strlen(getenv("HTTP_HOST")) > 900)
            return rb_enc_str_new_cstr("/", en);
	if(TYPE(str) == T_NIL)
	    str = rb_str_new2("0");
	if(TYPE(pstr) == T_NIL)
	    pstr = rb_str_new2("0");
	if(TYPE(ppstr) == T_NIL)
	    ppstr = rb_str_new2("0");
	if(TYPE(reg) == T_NIL)
	    reg = rb_str_new2("0");
	
    char url[128];
    bzero(url,128);
    strcpy(url,config.url);
	char * prot = strtok(url,":");
	char dom[1024];
	bzero(dom,1024);
    sprintf(dom,"%s://%s/",prot,getenv("HTTP_HOST"));
    
	VALUE rezult = rb_enc_str_new_cstr(dom, en);
	Rezultsql rez;
	char pr[50];
	bzero(pr,50);
	strcpy(pr,pref);
	char *p[5];
	p[0] = pr;
	p[1] = StringValuePtr(str);	
	p[2] = StringValuePtr(pstr);
	p[3] = StringValuePtr(ppstr);
	p[4] = StringValuePtr(reg);
	exsql(5, "select link from ~seotexts where str = '~' and pstr = '~' and level <= '~' and user_id = '~' ", p, &rez);
	 if( rez.rows > 0 && rez.colun > 0){
		 if(strlen(rez.result[0][0])>1){
		VALUE r = rb_str_append(rb_enc_str_new_cstr(rez.result[0][0], en),rb_enc_str_new_cstr(".html", en));
		rezult = rb_str_append(rezult, r);
		 }
	    clearMysqRez(&rez);    
	 }
	return rezult;
    }
    VALUE get_region_ex(VALUE self){
	VALUE rezult = rb_ary_new();
	Rezultsql rez;
	char *p[1];
	exsql(0, "select region_exist.id as id, region_exist.sity_id as region_exist_sity_id, sity.sity as sity  from region_exist left join sity on sity.id = region_exist.sity_id", p, &rez);
	if( rez.rows > 0 && rez.colun > 0){
	    rb_encoding * en = rb_utf8_encoding();
	    for(int i = 0; i < rez.rows; i++){
		VALUE temp = rb_hash_new();
		rb_hash_aset(temp, rb_str_new2("id"), rb_enc_str_new_cstr(rez.result[i][0], en)) ;
		rb_hash_aset(temp, rb_str_new2("region_exist_sity_id"), rb_enc_str_new_cstr(rez.result[i][1], en)) ;
		rb_hash_aset(temp, rb_str_new2("sity"), rb_enc_str_new_cstr(rez.result[i][2], en)) ;
		rb_ary_push(rezult,temp);
	    }
	    clearMysqRez(&rez);
	}
	return rezult;
    }
    VALUE get_cityname(VALUE self, VALUE id){
	if(TYPE(id) == T_NIL)
	    id = rb_str_new2("0");
	VALUE rezult = rb_str_new2("");
	Rezultsql rez;
	char *p[1];
	p[0] = StringValuePtr(id);
	exsql(0, "select sity from sity where id = '~'", p, &rez);
	if( rez.rows > 0 && rez.colun > 0){
	    rezult = rb_enc_str_new_cstr(rez.result[0][0], rb_utf8_encoding());
	    clearMysqRez(&rez);
	}
	return rezult;
    }
#ifdef __cplusplus
}
#endif

#endif /* MAINCLASS_H */

