
#ifndef MESSAGES_H
#define MESSAGES_H

#include "vdcgi.h"


#ifdef __cplusplus
extern "C" {
#endif

    VALUE get_unitmes(VALUE self, VALUE id){
	if(TYPE(id) == T_NIL)
	    id = rb_str_new2("0");
	VALUE rezult = rb_hash_new();
	char *p[3];
	p[0] = pref;
	p[1] = pref;
	p[2] = StringValuePtr(id);
	Rezultsql rez;
	rb_encoding * en = rb_utf8_encoding();
	exsql(3, "select id, tems_id, (select title from ~messages_tems where id = m.tems_id) as tems_name, autor_id,(select login from users where id = m.autor_id) as autor_name, recepient_id, (select name from users where id = m.recepient_id) as recepient_name, rd, body, Date_Format(dt,'%d-%m-%Y | %h:%i') as dt from ~messages m where id = '~'", p, &rez);
	 if( rez.rows > 0 && rez.colun > 0){
	    rb_hash_aset(rezult, rb_str_new2("id"), rb_enc_str_new_cstr(rez.result[0][0], en)) ;
	    rb_hash_aset(rezult, rb_str_new2("tems_id"), rb_enc_str_new_cstr(rez.result[0][1], en)) ;
	    rb_hash_aset(rezult, rb_str_new2("tems_name"), rb_enc_str_new_cstr(rez.result[0][2], en)) ;
	    rb_hash_aset(rezult, rb_str_new2("autor_id"), rb_enc_str_new_cstr(rez.result[0][3], en)) ;
	    rb_hash_aset(rezult, rb_str_new2("autor_name"), rb_enc_str_new_cstr(rez.result[0][4], en)) ;
	    rb_hash_aset(rezult, rb_str_new2("recepient_id"), rb_enc_str_new_cstr(rez.result[0][5], en)) ;
	    rb_hash_aset(rezult, rb_str_new2("recepient_name"), rb_enc_str_new_cstr(rez.result[0][6], en)) ;
	    rb_hash_aset(rezult, rb_str_new2("rd"), rb_enc_str_new_cstr(rez.result[0][7], en)) ;
	    rb_hash_aset(rezult, rb_str_new2("body"), rb_enc_str_new_cstr(rez.result[0][8], en)) ;
	    rb_hash_aset(rezult, rb_str_new2("dt"), rb_enc_str_new_cstr(rez.result[0][9], en)) ;
	    clearMysqRez(&rez);    
	 }
	return rezult;
    }
    VALUE get_listmesages(VALUE self, VALUE thems){
	if(TYPE(thems) == T_NIL)
	    thems = rb_str_new2("");
	VALUE rezult = rb_ary_new();
	char *p[3];
	p[0] = pref;
	p[1] = pref;
	p[2] = StringValuePtr(thems);
	Rezultsql rez;
	rb_encoding * en = rb_utf8_encoding();
	exsql(3, "select id, tems_id, (select title from ~messages_tems where id = m.tems_id) as tems_name, autor_id,(select name from users where id = m.autor_id) as autor_name, recepient_id, (select name from users where id = m.recepient_id) as recepient_name, rd, body, Date_Format(dt,'%d-%m-%Y | %h:%i') as dt from ~messages m where tems_id = '~' order by dt", p, &rez);
	 if( rez.rows > 0 && rez.colun > 0){
	     rb_encoding * en = rb_utf8_encoding();
	    for(int i = 0; i < rez.rows; i++){
		VALUE temp = rb_hash_new();
		rb_hash_aset(temp, rb_str_new2("id"), rb_enc_str_new_cstr(rez.result[i][0], en)) ;
		rb_hash_aset(temp, rb_str_new2("tems_id"), rb_enc_str_new_cstr(rez.result[i][1], en)) ;
		rb_hash_aset(temp, rb_str_new2("tems_name"), rb_enc_str_new_cstr(rez.result[i][2], en)) ;
		rb_hash_aset(temp, rb_str_new2("autor_id"), rb_enc_str_new_cstr(rez.result[i][3], en)) ;
		rb_hash_aset(temp, rb_str_new2("autor_name"), rb_enc_str_new_cstr(rez.result[i][4], en)) ;
		rb_hash_aset(temp, rb_str_new2("recepient_id"), rb_enc_str_new_cstr(rez.result[i][5], en)) ;
		rb_hash_aset(temp, rb_str_new2("recepient_name"), rb_enc_str_new_cstr(rez.result[i][6], en)) ;
		rb_hash_aset(temp, rb_str_new2("rd"), rb_enc_str_new_cstr(rez.result[i][7], en)) ;
		rb_hash_aset(temp, rb_str_new2("body"), rb_enc_str_new_cstr(rez.result[i][8], en)) ;
		rb_hash_aset(temp, rb_str_new2("dt"), rb_enc_str_new_cstr(rez.result[i][9], en)) ;
		rb_ary_push(rezult,temp);
	    }
	    clearMysqRez(&rez);    
	 }
	return rezult;
    }
    VALUE get_listnewmesages(VALUE self, VALUE from, VALUE tem){
	if(TYPE(tem) == T_NIL)
	    tem = rb_str_new2("0");
	if(TYPE(from) == T_NIL)
	    from = rb_str_new2("0");
	VALUE rezult = rb_ary_new();
	char *p[5];
	p[0] = pref;
	p[1] = pref;
	p[2] = StringValuePtr(tem);
	p[3] = user_id_s;
	p[4] = StringValuePtr(from);
	Rezultsql rez;
	rb_encoding * en = rb_utf8_encoding();
	exsql(5, "select id, tems_id, (select title from ~messages_tems where id = m.tems_id) as tems_name, autor_id,(select login from users where id = m.autor_id) as autor_name, recepient_id, (select name from users where id = m.recepient_id) as recepient_name, rd, body, Date_Format(dt,'%d-%m-%Y | %h:%i') as dt  from ~messages m where tems_id = '~' and rb = 0 and recepient_id = '~' and autor_id = '~'", p, &rez);
	 if( rez.rows > 0 && rez.colun > 0){
	     rb_encoding * en = rb_utf8_encoding();
	    for(int i = 0; i < rez.rows; i++){
		VALUE temp = rb_hash_new();
		rb_hash_aset(temp, rb_str_new2("id"), rb_enc_str_new_cstr(rez.result[0][0], en)) ;
		rb_hash_aset(temp, rb_str_new2("tems_id"), rb_enc_str_new_cstr(rez.result[0][1], en)) ;
		rb_hash_aset(temp, rb_str_new2("tems_name"), rb_enc_str_new_cstr(rez.result[0][2], en)) ;
		rb_hash_aset(temp, rb_str_new2("autor_id"), rb_enc_str_new_cstr(rez.result[0][3], en)) ;
		rb_hash_aset(temp, rb_str_new2("autor_name"), rb_enc_str_new_cstr(rez.result[0][4], en)) ;
		rb_hash_aset(temp, rb_str_new2("recepient_id"), rb_enc_str_new_cstr(rez.result[0][5], en)) ;
		rb_hash_aset(temp, rb_str_new2("recepient_name"), rb_enc_str_new_cstr(rez.result[0][6], en)) ;
		rb_hash_aset(temp, rb_str_new2("rd"), rb_enc_str_new_cstr(rez.result[0][7], en)) ;
		rb_hash_aset(temp, rb_str_new2("body"), rb_enc_str_new_cstr(rez.result[0][8], en)) ;
		rb_hash_aset(temp, rb_str_new2("dt"), rb_enc_str_new_cstr(rez.result[0][9], en)) ;
		rb_ary_push(rezult,temp);
	    }
	    clearMysqRez(&rez);    
	 }
	return rezult;
    
    }
    VALUE get_listmymesages(VALUE self){
	VALUE rezult = rb_ary_new();
	char *p[4];
	p[0] = pref;
	p[1] = pref;
	p[2] = user_id_s;
	p[3] = user_id_s;
	Rezultsql rez;
	rb_encoding * en = rb_utf8_encoding();
	exsql(4, "select id, tems_id, (select title from ~messages_tems where id = m.tems_id) as tems_name, autor_id,(select login from users where id = m.autor_id) as autor_name, recepient_id, (select name from users where id = m.recepient_id) as recepient_name, rd, body, Date_Format(dt,'%d-%m-%Y | %h:%i') as dt  from ~messages m where autor_id = ~ or recepient_id = ~", p, &rez);
	 if( rez.rows > 0 && rez.colun > 0){
	     rb_encoding * en = rb_utf8_encoding();
	    for(int i = 0; i < rez.rows; i++){
		VALUE temp = rb_hash_new();
		rb_hash_aset(temp, rb_str_new2("id"), rb_enc_str_new_cstr(rez.result[0][0], en)) ;
		rb_hash_aset(temp, rb_str_new2("tems_id"), rb_enc_str_new_cstr(rez.result[0][1], en)) ;
		rb_hash_aset(temp, rb_str_new2("tems_name"), rb_enc_str_new_cstr(rez.result[0][2], en)) ;
		rb_hash_aset(temp, rb_str_new2("autor_id"), rb_enc_str_new_cstr(rez.result[0][3], en)) ;
		rb_hash_aset(temp, rb_str_new2("autor_name"), rb_enc_str_new_cstr(rez.result[0][4], en)) ;
		rb_hash_aset(temp, rb_str_new2("recepient_id"), rb_enc_str_new_cstr(rez.result[0][5], en)) ;
		rb_hash_aset(temp, rb_str_new2("recepient_name"), rb_enc_str_new_cstr(rez.result[0][6], en)) ;
		rb_hash_aset(temp, rb_str_new2("rd"), rb_enc_str_new_cstr(rez.result[0][7], en)) ;
		rb_hash_aset(temp, rb_str_new2("body"), rb_enc_str_new_cstr(rez.result[0][8], en)) ;
		rb_hash_aset(temp, rb_str_new2("dt"), rb_enc_str_new_cstr(rez.result[0][9], en)) ;
		rb_ary_push(rezult,temp);
	    }
	    clearMysqRez(&rez);    
	 }
	return rezult;
    }
    VALUE get_countmesfrom(VALUE self, VALUE tems){
	if(TYPE(tems) == T_NIL)
	    tems = rb_str_new2("0");
	VALUE rezult =  INT2FIX(0);
	Rezultsql rez;
	char *p[3];
	p[0] = pref;
	p[1] = StringValuePtr(tems);
	p[2] = user_id_s;
	exsql(3, "select count(id) as id from ~messages where rd = 0 and tems_id = '~' and autor_id = '~'", p, &rez);
	if( rez.rows > 0 && rez.colun > 0){
	    rezult =  INT2FIX(atoi(rez.result[0][0]));
	    clearMysqRez(&rez);
	}
	return rezult;
    }
    VALUE get_countnewmesto(VALUE self, VALUE tems){
	if(TYPE(tems) == T_NIL)
	    tems = rb_str_new2("0");
	VALUE rezult =  INT2FIX(0);
	Rezultsql rez;
	char *p[3];
	p[0] = pref;
	p[1] = StringValuePtr(tems);
	p[2] = user_id_s;
	exsql(3, "select count(id) as id from ~messages where rd = 0 and tems_id = '~' and recepient_id = '~'", p, &rez);
	if( rez.rows > 0 && rez.colun > 0){
	    rezult =  INT2FIX(atoi(rez.result[0][0]));
	    clearMysqRez(&rez);
	}
	return rezult;
    }
    VALUE get_countmesto(VALUE self, VALUE tems){
	if(TYPE(tems) == T_NIL)
	    tems = rb_str_new2("0");
	VALUE rezult =  INT2FIX(0);
	Rezultsql rez;
	char *p[3];
	p[0] = pref;
	p[1] = StringValuePtr(tems);
	p[2] = user_id_s;
	exsql(3, "select count(id) as id from ~messages where tems_id = '~' and recepient_id = '~'", p, &rez);
	if( rez.rows > 0 && rez.colun > 0){
	    rezult =  INT2FIX(atoi(rez.result[0][0]));
	    clearMysqRez(&rez);
	}
	return rezult;
    }
    VALUE get_countnewmesal(VALUE self, VALUE tems){
	if(TYPE(tems) == T_NIL)
	    tems = rb_str_new2("0");
	VALUE rezult =  INT2FIX(0);
	Rezultsql rez;
	char *p[4];
	p[0] = pref;
	p[1] = user_id_s;
	p[2] = user_id_s;
	p[3] = StringValuePtr(tems);
	exsql(4, "select count(id) as id from ~messages where rd = 0 and (recepient_id = '~' or autor_id = '~' ) and tems_id = '~'", p, &rez);
	if( rez.rows > 0 && rez.colun > 0){
	    rezult =  INT2FIX(atoi(rez.result[0][0]));
	    clearMysqRez(&rez);
	}
	return rezult;
    }
    VALUE get_countmesal(VALUE self, VALUE tems){
	if(TYPE(tems) == T_NIL)
	    tems = rb_str_new2("0");
	VALUE rezult =  INT2FIX(0);
	Rezultsql rez;
	char *p[4];
	p[0] = pref;
	p[1] = user_id_s;
	p[2] = user_id_s;
	p[3] = StringValuePtr(tems);
	exsql(4, "select count(id) as id from ~messages where (recepient_id = '~' or autor_id = '~' ) and tems_id = '~'", p, &rez);
	if( rez.rows > 0 && rez.colun > 0){
	    rezult =  INT2FIX(atoi(rez.result[0][0]));
	    clearMysqRez(&rez);
	}
	return rezult;
    }
    VALUE get_countmesalaltem(VALUE self, VALUE user){
	if(TYPE(user) == T_NIL)
	    user = rb_str_new2("0");
	VALUE rezult =  INT2FIX(0);
	Rezultsql rez;
	char *p[3];
	p[0] = pref;
	p[1] = StringValuePtr(user);
	p[2] = StringValuePtr(user);
	exsql(3, "select count(id) as id from ~messages where (recepient_id = '~' or autor_id = '~' )", p, &rez);
	if( rez.rows > 0 && rez.colun > 0){
	    rezult =  INT2FIX(atoi(rez.result[0][0]));
	    clearMysqRez(&rez);
	}
	return rezult;
    }
   
    VALUE get_listtemuser(VALUE self, VALUE id){
	 if(TYPE(id)== T_NIL)
	    id = rb_str_new2("0");
	VALUE rezult = rb_ary_new();
	char *p[4];
	p[0] = pref;
	p[1] = pref;
	p[2] = StringValuePtr(id);
	p[3] = StringValuePtr(id);
	Rezultsql rez;
	exsql(4, "select id, title from ~messages_tems where id in (select tems_id from  ~messages where autor_id = '~' or recepient_id = '~')", p, &rez);
	 if( rez.rows > 0 && rez.colun > 0){
	     rb_encoding * en = rb_utf8_encoding();
	    for(int i = 0; i < rez.rows; i++){
		VALUE temp = rb_hash_new();
		rb_hash_aset(temp, rb_str_new2("id"), rb_enc_str_new_cstr(rez.result[i][0], en)) ;
		rb_hash_aset(temp, rb_str_new2("title"), rb_enc_str_new_cstr(rez.result[i][1], en)) ;
		rb_ary_push(rezult,temp);
	    }
	    clearMysqRez(&rez);    
	 }
	return rezult;
    }
     VALUE set_addtems(VALUE self, VALUE thems,VALUE usr){
	 if(TYPE(usr) == T_NIL)
	    usr = rb_str_new2("0");
	 if(TYPE(thems) == T_NIL)
	    thems = rb_str_new2("0");
	 char *p[3];
	p[0] = pref;
	p[1] = StringValuePtr(thems);
	p[2] =StringValuePtr(usr);
	execsql(3, "insert ~messages_tems set title = '~', user_id = '~'", p);
	return INT2FIX(atoi(InsId()));
     }

     VALUE set_addmesages(VALUE self, VALUE tems,VALUE from, VALUE to, VALUE body){
	 if(TYPE(tems) == T_NIL)
	    tems = rb_str_new2("0");
	 if(TYPE(from) == T_NIL)
	    from = rb_str_new2("0");
	 if(TYPE(to) == T_NIL)
	    to = rb_str_new2("0");
	 if(TYPE(body) == T_NIL)
	    body = rb_str_new2("");
	 char *p[5];
	p[0] = pref;
	p[1] = StringValuePtr(tems);
	p[2] =StringValuePtr(from);
	p[3] =StringValuePtr(to);
	p[4] =StringValuePtr(body);
	execsql(5, "insert  ~messages set tems_id = '~', autor_id = '~', recepient_id = '~', body = '~'", p);
	return INT2FIX(atoi(InsId()));
     }
      VALUE get_namethem(VALUE self, VALUE id){
	   if(TYPE(id) == T_NIL)
	    id = rb_str_new2("0");
	rb_encoding * en = rb_utf8_encoding();
	VALUE rezult = rb_enc_str_new_cstr(" ",en);
	char *p[2];
	p[0] = pref;
	p[1] = StringValuePtr(id);
	Rezultsql rez;
	exsql(2, "select title from ~messages_tems where id = '~'", p, &rez);
	 if( rez.rows > 0 && rez.colun > 0){
	     rb_encoding * en = rb_utf8_encoding();
	    for(int i = 0; i < rez.rows; i++){
		rezult = rb_enc_str_new_cstr(rez.result[0][0], en) ;
	    }
	    clearMysqRez(&rez);    
	 }
	return rezult;
      }
     VALUE get_listuserthems(VALUE self, VALUE id){
	  if(TYPE(id) == T_NIL)
	    id = rb_str_new2("0");
	VALUE rezult = rb_ary_new();
	char *p[2];
	p[0] = pref;
	p[1] = StringValuePtr(id);
	Rezultsql rez;
	exsql(2, "select id, title from ~messages_tems where user_id = '~'", p, &rez);
	 if( rez.rows > 0 && rez.colun > 0){
	     rb_encoding * en = rb_utf8_encoding();
	    for(int i = 0; i < rez.rows; i++){
		VALUE temp = rb_hash_new();
		rb_hash_aset(temp, rb_str_new2("id"), rb_enc_str_new_cstr(rez.result[0][0], en)) ;
		rb_hash_aset(temp, rb_str_new2("title"), rb_enc_str_new_cstr(rez.result[0][1], en)) ;
		rb_ary_push(rezult,temp);
	    }
	    clearMysqRez(&rez);    
	 }
	return rezult;
    }
      VALUE get_getrecep(VALUE self, VALUE temps, VALUE ovner){
	if(TYPE(temps) == T_NIL)
	    temps = rb_str_new2("0");
	if(TYPE(ovner) == T_NIL)
	    ovner = rb_str_new2("0");
	VALUE rezult =  INT2FIX(0);
	int ovn = atoi(StringValuePtr(ovner));
	char *p[2];
	p[0] = pref;
	p[1] = StringValuePtr(temps);
	Rezultsql rez;
	rezult =  INT2FIX(atoi(rez.result[0][0]));
	exsql(2, "select autor_id, recepient_id from ~messages where tems_id = '~'", p, &rez);
	 if( rez.rows > 0 && rez.colun > 0){
	     if (ovn == atoi(rez.result[0][0])){
		rezult = INT2FIX(atoi(rez.result[0][1])); 
	     }else
		 rezult = INT2FIX(atoi(rez.result[0][0]));
		 
	    clearMysqRez(&rez);    
	 }
	return rezult;
      }
      VALUE set_rd(VALUE self, VALUE id,VALUE user){
	if(TYPE(id) == T_NIL)
	    id = rb_str_new2("0");
	if(TYPE(user) == T_NIL)
	    user = rb_str_new2("0");
	 char *p[3];
	p[0] = pref;
	p[1] = StringValuePtr(id);
	p[2] =StringValuePtr(user);
	execsql(3, "update  ~messages set rd = 1 where tems_id = '~' and recepient_id = '~'", p);
	return self;
     }
      
#ifdef __cplusplus
}
#endif

#endif /* MESSAGES_H */

