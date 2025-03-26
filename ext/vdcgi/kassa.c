#ifndef KASSA_H
#define KASSA_H

#include "vdcgi.h"


#ifdef __cplusplus
extern "C" {
#endif
#include "vdcgi.h"
    VALUE get_unitbascet(VALUE self, VALUE usr){
	if(TYPE(usr) == T_NIL)
	    usr = rb_str_new2("0");
	VALUE rezult = INT2FIX(0);
	Rezultsql rez;
	char *p[1];
	p[0] = StringValuePtr(usr);
	exsql(1, "select sum(coun) as coun from order_unit where user_id = '~'  and status = 0 ", p, &rez);
	 if( rez.rows > 0 && rez.colun > 0){
	    rezult = INT2FIX(atoi(rez.result[0][0]));
	    clearMysqRez(&rez);    
	 }
	return rezult;
    }
    VALUE get_listpayemtsystem(VALUE self){
	VALUE rezult = rb_ary_new();
	Rezultsql rez;
	char *p[1];
	exsql(0, "select id, name from payment_system_item order by ord", p, &rez);
	if( rez.rows > 0 && rez.colun > 0){
	    rb_encoding * en = rb_utf8_encoding();
	    for(int i = 0; i < rez.rows; i++){
		VALUE temp = rb_hash_new();
		rb_hash_aset(temp, rb_str_new2("id"), rb_enc_str_new_cstr(rez.result[i][0], en)) ;
		rb_hash_aset(temp, rb_str_new2("name"), rb_enc_str_new_cstr(rez.result[i][1], en)) ;
		rb_ary_push(rezult,temp);
	    }
	    clearMysqRez(&rez);
	}
	return rezult;
    }
    VALUE get_listorderuser(VALUE self, VALUE usr,VALUE sort){
	if(TYPE(usr) == T_NIL)
	    usr = rb_str_new2("0");
	if(TYPE(sort) == T_NIL)
	    sort = rb_str_new2("0");
	VALUE rezult = rb_ary_new();
	int srt = atoi(StringValuePtr(sort));
	char ord[124];
	
	bzero(ord,124);
	if(srt != 0)
	    sprintf(ord," and status = '%i' ",srt);
	char *p[2];
	p[0] = StringValuePtr(usr);
	p[1] = ord;
	Rezultsql rez;
	exsql(2, "select id, status, sum, data_order, delive, plat_id, shop_id, (select shop_name from shops where id = k.shop_id) as shop_name from orders k where user_id = '~' ~ order by k.data_order desc", p, &rez);
	if( rez.rows > 0 && rez.colun > 0){
	    rb_encoding * en = rb_utf8_encoding();
	    for(int i = 0; i < rez.rows; i++){
		VALUE temp = rb_hash_new();
		rb_hash_aset(temp, rb_str_new2("id"), rb_enc_str_new_cstr(rez.result[i][0], en)) ;
		rb_hash_aset(temp, rb_str_new2("status"), rb_enc_str_new_cstr(rez.result[i][1], en)) ;
		rb_hash_aset(temp, rb_str_new2("summ"), rb_enc_str_new_cstr(rez.result[i][1], en)) ;
		rb_hash_aset(temp, rb_str_new2("data_order"), rb_enc_str_new_cstr(rez.result[i][1], en)) ;
		rb_hash_aset(temp, rb_str_new2("delive"), rb_enc_str_new_cstr(rez.result[i][1], en)) ;
		rb_hash_aset(temp, rb_str_new2("plat_id"), rb_enc_str_new_cstr(rez.result[i][1], en)) ;
		rb_hash_aset(temp, rb_str_new2("shops"), rb_enc_str_new_cstr(rez.result[i][1], en)) ;
		rb_hash_aset(temp, rb_str_new2("shop_name"), rb_enc_str_new_cstr(rez.result[i][1], en)) ;
		
		Rezultsql rezz;
		char *pp[1];
		pp[0] = rez.result[i][0];
		exsql(1, "select product_id, size, shop_id, deliver, p.name as name, p.category_id as category_id from order_unit o left join products p on p.id = o.product_id  where order_id = '~' ", pp, &rezz);
		if( rezz.rows > 0 && rezz.colun > 0){
		    for(int b = 0; b < rezz.rows; b++){
			VALUE ar_t = rb_hash_new();
			rb_hash_aset(ar_t,rb_str_new2("product_id"),rb_enc_str_new_cstr(rezz.result[b][0], en));
			rb_hash_aset(ar_t,rb_str_new2("size"),rb_enc_str_new_cstr(rezz.result[b][1], en));
			rb_hash_aset(ar_t,rb_str_new2("shop_id"),rb_enc_str_new_cstr(rezz.result[b][2], en));
			rb_hash_aset(ar_t,rb_str_new2("deliver"),rb_enc_str_new_cstr(rezz.result[b][3], en));
			rb_hash_aset(ar_t,rb_str_new2("name"),rb_enc_str_new_cstr(rezz.result[b][4], en));
			rb_hash_aset(ar_t,rb_str_new2("category_id"),rb_enc_str_new_cstr(rezz.result[b][5], en));
			Rezultsql rezzz;
			char *ppp[1];
			ppp[0] = rezz.result[b][1];
			switch(atoi(rezz.result[b][8])){
			    case 1:
				exsql(1, "select sale from size where id = '~' ", ppp, &rezzz);
				break;
			    case 2:
				exsql(1, "select sale_two from size where id = '~' ", ppp, &rezzz);
				break;
			    case 3:
				exsql(1, "select sale_three from size where id = '~' ", ppp, &rezzz);
				break;
			    case 0:
				exsql(1, "select sale from size where id = '~' ", ppp, &rezzz);
				break;
			    default:
				exsql(1, "select sale_opt from size where id = '~' ", ppp, &rezzz);
				break;
			}
			if( rezzz.rows > 0 && rezzz.colun > 0){
			    rb_hash_aset(ar_t,rb_str_new2("sale"),rb_enc_str_new_cstr(rezzz.result[0][0], en));
			    clearMysqRez(&rezzz);
			}
			rb_hash_aset(temp, rb_str_new2("list_prod"), ar_t) ;
		    }
		    
		    clearMysqRez(&rezz);
		}
		rb_ary_push(rezult,temp);
	    }
	    clearMysqRez(&rez);
	}
	return self;
    }
    VALUE get_balansuser(VALUE self, VALUE usr){
	if(TYPE(usr) == T_NIL)
	    usr = rb_str_new2("0");
	VALUE rezult = rb_str_new2("0");
	Rezultsql rez;
	char pr[50];
	bzero(pr,50);
	strcpy(pr,pref);
	char *p[1];
	p[0] = StringValuePtr(usr);
	exsql(1, "select sum from kassa_user where user_id = '~' ", p, &rez);
	 if( rez.rows > 0 && rez.colun > 0){
		rezult = rb_str_new2(rez.result[0][0]);
		
	    clearMysqRez(&rez);    
	 }
	return rezult;
    }
    
     VALUE get_listdepositout(VALUE self){
	VALUE rezult = rb_ary_new();
	Rezultsql rez;
	char *p[1];
	exsql(0, "select id, summ, user_id, way, (select concat(name,' ',midlename, ' ', oldname) from users where id = o.user_id) as user_name, Date_Format(data_order,'%d.%m.%Y | %h:%i') as data_order, Date_Format(data_exec,'%d.%m.%Y | %h:%i') as data_exec, plat_id, status from kassa_order o where type = 1 and status = 3 ", p, &rez);
//	status = 3 успешо завершен
	if( rez.rows > 0 && rez.colun > 0){
	    rb_encoding * en = rb_utf8_encoding();
	    for(int i = 0; i < rez.rows; i++){
		VALUE temp = rb_hash_new();
		rb_hash_aset(temp, rb_str_new2("id"), rb_enc_str_new_cstr(rez.result[i][0], en)) ;
		rb_hash_aset(temp, rb_str_new2("summ"), rb_enc_str_new_cstr(rez.result[i][1], en)) ;
		rb_hash_aset(temp, rb_str_new2("user_id"), rb_enc_str_new_cstr(rez.result[i][2], en)) ;
		rb_hash_aset(temp, rb_str_new2("way"), rb_enc_str_new_cstr(rez.result[i][3], en)) ;
		rb_hash_aset(temp, rb_str_new2("user_name"), rb_enc_str_new_cstr(rez.result[i][4], en)) ;
		rb_hash_aset(temp, rb_str_new2("data_order"), rb_enc_str_new_cstr(rez.result[i][5], en)) ;
		rb_hash_aset(temp, rb_str_new2("data_exec"), rb_enc_str_new_cstr(rez.result[i][6], en)) ;
		rb_hash_aset(temp, rb_str_new2("plat_id"), rb_enc_str_new_cstr(rez.result[i][7], en)) ;
		rb_hash_aset(temp, rb_str_new2("status"), rb_enc_str_new_cstr(rez.result[i][8], en)) ;
		rb_ary_push(rezult,temp);
	    }
	    clearMysqRez(&rez);
	}
	return rezult;
    }
    
    
    VALUE get_listorderkassauser(VALUE self){
	VALUE rezult = rb_ary_new();
	Rezultsql rez;
	char *p[1];
	exsql(0, "select id, summ, user_id, way, (select concat(name,' ',midlename, ' ', oldname) from users where id = o.user_id) as user_name, Date_Format(data_order,'%d.%m.%Y | %h:%i') as data_order, Date_Format(data_exec,'%d.%m.%Y | %h:%i') as data_exec, plat_id, status from kassa_order o  ", p, &rez);
	if( rez.rows > 0 && rez.colun > 0){
	    rb_encoding * en = rb_utf8_encoding();
	    for(int i = 0; i < rez.rows; i++){
		VALUE temp = rb_hash_new();
		rb_hash_aset(temp, rb_str_new2("id"), rb_enc_str_new_cstr(rez.result[i][0], en)) ;
		rb_hash_aset(temp, rb_str_new2("summ"), rb_enc_str_new_cstr(rez.result[i][1], en)) ;
		rb_hash_aset(temp, rb_str_new2("user_id"), rb_enc_str_new_cstr(rez.result[i][2], en)) ;
		rb_hash_aset(temp, rb_str_new2("way"), rb_enc_str_new_cstr(rez.result[i][3], en)) ;
		rb_hash_aset(temp, rb_str_new2("user_name"), rb_enc_str_new_cstr(rez.result[i][4], en)) ;
		rb_hash_aset(temp, rb_str_new2("data_order"), rb_enc_str_new_cstr(rez.result[i][5], en)) ;
		rb_hash_aset(temp, rb_str_new2("data_exec"), rb_enc_str_new_cstr(rez.result[i][6], en)) ;
		rb_hash_aset(temp, rb_str_new2("plat_id"), rb_enc_str_new_cstr(rez.result[i][7], en)) ;
		rb_hash_aset(temp, rb_str_new2("status"), rb_enc_str_new_cstr(rez.result[i][8], en)) ;
		rb_ary_push(rezult,temp);
	    }
	    clearMysqRez(&rez);
	}
	return rezult;
    }
    VALUE get_conunt_order(VALUE self, VALUE type){
	if(TYPE(type) == T_NIL)
	    type = rb_str_new2("0");
	VALUE rezult = INT2FIX(0);
	Rezultsql rez;
	char *p[1];
	p[0] = StringValuePtr(type);
	exsql(1, "select count(id) as cn from kassa_order where way = '~' ", p, &rez);
	 if( rez.rows > 0 && rez.colun > 0){
	    rezult = INT2FIX(atoi(rez.result[0][0]));
	    clearMysqRez(&rez);    
	 }
	return rezult;
    }
    VALUE get_outsumadmin(VALUE self){
	VALUE rezult = rb_str_new2("0");
	Rezultsql rez;
	char pr[50];
	bzero(pr,50);
	strcpy(pr,pref);
	char *p[1];
	exsql(0, "select sum(sum) as sum from kassa_order where way = 1 and user_id = 1 ", p, &rez);
	 if( rez.rows > 0 && rez.colun > 0){
	    rezult = rb_str_new2(rez.result[0][0]);
	    clearMysqRez(&rez);    
	 }
	return rezult;
    }
    VALUE  get_orderinerall(VALUE self){
	VALUE rezult = rb_str_new2("0");
	Rezultsql rez;
	char pr[50];
	bzero(pr,50);
	strcpy(pr,pref);
	char *p[1];
	exsql(0, "select sum(sum) as sum from kassa_order where way = 0 ", p, &rez);
	 if( rez.rows > 0 && rez.colun > 0){
	    rezult = rb_str_new2(rez.result[0][0]);
	    clearMysqRez(&rez);    
	 }
	return rezult;
    }
   VALUE  get_orderoutall(VALUE self){
	VALUE rezult = rb_str_new2("0");
	Rezultsql rez;
	char pr[50];
	bzero(pr,50);
	strcpy(pr,pref);
	char *p[1];
	exsql(0, "select sum(sum) as sum from kassa_order where way = 1 ", p, &rez);
	 if( rez.rows > 0 && rez.colun > 0){
	    rezult = rb_str_new2(rez.result[0][0]);
	    clearMysqRez(&rez);    
	 }
	return rezult;
    }
    
    
#ifdef __cplusplus
}
#endif

#endif /* KASSA_H */

