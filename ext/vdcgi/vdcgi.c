#include "vdcgi.h"


VALUE user_param;
int level = 0;
int user_id = 0;
char level_s[10];
char user_id_s[10];
char pref[50];
int content_lech = 0;
int PAPAM_BUF  = 1024;
char coock[1024];
Config config;
Param param_cgi[1024];
Mysq mysql[100];
MYSQL *last_ql;
int loging;
VALUE param;
VALUE user_level_r;
VALUE user_id_r;
int socket_ven;
VALUE vdcgi = Qnil;
VALUE clientven = Qnil;
VALUE mainapp = Qnil;
VALUE user = Qnil;
VALUE article = Qnil;
VALUE kassa = Qnil;
VALUE bitcoin = Qnil;
VALUE staistic = Qnil;
VALUE chat = Qnil;
VALUE video = Qnil;
VALUE Robo_kassa = Qnil;
VALUE product = Qnil;
VALUE inter_kassa = Qnil;
VALUE admin = Qnil;
VALUE vdnet = Qnil;
VALUE messages = Qnil;
VALUE img = Qnil;
UserParam u_p;
int GetConfigI(char *patch, Config * config){
	setlocale(LC_ALL, "");
    FILE *meminfo = fopen(patch, "r");
	 char line[256];
	 config->devel = 0;
	 config->access = 10;
	 config->block = false;
     config->threed = 1;
	    while(fgets(line, sizeof(line), meminfo))
	    {
		if(strstr(line,"=user")){
			if(strlen(config->user) < 100)
				strcpy(config->user,strtok(line, "="));
		} else if(strstr(line,"=passwd")){
			if(strlen(config->passwd) < 100)
				strcpy(config->passwd,strtok(line, "="));
		} else if (strstr(line,"=port")){
			config->port = atoi(strtok(line, "="));
		} else if (strstr(line,"=host")){
			if(strlen(config->host) < 100)
				strcpy(config->host,strtok(line, "="));
		} else if (strstr(line,"=db")){
			if(strlen(config->baza) < 100)
				strcpy(config->baza,strtok(line, "="));
		} else if (strstr(line,"=ip")){
			if(strlen(config->ip) < 100)
				strcpy(config->ip,strtok(line, "="));
		} else if (strstr(line,"=domain")){
			if(strlen(config->domain) < 100)
				strcpy(config->domain,strtok(line, "="));
		}  else if (strstr(line,"=url")){
			if(strlen(config->url) < 100)
				strcpy(config->url,strtok(line, "="));
		}  else if (strstr(line,"=limit")){
			if(strlen(config->limit) < 10)
				strcpy(config->limit,strtok(line, "="));
		}  else if (strstr(line,"=devel")){
			if( strlen(strtok(line, "=")) > 0){
				config->devel = atoi(strtok(line, "="));
			}
		}  else if (strstr(line,"=access")){
			if( strlen(strtok(line, "=")) > 0){
				config->access = atoi(strtok(line, "="));
			}
        }  else if (strstr(line,"=threed")){
            if( strlen(strtok(line, "=")) > 0){
                int tr = atoi(strtok(line, "="));
                if(tr <=100){
                    config->threed = tr;
                }

            }

        } else if (strstr(line,"=block")){
            if( strlen(strtok(line, "=")) > 0){
                config->block = true;
            }

        }else if (strstr(line,"=passtrack")){
            if(strlen(config->passtrack) < 100)
                strcpy(config->passtrack,strtok(line, "="));
        }else if (strstr(line,"=logintrack")){
            if(strlen(config->logintrack) < 100)
                strcpy(config->logintrack,strtok(line, "="));
        }else if (strstr(line,"=idtrack")){
            if(strlen(config->idtrack) < 11)
                strcpy(config->idtrack,strtok(line, "="));
        }else if (strstr(line,"=utrack")){
            if(strlen(config->utrack) < 100)
                strcpy(config->utrack,strtok(line, "="));
        }


        }
	    fclose(meminfo);
	    return 0;
}
VALUE get_baza(VALUE self, VALUE name){
    initparam(param_cgi);
	Check_Type(name, T_STRING);
	GetConfigI(StringValuePtr(name), &config);
	int ms_c = 0;
//    fprintf(stderr,"start baza %s %s %s %s  %i\n",config.host,config.user,config.passwd,config.baza,config.port);
	for(ms_c = 0; ms_c < config.threed; ms_c++) {
//        fprintf(stderr,"start on %s %s %s %s  %i\n",config.host,config.user,config.passwd,config.baza,config.port);
         if (mysql_init(&mysql[ms_c].mysql) != NULL) {
            if (mysql_real_connect(&mysql[ms_c].mysql, config.host, config.user, config.passwd, config.baza, config.port, NULL,
                                   0) != NULL) {
                mysql_query(&mysql[ms_c].mysql, "set character_set_connection = utf8");
                mysql_query(&mysql[ms_c].mysql, "set character_set_client = utf8");
                mysql_query(&mysql[ms_c].mysql, "set character_set_results = utf8");

            } else {
//                fprintf(stderr,"mysql no start\n");
                mysql_errno(&mysql[ms_c].mysql);
                printf("no baza conect");
                return Data_Wrap_Struct(self, 0, clearvd, &param_cgi);
                // exit(1);
            }
        } else {
            mysql_errno(&mysql[ms_c].mysql);
            printf("no baza conect");
            return Data_Wrap_Struct(self, 0, clearvd, &param_cgi);
            // exit(2);
        }
    }
	return Data_Wrap_Struct(self, 0, clearvd, &param_cgi);
}

int baza_reconect(MYSQL *mysql){
			if(mysql_ping(mysql) != 0){
				if(mysql_ping(mysql) != 0){
                    mysql_close(mysql);
//                    exit(1);
                    if(mysql_init(mysql ) != NULL){
                     if(mysql_real_connect(mysql,config.host,config.user,config.passwd,config.baza,config.port,NULL,0) != NULL){
                            mysql_query(mysql, "set character_set_connection = utf8");
                            mysql_query(mysql, "set character_set_client = utf8");
                            mysql_query(mysql, "set character_set_results = utf8");
                            return 0;
                        } else{
                             mysql_errno(mysql);
                             exit(1);
                        }
                        }else{
                         mysql_errno(mysql);
                         exit(2);
                         }
				}else{
                    return 0;
				}

			}else{
                return 0;
			}
	}
int clearvd(Param *param_cgi){
    int ms_c = 0;
    for(ms_c = 0; ms_c < config.threed; ms_c++) {
        mysql_close(&mysql[ms_c].mysql);
    }
  clearparams(param_cgi);
  return 0;
}


VALUE get_clientven(VALUE self, VALUE vd, VALUE ip, VALUE port){
	rb_iv_set(self,"@conect", vd);
    rb_iv_set(self,"@ip", ip);
    rb_iv_set(self,"@port", ip);
	return self;
}

VALUE get_mainapp(VALUE self, VALUE vd){
	rb_iv_set(self,"@conect", vd);
	return self;
}
VALUE get_user(VALUE self, VALUE vd){
	rb_iv_set(self,"@conect", vd);
	return self;
}
VALUE get_article(VALUE self, VALUE vd){
	rb_iv_set(self,"@conect", vd);
	return self;
}
VALUE get_kassa(VALUE self, VALUE vd){
	rb_iv_set(self,"@conect", vd);
	return self;	
}
VALUE get_bitcoin(VALUE self, VALUE vd){
	rb_iv_set(self,"@conect", vd);
	return self;
}
VALUE get_staistic(VALUE self, VALUE vd){
	rb_iv_set(self,"@conect", vd);
	return self;
}
VALUE get_video(VALUE self, VALUE vd){
	rb_iv_set(self,"@conect", vd);
	return self;
}
VALUE get_Robo_kassa(VALUE self, VALUE vd){
	rb_iv_set(self,"@conect", vd);
	return self;
}
VALUE get_product(VALUE self, VALUE vd){
	rb_iv_set(self,"@conect", vd);
	return self;
}
VALUE get_net(VALUE self, VALUE vd){
	rb_iv_set(self,"@conect", vd);
	return self;
}
VALUE get_inter_kassa(VALUE self, VALUE vd){
	rb_iv_set(self,"@conect", vd);
	return self;
}
VALUE get_admin(VALUE self, VALUE vd){
	rb_iv_set(self,"@conect", vd);
	return self;
}
VALUE get_messages(VALUE self, VALUE vd){
	rb_iv_set(self,"@conect", vd);
	return self;
}
VALUE get_img(VALUE self, VALUE vd){
	// rb_iv_set(self,"@conect", vd);
	return self;
}

VALUE rb_mVdcgi;

RUBY_FUNC_EXPORTED void
Init_vdcgi(void)
{
  rb_mVdcgi = rb_define_module("Vdcgi");
 
  
// }


// void Init_vdcgi() {
  VALUE vdcgi = rb_define_class_under( rb_mVdcgi, "Vdcgi", rb_cObject);
  VALUE mainapp = rb_define_class_under( rb_mVdcgi, "VdMainapp", rb_cObject);
  VALUE user = rb_define_class_under( rb_mVdcgi, "VdUser", rb_cObject);
  VALUE article = rb_define_class_under( rb_mVdcgi, "VdArticle", rb_cObject);
  VALUE kassa = rb_define_class_under( rb_mVdcgi, "VdKassa", rb_cObject);
  VALUE bitcoin = rb_define_class_under( rb_mVdcgi, "VdBitcoin", rb_cObject);
  VALUE staistic = rb_define_class_under( rb_mVdcgi, "VdStatistic", rb_cObject);
  VALUE video = rb_define_class_under( rb_mVdcgi, "VdVideo", rb_cObject);
  VALUE Robo_kassa = rb_define_class_under( rb_mVdcgi, "VdRobo_kassa", rb_cObject);
  VALUE product = rb_define_class_under( rb_mVdcgi, "VdProduct", rb_cObject);
  VALUE vdnet = rb_define_class_under( rb_mVdcgi, "VdNet", rb_cObject);
  VALUE inter_kassa = rb_define_class_under( rb_mVdcgi, "VdInter_kassa", rb_cObject);
  VALUE admin = rb_define_class_under( rb_mVdcgi, "VdAdmin", rb_cObject);
  VALUE messages = rb_define_class_under( rb_mVdcgi, "VdMessages", rb_cObject);
  VALUE clientven = rb_define_class_under( rb_mVdcgi, "Clientven", rb_cObject);
  VALUE img = rb_define_class_under( rb_mVdcgi, "VdImg", rb_cObject);

  
  rb_define_method(mainapp, "initialize", get_mainapp, 1);
  rb_define_singleton_method(vdcgi, "new", get_baza, 1);
//   rb_define_method(mainapp, "initialize", get_mainapp, 1);
  rb_define_method(clientven, "initialize", get_clientven, 3);
  rb_define_method(user, "initialize", get_user, 1);
  rb_define_method(article, "initialize", get_article, 1);
  rb_define_method(kassa, "initialize", get_kassa, 1);
  rb_define_method(bitcoin, "initialize", get_bitcoin, 1);
  rb_define_method(staistic, "initialize", get_staistic, 1);
  rb_define_method(video, "initialize", get_video, 1);
  rb_define_method(Robo_kassa, "initialize", get_Robo_kassa, 1);
  rb_define_method(vdnet, "initialize", get_net, 1);
  rb_define_method(inter_kassa, "initialize", get_inter_kassa, 1);
  rb_define_method(admin, "initialize", get_admin, 1);
  rb_define_method(messages, "initialize", get_messages, 1);
  rb_define_method(img, "initialize", get_img, 1);
  rb_define_method(product, "initialize", get_product, 1);



  rb_define_method(clientven, "initialize", get_conect, 5);
  rb_define_method(clientven, "check_con", check_con, 0);
  rb_define_method(clientven, "startMessage", startMessage, 1);
  rb_define_method(clientven, "remoteCmd", remoteCmd, 2);
  rb_define_method(clientven, "answerCmd", answerComand, 1);
  rb_define_method(clientven, "closeSockV", closeSockV, 0);
  rb_define_method(clientven, "PingPong", PingPong, 0);
  
  
     
  
  
  
  
//   rb_define_method(messages, "getunitmes", get_unitmes, 1);
  
  rb_define_method(messages, "getunitmes", get_unitmes, 1);
  rb_define_method(messages, "listmesages", get_listmesages, 1);
  rb_define_method(messages, "listnewmesages", get_listnewmesages, 2);
  rb_define_method(messages, "listmymesages", get_listmymesages, 0);
  rb_define_method(messages, "countmesfrom", get_countmesfrom, 1);
  rb_define_method(messages, "countnewmesto", get_countnewmesto, 1);
  rb_define_method(messages, "countmesto", get_countmesto, 1);
  rb_define_method(messages, "countnewmesal", get_countnewmesal, 1);
  rb_define_method(messages, "countmesal", get_countmesal, 1);
  rb_define_method(messages, "countmesalaltem", get_countmesalaltem, 1);

  rb_define_method(messages, "listtemuser", get_listtemuser, 1);
  rb_define_method(messages, "addtems", set_addtems, 2);
  rb_define_method(messages, "addmesages", set_addmesages, 4);
  rb_define_method(messages, "getnamethem", get_namethem, 1);
  rb_define_method(messages, "listuserthems", get_listuserthems, 1);
  rb_define_method(messages, "getrecep", get_getrecep, 2);
  rb_define_method(messages, "set_rd", set_rd, 2);
  
  rb_define_method(vdcgi, "exsql", rexsql, 2);
  rb_define_method(vdcgi, "exsql_h", rexsql_h, 2);
  rb_define_method(vdcgi, "level", get_level, 0);
  rb_define_method(vdcgi, "user_id", get_user_id, 0);
  rb_define_method(vdcgi, "lang", get_lang, 0);
  rb_define_method(vdcgi, "route", route, 4);
  rb_define_method(vdcgi, "param", getprm, 0);
  rb_define_method(vdcgi, "header", getcgi, 0);
  rb_define_method(vdcgi, "user_param", get_user_param, 0);
  rb_define_method(vdcgi, "pagewords", pagewords, 3);
  rb_define_method(vdcgi, "execsql", execsql_r, 2);
  rb_define_method(vdcgi, "pachtemplates", pachtemplates, 0);
  rb_define_method(vdcgi, "get_config", get_congig_r, 0);
  rb_define_method(vdcgi, "debug", debug, 1);
  rb_define_method(vdcgi, "getCockP", getCockP, 0);
  rb_define_method(vdcgi, "translitEnglR", translitEnglR, 1);
  rb_define_method(vdcgi, "set_content_lech", set_content_lech, 1);
  rb_define_method(vdcgi, "setparam", setparam, 2);
//   rb_define_method(vdcgi, "bazaNewconect", bazanewconect, 2);
  rb_define_method(vdcgi, "setActiv", setActiv, 4);
  rb_define_method(vdcgi, "setLang", setLang, 1);
  rb_define_method(vdcgi, "getParentUser", getParentUser, 0);
  rb_define_method(vdcgi, "insert_id", insert_id, 0);
  rb_define_method(vdcgi, "createWindowsShortcut", createWindowsShortcut, 4);
  rb_define_method(vdcgi, "replaceInFile", replaceInFile, 5);
  rb_define_method(vdcgi, "codeDll", codeDll, 3);
 
  rb_define_method(vdnet, "getHttpGet", getHttpGet, 5);
  rb_define_method(vdnet, "getHttpGets", getHttpGets, 5);
  rb_define_method(vdnet, "getPost", getPost, 5);
  rb_define_method(vdnet, "getPosts", getPosts, 5);
  rb_define_method(vdnet, "getHttpPosts", getHttpPosts, 5);
  rb_define_method(vdnet, "getPat", getPat, 5);
  rb_define_method(vdnet, "getPats", getPats, 5);
  rb_define_method(vdnet, "getHttpJson", getHttpJson, 5);
  rb_define_method(vdnet, "getHttpsJson", getHttpsJson, 5);
  rb_define_method(vdnet, "putHttpsJson", putHttpsJson, 5);
  rb_define_method(vdnet, "getHttpGetSocks",  getHttpGetSocks, 9);
  rb_define_method(vdnet, "getHttpGetSSocks",  getHttpGetSSocks, 9);
  rb_define_method(vdnet, "chekMailbox",  chmaixbox, 3);
  rb_define_method(vdnet, "chdomain",  chdomain, 2);
  rb_define_method(vdnet, "chmaixboxSSL",  chmaixboxSSL, 3);

 


  rb_define_method(admin, "set_pages", set_pages, 12);
  rb_define_method(admin, "pageparam", get_pageram, 1);
  rb_define_method(admin, "listaccess", get_listaccess, 0);
  rb_define_method(admin, "setCheckSum", setCheckSum, 2);
  rb_define_method(admin, "getSotextsForLeve", get_seotexts_for_level, 3);


  
  rb_define_method(mainapp, "write_title", write_title, 3);
  rb_define_method(mainapp, "listcontacts", get_listcontacts, 0);
  rb_define_method(mainapp, "regionpage", get_regionpage, 1);
  rb_define_method(mainapp, "menu", get_menu, 2);
  rb_define_method(mainapp, "menu_img", get_menu_img, 3);
  rb_define_method(mainapp, "javames", get_javames, 0);
  rb_define_method(mainapp, "namepage", get_namepage, 1);
  rb_define_method(mainapp, "accesspage", get_accesspage, 1);
  rb_define_method(mainapp, "fotos", get_fotos, 6);
  rb_define_method(mainapp, "fotoslink", get_fotoslink, 4);
  rb_define_method(mainapp, "sendmail", sendmail, 4);
  rb_define_method(mainapp, "listcounryactin", get_listcounryactin, 0);
  rb_define_method(mainapp, "listlang", get_listlang, 0);
  rb_define_method(mainapp, "getlang", get_langs, 1);
  rb_define_method(mainapp, "writelink", get_link, 4);
  rb_define_method(mainapp, "region_ex", get_region_ex, 0);
  rb_define_method(mainapp, "cityname", get_cityname, 1);
  rb_define_method(mainapp, "get_class", get_class, 1);
  rb_define_method(mainapp, "get_js", get_js, 2);

  
//   rb_define_method(img, "kapcha", get_kapcha, 0);
//   rb_define_method(img, "load_img", load_img, 5);
//   rb_define_method(img, "load_img_resize", load_img_resize, 6);

  
  rb_define_method(kassa, "unitbascet", get_unitbascet, 1);
  rb_define_method(kassa, "listpayemtsystem", get_listpayemtsystem, 0);
  rb_define_method(kassa, "listorderuser", get_listorderuser, 2);
  rb_define_method(kassa, "balansuser", get_balansuser, 1);
  rb_define_method(kassa, "listorderkassausers", get_listorderkassauser, 0);
  rb_define_method(kassa, "conunt_order", get_conunt_order, 1);
  rb_define_method(kassa, "outsumadmin", get_outsumadmin, 0);
  rb_define_method(kassa, "orderinerall", get_orderinerall, 0);
  rb_define_method(kassa, "orderoutall", get_orderoutall, 0);
  rb_define_method(kassa, "listdepositout", get_listdepositout, 0);
  
 
 
 

  rb_define_method(user, "username", get_username, 1);
  rb_define_method(user, "userparam", get_userparam, 1);
  
  rb_define_method(article, "conuntarticle", get_conuntarticle, 0);
  rb_define_method(article, "conuntarticlenew", get_conuntarticlenew, 1);
  rb_define_method(article, "listarticles", get_listarticles, 2);
  rb_define_method(article, "set_readarticle", set_readarticle, 2);
  rb_define_method(article, "get_readarticle", get_readarticle, 2);
  rb_define_method(article, "get_article", get_articles, 1);
  rb_define_method(article, "set_comment_article", set_comment_article, 3);
  rb_define_method(article, "set_wiewart", set_wiewart, 1);
  rb_define_method(article, "set_articles", set_articles, 15);
  rb_define_method(article, "countcomentrticle", get_countcomentrticle, 1);
  rb_define_method(article, "listcomentrticle", get_listcomentrticle, 1);

}