
#ifndef USER_H
#define USER_H

#ifdef __cplusplus
extern "C" {
#endif
#include "vdcgi.h"
    VALUE get_username(VALUE self, VALUE id){
	if(TYPE(id) == T_NIL)
	    id = rb_str_new2("0");
	char *id_c = StringValuePtr(id);
	VALUE rezult = rb_str_new2("");
	Rezultsql rez;
	char *p[1];
	p[0] = id_c;
	if(strlen(id_c) < 11){
	    exsql(1, "SELECT login, name FROM users WHERE id = '~'", p, &rez);
	}else
	    exsql(1, "SELECT 'Гость' as login, name FROM temp_user WHERE checksum = '~'", p, &rez);
	if( rez.rows > 0 && rez.colun > 0){
	    if(strlen(rez.result[0][1]) > 0 && strcmp(rez.result[0][1],"null") != 0){
		if(strlen(rez.result[0][1]) > 0 && strncmp(rez.result[0][1],"null",4) != 0){
		    rezult = rb_enc_str_new_cstr(rez.result[0][1], rb_utf8_encoding());
		} else
		    rezult = rb_enc_str_new_cstr(rez.result[0][0], rb_utf8_encoding());
		    
	    }else
		rezult = rb_enc_str_new_cstr("Гость", rb_utf8_encoding());
	    clearMysqRez(&rez);
	}else
            rezult = rb_enc_str_new_cstr("Гость", rb_utf8_encoding());
	return rezult;
    }
    VALUE get_userparam(VALUE self, VALUE id){
	if(TYPE(id) == T_NIL)
	    id = rb_str_new2("0");
	char *id_c = StringValuePtr(id);
	VALUE rezult = rb_hash_new();
	Rezultsql rez;
	rb_encoding * en = rb_utf8_encoding();
	char *p[1];
	p[0] = id_c;
	if(strlen(id_c) < 11){
	    exsql(1, "SELECT id, old_user_id,  region_id, login, level, mail, Date_Format(activity,'%d.%m.%Y') as activity, checksum, count_of_err, antibot, antispam, name, gender, phone, icq, www, skype, city_id, street, hous,  building, apartament,  about_me,  confirm, user_type, bank_account,  web_money, yandex_money, oldname,  midlename, spam, parent_id, country_id,  birthday,  adress,  date_reg  FROM users WHERE id = '~'", p, &rez);
	}else
	    exsql(1, "SELECT id, old_user_id,  region_id, login, level, mail, Date_Format(activity,'%d.%m.%Y') as activity, checksum, count_of_err, antibot, antispam, name, gender, phone, icq, www, skype, city_id, street, hous,  building, apartament,  about_me,  confirm, user_type, bank_account,  web_money, yandex_money, oldname,  midlename, spam, parent_id, country_id,  birthday,  adress,  date_reg  FROM users WHERE checksum = '~'", p, &rez);
	if( rez.rows > 0 && rez.colun > 0){ 
	    rb_hash_aset(rezult, rb_str_new2("id"), rb_enc_str_new_cstr(rez.result[0][0], en)) ;
	    rb_hash_aset(rezult, rb_str_new2("old_user_id"), rb_enc_str_new_cstr(rez.result[0][1], en)) ;
	    rb_hash_aset(rezult, rb_str_new2("region_id"), rb_enc_str_new_cstr(rez.result[0][2], en)) ;
	    rb_hash_aset(rezult, rb_str_new2("login"), rb_enc_str_new_cstr(rez.result[0][3], en)) ;
	    rb_hash_aset(rezult, rb_str_new2("level"), rb_enc_str_new_cstr(rez.result[0][4], en)) ;
	    rb_hash_aset(rezult, rb_str_new2("mail"), rb_enc_str_new_cstr(rez.result[0][5], en)) ;
	    rb_hash_aset(rezult, rb_str_new2("activity"), rb_enc_str_new_cstr(rez.result[0][6], en)) ;
	    rb_hash_aset(rezult, rb_str_new2("checksum"), rb_enc_str_new_cstr(rez.result[0][7], en)) ;
	    rb_hash_aset(rezult, rb_str_new2("count_of_err"), rb_enc_str_new_cstr(rez.result[0][8], en)) ;
	    rb_hash_aset(rezult, rb_str_new2("antibot"), rb_enc_str_new_cstr(rez.result[0][9], en)) ;
	    rb_hash_aset(rezult, rb_str_new2("antispam"), rb_enc_str_new_cstr(rez.result[0][10], en)) ;
	    rb_hash_aset(rezult, rb_str_new2("name"), rb_enc_str_new_cstr(rez.result[0][11], en)) ;
	    rb_hash_aset(rezult, rb_str_new2("gender"), rb_enc_str_new_cstr(rez.result[0][12], en)) ;
	    rb_hash_aset(rezult, rb_str_new2("phone"), rb_enc_str_new_cstr(rez.result[0][12], en)) ;
	    rb_hash_aset(rezult, rb_str_new2("icq"), rb_enc_str_new_cstr(rez.result[0][14], en)) ;
	    rb_hash_aset(rezult, rb_str_new2("www"), rb_enc_str_new_cstr(rez.result[0][15], en)) ;
	    rb_hash_aset(rezult, rb_str_new2("skype"), rb_enc_str_new_cstr(rez.result[0][16], en)) ;
	    rb_hash_aset(rezult, rb_str_new2("city_id"), rb_enc_str_new_cstr(rez.result[0][17], en)) ;
	    rb_hash_aset(rezult, rb_str_new2("street"), rb_enc_str_new_cstr(rez.result[0][18], en)) ;
	    rb_hash_aset(rezult, rb_str_new2("hous"), rb_enc_str_new_cstr(rez.result[0][19], en)) ;
	    rb_hash_aset(rezult, rb_str_new2("building"), rb_enc_str_new_cstr(rez.result[0][20], en)) ;
	    rb_hash_aset(rezult, rb_str_new2("apartament"), rb_enc_str_new_cstr(rez.result[0][21], en)) ;
	    rb_hash_aset(rezult, rb_str_new2("about_me"), rb_enc_str_new_cstr(rez.result[0][22], en)) ;
	    rb_hash_aset(rezult, rb_str_new2("confirm"), rb_enc_str_new_cstr(rez.result[0][23], en)) ;
	    rb_hash_aset(rezult, rb_str_new2("user_type"), rb_enc_str_new_cstr(rez.result[0][24], en)) ;
	    rb_hash_aset(rezult, rb_str_new2("bank_account"), rb_enc_str_new_cstr(rez.result[0][24], en)) ;
	    rb_hash_aset(rezult, rb_str_new2("web_money"), rb_enc_str_new_cstr(rez.result[0][26], en)) ;
	    rb_hash_aset(rezult, rb_str_new2("yandex_money"), rb_enc_str_new_cstr(rez.result[0][27], en)) ;
	    rb_hash_aset(rezult, rb_str_new2("oldname"), rb_enc_str_new_cstr(rez.result[0][28], en)) ;
	    rb_hash_aset(rezult, rb_str_new2("midlename"), rb_enc_str_new_cstr(rez.result[0][29], en)) ;
	    rb_hash_aset(rezult, rb_str_new2("spam"), rb_enc_str_new_cstr(rez.result[0][30], en)) ;
	    rb_hash_aset(rezult, rb_str_new2("parent_id"), rb_enc_str_new_cstr(rez.result[0][31], en)) ;
	    rb_hash_aset(rezult, rb_str_new2("country_id"), rb_enc_str_new_cstr(rez.result[0][32], en)) ;
	    rb_hash_aset(rezult, rb_str_new2("birthday"), rb_enc_str_new_cstr(rez.result[0][33], en)) ;
	    rb_hash_aset(rezult, rb_str_new2("adress"), rb_enc_str_new_cstr(rez.result[0][34], en)) ;
	    rb_hash_aset(rezult, rb_str_new2("date_reg"), rb_enc_str_new_cstr(rez.result[0][35], en)) ;
	    clearMysqRez(&rez);
	}
	return rezult;
    }


#ifdef __cplusplus
}
#endif

#endif /* USER_H */

