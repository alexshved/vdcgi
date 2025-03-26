

#ifndef ARTICLE_H
#define ARTICLE_H

#include "vdcgi.h"


#ifdef __cplusplus
extern "C" {
#endif
#include "vdcgi.h"
    VALUE get_conuntarticle(VALUE self){
	VALUE rezult =  INT2FIX(0);
	Rezultsql rez;
	char *p[1];
	p[0] = pref;
	exsql(1, "select count(id) as id from ~articles", p, &rez);
	if( rez.rows > 0 && rez.colun > 0){
	    rezult =  INT2FIX(atoi(rez.result[0][0]));
	    clearMysqRez(&rez);
	}
	return rezult;
    }
    VALUE get_conuntarticlenew(VALUE self,VALUE period){
	if(TYPE(period) == T_NIL)
	    period = rb_str_new2("0");
	VALUE rezult =  INT2FIX(0);
	Rezultsql rez;
	char *p[2];
	p[0] = pref;
	p[1] = StringValuePtr(period);
	exsql(2, "select count(id) as id from ~articles where NOW() < DATE_ADD(date_create, interval ~ DAY) ", p, &rez);
	if( rez.rows > 0 && rez.colun > 0){
	    rezult =  INT2FIX(atoi(rez.result[0][0]));
	    clearMysqRez(&rez);
	}
	return rezult;
    }
    VALUE get_listarticles(VALUE self,VALUE sort,VALUE start){
	if(TYPE(sort) == T_NIL)
	    sort = rb_str_new2("0");
	if(TYPE(start) == T_NIL)
	    start = rb_str_new2("0");
	VALUE rezult = rb_ary_new();
	int srt = atoi(StringValuePtr(sort));
	int st = atoi(StringValuePtr(start));
	char limit[100];
	bzero(limit,100);
	if(st == 0){
	    sprintf(limit," limit %s", config.limit);
	} else {
	    sprintf(limit," limit %s , %s",StringValuePtr(start), config.limit);
	}
	char whr[100];
	bzero(whr,100);
	switch(srt){
	    case 1:
		strcpy(whr,"order by name");
		break;
	    case 2:
		strcpy(whr,"order by lid");
		break;
	    case 3:
		strcpy(whr,"order by body");
		break;
	    case 4:
		strcpy(whr,"order by lk");
		break;
	    case 5:
		strcpy(whr,"order by user_id");
		break;
	    case 6:
		strcpy(whr,"order by dt desc");
		break;
	   default:
		strcpy(whr,"order by id desc");
		break;
	}
	Rezultsql rez;
	
	char *p[3];
	p[0] = pref;
	p[1] = whr;
	p[2] = limit;
	exsql(3, "select id, name, lid, body, lk, user_id, Date_Format(date_create,'%d-%m-%Y') as dt  from ~articles a ~ ~", p, &rez);
	if( rez.rows > 0 && rez.colun > 0){
	    rb_encoding * en = rb_utf8_encoding();
	    for(int i = 0; i < rez.rows; i++){
		VALUE temp = rb_hash_new();
		rb_hash_aset(temp, rb_str_new2("id"), rb_enc_str_new_cstr(rez.result[i][0], en)) ;
		rb_hash_aset(temp, rb_str_new2("name"), rb_enc_str_new_cstr(rez.result[i][1], en)) ;
		rb_hash_aset(temp, rb_str_new2("lid"), rb_enc_str_new_cstr(rez.result[i][2], en)) ;
		rb_hash_aset(temp, rb_str_new2("body"), rb_enc_str_new_cstr(rez.result[i][3], en)) ;
		rb_hash_aset(temp, rb_str_new2("lk"), rb_enc_str_new_cstr(rez.result[i][4], en)) ;
		rb_hash_aset(temp, rb_str_new2("user_id"), rb_enc_str_new_cstr(rez.result[i][5], en)) ;
		rb_hash_aset(temp, rb_str_new2("dt"), rb_enc_str_new_cstr(rez.result[i][6], en)) ;
		 rb_ary_push(rezult,temp);
	    }
	    clearMysqRez(&rez);
	}
	return rezult;
    }
    VALUE set_readarticle(VALUE self,VALUE user,VALUE article){
	if(TYPE(user) == T_NIL)
	    user = rb_str_new2("0");
	if(TYPE(article) == T_NIL)
	    article = rb_str_new2("0");
	char *p[3];
	p[0] = pref;
	p[1] = StringValuePtr(article);
	p[2] =StringValuePtr(user);
	execsql(3, "insert ~view_article set article_id = '~', user_id = '~'", p);
	return self;
    }
    VALUE get_readarticle(VALUE self,VALUE user,VALUE article){
	if(TYPE(user) == T_NIL)
	    user = rb_str_new2("0");
	if(TYPE(article) == T_NIL)
	    article = rb_str_new2("0");
	VALUE rezult =  INT2FIX(0);
	Rezultsql rez;
	char *p[3];
	p[0] = pref;
	p[1] = StringValuePtr(article);
	p[2] =StringValuePtr(user);
	exsql(3, "select count(id) as id from ~view_article where article_id = '~' and user_id = '~'", p, &rez);
	if( rez.rows > 0 && rez.colun > 0){
	    rezult =  INT2FIX(atoi(rez.result[0][0]));
	    clearMysqRez(&rez);
	}
	return rezult;
    }
    
    VALUE set_articles(VALUE self, VALUE idr, VALUE name,VALUE lid,VALUE body,VALUE autor,VALUE access,VALUE block,VALUE user_id,VALUE product_id,VALUE category_id,VALUE link_s,VALUE subsubcategory_id, VALUE titl, VALUE keyw, VALUE descr){
	if(TYPE(idr) == T_NIL)
	    idr = rb_str_new2("0");
	if(TYPE(name) == T_NIL)
	    name = rb_str_new2("");
	if(TYPE(name) == T_NIL)
	    name = rb_str_new2("");
	if(TYPE(lid) == T_NIL)
	    lid = rb_str_new2("");
	if(TYPE(name) == T_NIL)
	    name = rb_str_new2("");
	if(TYPE(body) == T_NIL)
	    body = rb_str_new2("");
	if(TYPE(autor) == T_NIL)
	    autor = rb_str_new2("");
	if(TYPE(access) == T_NIL)
	    access = rb_str_new2("0");
	if(TYPE(user_id) == T_NIL)
	    user_id = rb_str_new2("0");
	if(TYPE(block) == T_NIL)
	    block = rb_str_new2("0");
	if(TYPE(product_id) == T_NIL)
	    product_id = rb_str_new2("0");
	if(TYPE(link_s) == T_NIL)
	    link_s = rb_str_new2("_");
	if(TYPE(category_id) == T_NIL)
	    category_id = rb_str_new2("0");
	if(TYPE(subsubcategory_id) == T_NIL)
	    subsubcategory_id = rb_str_new2("0");
	if(TYPE(titl) == T_NIL)
	    titl = rb_str_new2("");
	if(TYPE(keyw) == T_NIL)
	    keyw = rb_str_new2("");
	if(TYPE(descr) == T_NIL)
	    descr = rb_str_new2("");
	int id = atoi(StringValuePtr(idr));
	int ins_id = 0;
	char *pp[3];
	pp[0] = pref;
	pp[1] = StringValuePtr(idr);
	pp[2] = StringValuePtr(category_id);
	execsql(3, "update ~seotexts set link = '' where str = '~' and pstr = '~' ", pp);
	char *tmp;
	if(strlen(StringValuePtr(link_s)) < 3){
	    tmp = translitEngl(StringValuePtr(name));
	}else{
	    tmp = (char*)malloc(strlen(StringValuePtr(link_s)) + 1);
	    strcpy(tmp,StringValuePtr(link_s));
	}
	    
	char *temp = (char*)malloc(strlen(tmp) + 124);
	bzero(temp,(strlen(tmp) + 124));
	strcpy(temp,tmp);
	char *link = (char*)malloc(strlen(tmp) + 124);
	bzero(link,(strlen(tmp) + 124));
	char *pt[2];
	pt[0] = pref;
	pt[1] = temp;
	test: ;
	Rezultsql rez;
	exsql(2, "select id from ~seotexts where link = '~'", pt, &rez);
	if(rez.colun != 0 && rez.rows != 0){
	    clearMysqRez(&rez);
	    strcat(temp,"1");
	    
	    goto test;
	}else{
	    strcpy(link,temp);
	}
	
	free(tmp);
	free(temp);
	char *p[13];
	p[0] = pref;
	p[1] = StringValuePtr(name);
	p[2] = StringValuePtr(lid);
	p[3] = StringValuePtr(body);
	p[4] = StringValuePtr(autor);
	p[5] = StringValuePtr(access);
	p[6] = StringValuePtr(block);
	p[7] = StringValuePtr(user_id);
	p[8] = StringValuePtr(product_id);
	p[9] = StringValuePtr(category_id);
	p[10] = "0";
	p[11] = StringValuePtr(subsubcategory_id);
	p[12] = StringValuePtr(idr);
	
	if(id > 1000000){
	    execsql(12, "insert ~articles set name = '~', lid = '~',body = '~', autor = '~', access = '~',block = '~', user_id = '~', product_id = '~',category_id = '~', subcategory_id = '~', subsubcategory_id = '~' ", p);
	}else{
	    execsql(13, "update ~articles set name = '~', lid = '~',body = '~', autor = '~', access = '~',block = '~', user_id = '~', product_id = '~',category_id = '~', subcategory_id = '~', subsubcategory_id = '~' where id = '~' ", p);
	}
	char in_id[12];
	bzero(in_id,12);
	if(id > 1000000){
        ins_id = InsIdInt();
        sprintf(in_id,"%i",ins_id);
	}else{
	    ins_id = id;
	    sprintf(in_id,"%i",ins_id);
	}
    if(id <= 1000000){
	char *pa[7];
	pa[0] = pref;
	pa[1] = link;
	pa[2] = StringValuePtr(titl);
	pa[3] = StringValuePtr(keyw);
	pa[4] = StringValuePtr(descr);
	pa[5] = StringValuePtr(category_id);
	pa[6] = in_id;
	execsql(7, "update ~seotexts set link = '~', titl = '~', keyw = '~', descr = '~' where pstr = '~' and str = '~';", pa);
    }else{
	char *pa[7];
	pa[0] = pref;
	pa[1] = link;
	pa[2] = StringValuePtr(titl);
	pa[3] = StringValuePtr(keyw);
	pa[4] = StringValuePtr(descr);
	pa[5] = in_id;
	pa[6] = StringValuePtr(category_id);
	execsql(7, "insert ~seotexts set link = '~', titl = '~', keyw = '~', descr = '~', str = '~', pstr = '~', shablon = 'article.rhtml';", pa);
    }
   if(id > 1000000){
	    char *ps[3];
	    ps[0] = pref;
	    ps[1] = in_id;
	    ps[2] = StringValuePtr(idr);
	    execsql(3, "update ~article_photosn set parent_id = '~' where parent_id = '~';", ps);
	    char *root = getenv("DOCUMENT_ROOT");
	    char pch[400];
	    bzero(pch,400);
	    strcpy(pch,root);
	    strcat(pch,"/images");
	    DIR  * dir = opendir(pch);
	    struct dirent * dirEntry;
	    if (dir) {
		while (0 != (dirEntry = readdir(dir))) {
		    if(strcmp(dirEntry->d_name,".") != 0 && strcmp(dirEntry->d_name,"..") != 0){
			char chk[400];
            char dirtemp[400];
			bzero(chk,400);
            bzero(dirtemp,400);
			sprintf(chk,"%s/images/%s/article_photos/%s",root,dirEntry->d_name,in_id);
            sprintf(dirtemp,"%s/images/%s/article_photos/%s",root,dirEntry->d_name,StringValuePtr(idr));
			DIR  * direx = opendir(dirtemp);
			if(direx){
			    closedir(direx);
			    char cmd[400];
			    bzero(cmd,400);
                sprintf(cmd,"mv -u %s/images/%s/article_photos/%s %s/images/%s/article_photos/%s\n",root, dirEntry->d_name, StringValuePtr(idr), root, dirEntry->d_name, in_id);
			    system(cmd);
			}else{
			    mkdir(chk,0775);
//			    char cmd[400];
//			    bzero(cmd,400);
//			    sprintf(cmd,"mv -u %s/images/%s/article_photos/%s %s/images/%s/article_photos/%s\n",root, dirEntry->d_name, StringValuePtr(idr), root, dirEntry->d_name, in_id);
//                debug_inner_c("cmd 2",cmd)    ;
//			    system(cmd);
			}
		    }
		}
		closedir(dir);
	      }
    }
	//free(ins_id);
	free(link);
    
	return INT2FIX(ins_id);
    }
    
    
    VALUE get_articles(VALUE self,VALUE id){
	if(TYPE(id) == T_NIL)
	    id = rb_str_new2("0");
	char l[10];
	bzero(l,10);
	sprintf(l,"%i",level);
	VALUE rezult = rb_hash_new();
	char *p[4];
	p[0] = pref;
	p[1] = StringValuePtr(id);
	p[2] = l;
	Rezultsql rez;
	exsql(3, "select id, name, lid, body, user_id, product_id, category_id, subcategory_id, subsubcategory_id, Date_Format(date_create,'%d.%m.%Y | %h:%i') as dt, wv, autor, access, lk from ~articles a where id = '~' and access <= '~'", p, &rez);
	if( rez.rows > 0 && rez.colun > 0){
	    rb_encoding * en = rb_utf8_encoding();
	   	rb_hash_aset(rezult, rb_str_new2("id"), rb_enc_str_new_cstr(rez.result[0][0], en)) ;
		rb_hash_aset(rezult, rb_str_new2("name"), rb_enc_str_new_cstr(rez.result[0][1], en)) ;
		rb_hash_aset(rezult, rb_str_new2("lid"), rb_enc_str_new_cstr(rez.result[0][2], en)) ;
		rb_hash_aset(rezult, rb_str_new2("body"), rb_enc_str_new_cstr(rez.result[0][3], en)) ;
		rb_hash_aset(rezult, rb_str_new2("user_id"), rb_enc_str_new_cstr(rez.result[0][4], en)) ;
		rb_hash_aset(rezult, rb_str_new2("product_id"), rb_enc_str_new_cstr(rez.result[0][5], en)) ;
		rb_hash_aset(rezult, rb_str_new2("category_id"), rb_enc_str_new_cstr(rez.result[0][6], en)) ;
		rb_hash_aset(rezult, rb_str_new2("subcategory_id"), rb_enc_str_new_cstr(rez.result[0][7], en)) ;
		rb_hash_aset(rezult, rb_str_new2("subsubcategory_id"), rb_enc_str_new_cstr(rez.result[0][8], en)) ;
		rb_hash_aset(rezult, rb_str_new2("dt"), rb_enc_str_new_cstr(rez.result[0][9], en)) ;
		rb_hash_aset(rezult, rb_str_new2("wv"), rb_enc_str_new_cstr(rez.result[0][10], en)) ;
		rb_hash_aset(rezult, rb_str_new2("autor"), rb_enc_str_new_cstr(rez.result[0][11], en)) ;
		rb_hash_aset(rezult, rb_str_new2("access"), rb_enc_str_new_cstr(rez.result[0][12], en)) ;
		rb_hash_aset(rezult, rb_str_new2("lk"), rb_enc_str_new_cstr(rez.result[0][13], en)) ;
	    clearMysqRez(&rez);
	}else{
	    rb_encoding * en = rb_utf8_encoding();
	    rb_hash_aset(rezult, rb_str_new2("id"),  rb_enc_str_new_cstr("0", en)) ;
	    rb_hash_aset(rezult, rb_str_new2("id"),  rb_enc_str_new_cstr("0", en)) ;
	    rb_hash_aset(rezult, rb_str_new2("name"),  rb_enc_str_new_cstr("", en)) ;
	    rb_hash_aset(rezult, rb_str_new2("lid"),  rb_enc_str_new_cstr("", en)) ;
	    rb_hash_aset(rezult, rb_str_new2("body"),  rb_enc_str_new_cstr("", en)) ;
	    rb_hash_aset(rezult, rb_str_new2("user_id"),  rb_enc_str_new_cstr("0", en)) ;
	    rb_hash_aset(rezult, rb_str_new2("product_id"),  rb_enc_str_new_cstr("0", en)) ;
	    rb_hash_aset(rezult, rb_str_new2("category_id"),  rb_enc_str_new_cstr("0", en)) ;
	    rb_hash_aset(rezult, rb_str_new2("subcategory_id"),  rb_enc_str_new_cstr("0", en)) ;
	    rb_hash_aset(rezult, rb_str_new2("subsubcategory_id"),  rb_enc_str_new_cstr("0", en)) ;
	    rb_hash_aset(rezult, rb_str_new2("dt"),  rb_enc_str_new_cstr("", en)) ;
	    rb_hash_aset(rezult, rb_str_new2("autor"),  rb_enc_str_new_cstr("0", en)) ;
	    rb_hash_aset(rezult, rb_str_new2("access"),  rb_enc_str_new_cstr("0", en)) ;
	    rb_hash_aset(rezult, rb_str_new2("lk"),  rb_enc_str_new_cstr("0", en)) ;
	}
	return rezult;
	
    }
    VALUE set_comment_article(VALUE self,VALUE article_id,VALUE user_id, VALUE body){
	if(TYPE(article_id) == T_NIL)
	    article_id = rb_str_new2("0");
	if(TYPE(user_id) == T_NIL)
	    user_id = rb_str_new2("0");
	if(TYPE(body) == T_NIL)
	    body = rb_str_new2("");
	char *p[4];
	p[0] = pref;
	p[1] = StringValuePtr(article_id);
	p[2] = StringValuePtr(user_id);
	p[3] = StringValuePtr(body);
	execsql(4, "insert ~viecomments_article set article_id = '~', user_id = '~', body = '~'", p);
	return self;
    }
    VALUE set_wiewart(VALUE self,VALUE id){
	if(TYPE(id) == T_NIL)
	id = rb_str_new2("0");
	char *p[2];
	p[0] = pref;
	p[1] = StringValuePtr(id);
	execsql(2, "update ~articles set wv = wv + 1 where id = '~'", p);
	return self;
    }
    VALUE get_countcomentrticle(VALUE self,VALUE id){
	if(TYPE(id) == T_NIL)
	    id = rb_str_new2("0");
	VALUE rezult =  INT2FIX(0);
	Rezultsql rez;
	char *p[2];
	p[0] = pref;
	p[1] = StringValuePtr(id);
	exsql(2, "select count(id) cn from ~comments_article where article_id = '~' and  rd = 1", p, &rez);
	if( rez.rows > 0 && rez.colun > 0){
	    rezult =  INT2FIX(atoi(rez.result[0][0]));
	    clearMysqRez(&rez);
	}
	return rezult;
    }
    VALUE get_listcomentrticle(VALUE self,VALUE id){
	if(TYPE(id) == T_NIL)
	    id = rb_str_new2("0");
	VALUE rezult = rb_ary_new();
	char *p[4];
	p[0] = pref;
	p[1] = StringValuePtr(id);
	Rezultsql rez;
	exsql(2, "select id, user_id, Date_Format(dt, '%d.%m.%Y | %h:%i') as dt, body, rd from ~comments_article where article_id = '~' and rd = 1", p, &rez);
	if( rez.rows > 0 && rez.colun > 0){
	    rb_encoding * en = rb_utf8_encoding();
	    for(int i = 0; i < rez.rows; i++){
		VALUE temp = rb_hash_new();
		rb_hash_aset(temp, rb_str_new2("id"), rb_enc_str_new_cstr(rez.result[i][0], en)) ;
		rb_hash_aset(temp, rb_str_new2("user_id"), rb_enc_str_new_cstr(rez.result[i][1], en)) ;
		rb_hash_aset(temp, rb_str_new2("dt"), rb_enc_str_new_cstr(rez.result[i][2], en)) ;
		rb_hash_aset(temp, rb_str_new2("body"), rb_enc_str_new_cstr(rez.result[i][3], en)) ;
		rb_hash_aset(temp, rb_str_new2("rd"), rb_enc_str_new_cstr(rez.result[i][4], en)) ;
		rb_ary_push(rezult,temp);
	    }
	    clearMysqRez(&rez);
	}
	return rezult;
    }
#ifdef __cplusplus
}
#endif

#endif /* ARTICLE_H */

