
#ifndef ADMIN_H
#define ADMIN_H

#ifdef __cplusplus
extern "C" {
#endif
#include "vdcgi.h"
    
    
 VALUE set_pages(VALUE self, VALUE idstr, VALUE idparent_p, VALUE link, VALUE keyw, VALUE titl, VALUE descr, VALUE tegs, VALUE name, VALUE positions, VALUE region, VALUE shablon, VALUE access ){
     if(TYPE(idstr) == T_NIL)
	idstr = rb_str_new2("0");
     if(TYPE(idparent_p) == T_NIL)
	idparent_p = rb_str_new2("0");
     if(TYPE(link) == T_NIL)
	link = rb_str_new2(" ");
     if(TYPE(keyw) == T_NIL)
	keyw = rb_str_new2(" ");
     if(TYPE(keyw) == T_NIL)
	keyw = rb_str_new2(" ");
     if(TYPE(titl) == T_NIL)
	titl = rb_str_new2(" ");
     if(TYPE(descr) == T_NIL)
	descr = rb_str_new2(" ");
     if(TYPE(tegs) == T_NIL)
	tegs = rb_str_new2(" ");
     if(TYPE(name) == T_NIL)
	name = rb_str_new2(" ");
     if(TYPE(positions) == T_NIL)
	positions = rb_str_new2("0");
     if(TYPE(shablon) == T_NIL)
	shablon = rb_str_new2(" ");
     if(TYPE(access) == T_NIL)
	access = rb_str_new2("0");
     if(TYPE(region) == T_NIL) 
	region = rb_str_new2("0");
     if(strlen(StringValuePtr(idstr)) == 0) return T_NIL;
    int idp = atoi(StringValuePtr(idstr));
    char *p[7];
    
    p[0] = pref;
    p[1] = StringValuePtr(positions);
    p[2] = StringValuePtr(idparent_p);
    execsql(3, "update ~pages set positions = positions + 1 where positions >= '~' and parent_id = '~';", p);
    char *insid;
    if(idp > 100000000){
    Rezultsql lang;
    gel_list_lang_iner(&lang);
        if( lang.rows > 0 && lang.colun > 0) {
            for(int i = 0; i < lang.rows; i++) {
                char pr[1024];
                bzero(pr,1024);
                strcpy(pr,lang.result[i][2]);
                strcat(pr,config.baza);
                p[0] = pr;
                p[2] = StringValuePtr(name);
                p[3] = StringValuePtr(idparent_p);
                p[4] = StringValuePtr(region);
                p[5] = StringValuePtr(access);
                execsql(6,
                        "insert ~.pages set positions = '~', title = '~', parent_id = '~', region_id = '~', access = '~';",
                        p);
                insid = InsId();
            }
            clearMysqRez(&lang);
        }
    }else{
	p[2] = StringValuePtr(name);
	p[3] = StringValuePtr(access);
	p[4] = StringValuePtr(idstr);
	insid = (char*)malloc(12);
	bzero(insid,12);
	strcpy(insid,StringValuePtr(idstr));
	execsql(5, "update ~pages set positions = '~', title = '~', access = '~' where id = '~';", p);
    }
    
    char *link_rez;
    if(strlen(StringValuePtr(link)) > 3){
	link_rez = (char*) malloc(strlen(StringValuePtr(link)+8));
//	bzero(link_rez,strlen(StringValuePtr(link)+8));
	strcpy(link_rez,StringValuePtr(link));
    }else if(atoi(insid) == 1){
	link_rez = (char*) malloc(2);
	bzero(link_rez,2);
	
    }else{
	char *tmp = translitEngl(StringValuePtr(name));
	char *temp = (char*)malloc(strlen(tmp) + 1024);
	bzero(temp,(strlen(tmp) + 1024));
	strcpy(temp,tmp);
	link_rez = (char*)malloc(strlen(tmp) + 1024);
	bzero(link_rez,(strlen(tmp) + 1024));
	char *pt[2];
	pt[0] = pref;
	pt[1] = temp;
	test: ;
	Rezultsql rez;
	exsql(2, "select id from ~seotexts where link = '~'", pt, &rez);
	if(rez.colun != 0 && rez.rows != 0){
            char rnd[1024];
            bzero(rnd,1024);
            sprintf(rnd,"%i",randm());
	    clearMysqRez(&rez);
	    strcat(temp,rnd);
	    goto test;
	}else{
	    strcpy(link_rez,temp);
	}      
	free(tmp);
	free(temp);
    }
//     fprintf(stderr,"link_rez %s\n",link_rez);
//    debug_inner("link");
//    debug_inner(link_rez);
    
     
    if(idp <= 100000000){
	char *pa[11];
	pa[0] = pref;
	pa[1] = link_rez;
	pa[2] = StringValuePtr(titl);
	pa[3] = StringValuePtr(keyw);
	pa[4] = StringValuePtr(descr);
	pa[5] = StringValuePtr(tegs);
	pa[6] = StringValuePtr(shablon);
	pa[7] = StringValuePtr(access);
	pa[8] = insid;
	pa[9] = StringValuePtr(idparent_p);
        pa[10] = StringValuePtr(access);

                execsql(11,
                        "update ~seotexts set  link = '~', titl = '~', keyw = '~', descr = '~', tegs = '~', shablon = '~', level = '~'  where str = '~' and pstr = '~' and level = '~'  ;",
                        pa);

    }else{
	char *pa[10];
	pa[0] = pref;
	pa[1] = link_rez;
	pa[2] = StringValuePtr(titl);
	pa[3] = StringValuePtr(keyw);
	pa[4] = StringValuePtr(descr);
	pa[5] = StringValuePtr(tegs);
	pa[6] = insid;
	pa[7] = StringValuePtr(idparent_p);
	pa[8] = StringValuePtr(shablon);
	pa[8] = StringValuePtr(shablon);
	pa[9] = StringValuePtr(access);
        Rezultsql lang;
        gel_list_lang_iner(&lang);
        if( lang.rows > 0 && lang.colun > 0) {
        for (int i = 0; i < lang.rows; i++) {
        char pr[1024];
        bzero(pr,1024);
        strcpy(pr,lang.result[i][2]);
        strcat(pr,config.baza);
        pa[0] = pr;
	    execsql(10, "insert ~.seotexts set link = '~', titl = '~', keyw = '~', descr = '~', tegs = '~', str = '~', pstr = '~', shablon = '~', level = '~' ;", pa);
        }
         clearMysqRez(&lang);
     }
    }
    char root[1024];
    bzero(root,1024);
    getcwd(root,1024); 
    char * rt = strstr(root,"/public");
    bzero(rt,5);
    char pch_temp[1024];
    bzero(pch_temp,1024);
    strcpy(pch_temp,root);
    strcat(pch_temp,"/public/templates/");
    
    strcat(pch_temp,StringValuePtr(shablon));
//    debug_inner("pach");
//    debug_inner(pch_temp);
//    debug_inner("pach1");
//    fprintf(stderr,"pch_temp %s\n",pch_temp);
    FILE *fl = fopen (pch_temp,"a");
    if(fl != NULL) fclose(fl);
    if(idp > 100000000){
        Rezultsql  rezult;
	char *pr[2];
	pr[0] = pref;
	pr[1] = StringValuePtr(idparent_p);
	exsql(2, "select id from ~page_photosn where parent_id = '~'", pr,&rezult);
	if(rezult.colun != 0 && rezult.rows != 0){
	    char *ps[3];
	    ps[0] = pref;
	    ps[1] = insid;
	    ps[2] = StringValuePtr(idparent_p) ;
	    execsql(3, "update ~page_photosn set parent_id = '~' where parent_id = '~';", ps);
	    char pch[1024];
	    bzero(pch,1024);
	    strcpy(pch,root);
	    strcat(pch,"/images");
	    DIR  * dir = opendir(pch);
	    struct dirent * dirEntry;
	    if (dir) {
		while (0 != (dirEntry = readdir(dir))) {
		    if(strcmp(dirEntry->d_name,".") != 0 && strcmp(dirEntry->d_name,"..") != 0){
			char chk[1024];
			bzero(chk,1024);
			sprintf(chk,"%s/images/%s/page_photos/%s",root,dirEntry->d_name,StringValuePtr(idparent_p));
			DIR  * direx = opendir(chk);
			if(direx != 0){
			    closedir(direx);
			    char cmd[1024];
			    bzero(cmd,1024);
			    sprintf(cmd,"mv -u %s %s/images/%s/page_photos/%s",chk, root, dirEntry->d_name,insid);
			    system(cmd);
			}
		    }
		}
		closedir(dir);
	      }
	    clearMysqRez(&rezult);
	}
    }
    VALUE rezult;
    if(idp > 100000000){
        rb_encoding * en = rb_utf8_encoding();
        rezult = rb_enc_str_new_cstr(insid, en);
    }else{
        rb_encoding * en = rb_utf8_encoding();
        rezult = idstr;
    }
    free(link_rez);
    free(insid);
    return rezult;
    
    
    }

 VALUE get_seotexts_for_level(VALUE self, VALUE id,  VALUE idp, VALUE level ){
     if(TYPE(id) == T_NIL)
         id = rb_str_new2("0");
     if(TYPE(idp) == T_NIL)
         idp = rb_str_new2("0");
     if(TYPE(level) == T_NIL)
         level = rb_str_new2("0");
     VALUE rezult = rb_hash_new();
     char *p[4];
     p[0] = pref;
     p[1] = StringValuePtr(id);
     p[2] = StringValuePtr(idp);
     p[3] = StringValuePtr(level);
     Rezultsql rez;
     rb_encoding * en = rb_utf8_encoding();
     exsql(4, "select id , titl , keyw , descr , tegs , link , arti , str , pstr ,  reg , shablon, level , user_id  from ~seotexts m where str = '~' and pstr = '~' and level = '~'", p, &rez);
     if( rez.rows > 0 && rez.colun > 0){
         rb_hash_aset(rezult, rb_str_new2("id"), rb_enc_str_new_cstr(rez.result[0][0], en)) ;
         rb_hash_aset(rezult, rb_str_new2("titl"), rb_enc_str_new_cstr(rez.result[0][1], en)) ;
         rb_hash_aset(rezult, rb_str_new2("keyw"), rb_enc_str_new_cstr(rez.result[0][2], en)) ;
         rb_hash_aset(rezult, rb_str_new2("descr"), rb_enc_str_new_cstr(rez.result[0][3], en)) ;
         rb_hash_aset(rezult, rb_str_new2("tegs"), rb_enc_str_new_cstr(rez.result[0][4], en)) ;
         rb_hash_aset(rezult, rb_str_new2("link"), rb_enc_str_new_cstr(rez.result[0][5], en)) ;
         rb_hash_aset(rezult, rb_str_new2("arti"), rb_enc_str_new_cstr(rez.result[0][6], en)) ;
         rb_hash_aset(rezult, rb_str_new2("str"), rb_enc_str_new_cstr(rez.result[0][7], en)) ;
         rb_hash_aset(rezult, rb_str_new2("pstr"), rb_enc_str_new_cstr(rez.result[0][8], en)) ;
         rb_hash_aset(rezult, rb_str_new2("reg"), rb_enc_str_new_cstr(rez.result[0][9], en)) ;
         rb_hash_aset(rezult, rb_str_new2("shablon"), rb_enc_str_new_cstr(rez.result[0][10], en)) ;
         rb_hash_aset(rezult, rb_str_new2("level"), rb_enc_str_new_cstr(rez.result[0][11], en)) ;
         rb_hash_aset(rezult, rb_str_new2("user_id"), rb_enc_str_new_cstr(rez.result[0][12], en)) ;
         clearMysqRez(&rez);
     }
     return rezult;
 }

 VALUE get_pageram(VALUE self, VALUE id){
     if(TYPE(id) == T_NIL)
	id = rb_str_new2("");
	VALUE rezult = rb_hash_new();
	char *p[2];
	p[0] = pref;
	p[1] = StringValuePtr(id);
	Rezultsql rez;
	rb_encoding * en = rb_utf8_encoding();
	exsql(2, "select id, title, positions, region_id, access, edit, title2, text_iner, parent_id from ~pages m where id = '~'", p, &rez);
	 if( rez.rows > 0 && rez.colun > 0){
	    rb_hash_aset(rezult, rb_str_new2("id"), rb_enc_str_new_cstr(rez.result[0][0], en)) ;
	    rb_hash_aset(rezult, rb_str_new2("title"), rb_enc_str_new_cstr(rez.result[0][1], en)) ;
	    rb_hash_aset(rezult, rb_str_new2("positions"), rb_enc_str_new_cstr(rez.result[0][2], en)) ;
	    rb_hash_aset(rezult, rb_str_new2("region_id"), rb_enc_str_new_cstr(rez.result[0][3], en)) ;
	    rb_hash_aset(rezult, rb_str_new2("access"), rb_enc_str_new_cstr(rez.result[0][4], en)) ;
	    rb_hash_aset(rezult, rb_str_new2("edit"), rb_enc_str_new_cstr(rez.result[0][5], en)) ;
	    rb_hash_aset(rezult, rb_str_new2("title2"), rb_enc_str_new_cstr(rez.result[0][6], en)) ;
	    rb_hash_aset(rezult, rb_str_new2("text_iner"), rb_enc_str_new_cstr(rez.result[0][7], en)) ;
	    rb_hash_aset(rezult, rb_str_new2("parent_id"), rb_enc_str_new_cstr(rez.result[0][8], en)) ;
	    clearMysqRez(&rez);    
	 }
	return rezult;
    }
VALUE get_listaccess(VALUE self){
	VALUE rezult = rb_ary_new();
	char *p[1];
	p[0] = pref;
	Rezultsql rez;
	exsql(1, "SELECT user_type, access FROM  ~access ", p, &rez);
	    if( rez.rows > 0 && rez.colun > 0){
		rb_encoding * en = rb_utf8_encoding();
		for(int i = 0; i < rez.rows; i++){
		    VALUE temp = rb_hash_new();
		    rb_hash_aset(temp, rb_str_new2("user_type"), rb_enc_str_new_cstr(rez.result[i][0], en)) ;
		    rb_hash_aset(temp, rb_str_new2("access"), rb_enc_str_new_cstr(rez.result[i][1], en)) ;
		    rb_ary_push(rezult,temp);
		}
		clearMysqRez(&rez);    
	    }
	return rezult;
    }

VALUE setCheckSum(VALUE self, VALUE buf , VALUE size){
    BYTE* rezult = (BYTE*)StringValuePtr(buf);
    checksum((BYTE*)StringValuePtr(buf), NUM2INT(size));
    rb_encoding * en = rb_default_internal_encoding();
    VALUE ret = rb_enc_str_new(rezult,NUM2INT(size),en);
    return ret;
 }

void checksum(BYTE *ebuf, DWORD dwLength)
{
    DWORD CRC,i;
    WORD wCRC;
    bool blAA55 = false;
//    debug_inner("________________\n");
//    debug_inner_int(dwLength);
    if (dwLength == 1536*1024 || dwLength == 2048*1024) {
        CRC = CheckCRC1280(ebuf,dwLength);
        *(DWORD*)&ebuf[0x3084] = CRC;
        if (*(WORD*)&ebuf[0x3080] != 0) {
            *(WORD*)&ebuf[0x3080] = 0;
            wCRC = CheckCRC1536(ebuf,dwLength);
            if (wCRC != 0xAA55) {
                wCRC -= 0xAA55;
                wCRC = -wCRC;
                *(WORD*)&ebuf[0x3080] = wCRC;
            }
        }
    }
    else if (dwLength == 1280*1024)
        blAA55 = false;
    for (i = 0; i < dwLength; i++) {
        if (ebuf[i] == 0xAA && ebuf[i+1] == 0x06 && ebuf[i+2] == 0x55 && ebuf[i+3] == 0xAA) {
            blAA55 = true;
            break;
        }
    }
    if (*(DWORD*)&ebuf[0x3084] != 0) {
        CRC = CheckCRC1280(ebuf,dwLength);
        *(DWORD*)&ebuf[0x3084] = CRC;
        if (*(WORD*)&ebuf[0x3080] != 0 && !blAA55) {
            *(WORD*)&ebuf[0x3080] = 0;
            wCRC = CheckCRC1280_2(ebuf,dwLength);
            if (wCRC != 0xAA55) {
                wCRC -= 0xAA55;
                wCRC = -wCRC;
                *(WORD*)&ebuf[0x3080] = wCRC;
            }
        }
        else if (*(WORD*)&ebuf[0x3080] != 0 && blAA55) {
            *(WORD*)&ebuf[0x3080] = 0;
            wCRC = CheckCRC1280_3(ebuf,dwLength);
            if (wCRC != 0xAA55) {
                wCRC -= 0xAA55;
                wCRC = -wCRC;
                *(WORD*)&ebuf[0x3080] = wCRC;
            }
        }
    }
    else {
        *(WORD*)&ebuf[0x3080] = CheckCRC1280_2(ebuf,dwLength);;
    }
}


DWORD CheckCRC1280_2(BYTE* ebuf,DWORD dwLength)
{
    DWORD summ,i;

    summ = 0;

    for (i = 0; i < 0x3080; i++) {
        summ += ebuf[i];
        summ &= 0x0000FFFF;
    }
    i += 4;
    for (; i < dwLength; i++) {
        summ += ebuf[i];
        summ &= 0x0000FFFF;
        summ &= 0x7FFF;
    }
    summ += 0x8000;

    return summ;
}

DWORD CheckCRC1280_3(BYTE* ebuf,DWORD dwLength)
{
    DWORD summ,i;

    summ = 0;

    for (i = 0; i < dwLength; i += 4) {
        summ += *(DWORD*)&ebuf[i];
        summ += ((*(DWORD*)&ebuf[i])>>16);
        summ &= 0x0000FFFF;
    }

    return summ;
}

DWORD CheckCRC1280(BYTE* ebuf,DWORD dwLength)
{
    DWORD summ1,summ2,temp1,temp2,i,j,k;

    j = dwLength;
    summ1 = 1;
    summ2 = 0;
    i = 0;

    while (j) {
        if (j > 0x15AE) {
            k = 0x15AE;
        }
        else {
            k = j;
        }

        j -= k;

        while(k) {
            if ((i < 0x3080) || (i > 0x3087)) {
                summ1 += ebuf[i];
            }
            summ2 += summ1;
            i++;
            k--;
        }

        temp1 = summ1;
        temp2 = summ1;
        temp1 &= 0x0000FFFF;
        temp2 >>= 16;
        temp2 *= 0x0F;
        summ1 = temp1 + temp2;

        temp1 = summ2;
        temp2 = summ2;
        temp1 &= 0x0000FFFF;
        temp2 >>= 16;
        temp2 *= 0x0F;
        summ2 = temp1 + temp2;
    }

    if (summ1 > 0xFFF1) {
        summ1 += 0xFFFF000F;
    }

    temp1 = summ2;
    temp2 = summ2;
    temp1 &= 0x0000FFFF;
    temp2 >>= 16;
    temp2 *= 0x0F;
    summ2 = temp1 + temp2;

    if (summ2 > 0xFFF1) {
        summ2 += 0xFFFF000F;
    }

    summ2 <<= 16;
    summ2 |= summ1;

    return summ2;
}

DWORD CheckCRC1536(BYTE* ebuf,DWORD dwLength)
{
    DWORD summ,temp1,i;

    summ = 0;

    for (i = 0; i < dwLength; i+=4) {
        temp1 = *((DWORD*)&ebuf[i]);
        summ += temp1;
        temp1 >>= 16;
        summ += temp1;
        summ &= 0x0000FFFF;
    }

    return summ;
}

#ifdef __cplusplus
}
#endif

#endif /* ADMIN_H */

