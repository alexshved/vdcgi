

#ifndef MYMYSQL_H
#define MYMYSQL_H


#include <stdio.h>

#include "vdcgi.h"


#ifdef __cplusplus
extern "C" {
#endif
int prepareqw(int i, char *qw, char **par, char *buf){
	int sq = getMysq();
    char *tmst = (char*)malloc((strlen(qw) + 5));
    bzero(tmst,((strlen(qw) + 5)));
   	memcpy(tmst,qw,strlen(qw));
    char *tm = strtok(tmst,"~");
    int lst = 0; 
    strcpy(buf,tm);
    lst = strlen(buf);
    if(i > 0) mysql_real_escape_string(&mysql[sq].mysql, &buf[lst], par[0], strlen(par[0]));
    int f = 1;
    while(tm = strtok(NULL,"~")){
		strcat(buf,tm);
		lst = strlen(buf);
		if(f<i) mysql_real_escape_string(&mysql[sq].mysql, &buf[lst], par[f], strlen(par[f]));
		f++;
    }
    
    free(tmst);
    return 1;
}

int clearMysqRez(Rezultsql *rez){
	
    if(rez->coolname != NULL){
        for(int i = 0; i < rez->colun; i++){
            if(rez->coolname[i] != NULL) free(rez->coolname[i]);
        }
    }
    if(rez->coolname != NULL) free(rez->coolname);
    for(int i = 0; i < rez->rows; i++){
		for(int z = 0; z < rez->colun; z++){
		    if(rez->result[i][z] != NULL) free(rez->result[i][z]);
		    rez->result[i][z] = NULL;	
		} 
		if(rez->result[i] != NULL) free(rez->result[i]);
		rez->result[i] = NULL;
    }
    rez->colun = 0;
    rez->rows = 0;
    if(rez->result != NULL) free(rez->result);
    return 0;
}

int exsql(int iq, char *qw, char **par, Rezultsql *rez){
    int sq = getMysq();
//    debug_inner("baza\n");
//    debug_inner_int(sq);
    if(baza_reconect(&mysql[sq].mysql) != 0){
        rez->rows = 0;
        mysql[sq].busy = 0;
        return -1;
     }
    int rezz = 1;
    int lena = 0;
    if(iq > 0){
	for(int y = 0 ; y < iq; y++) lena += strlen(par[y]);
    }
    
    lena += strlen(qw) + 1024;
	char *qv = (char*)malloc(lena);
	bzero(qv,lena);
	char *fre_cw = qv;
	int lenwv = 0;
	if(iq > 0){
	    lenwv = prepareqw(iq, qw, par,qv);
	    if( lenwv == -1){
	       rez->rows = 0; 
	       rezz = -1;
            mysql[sq].busy = 0;
	       return rezz;
	    }
	}else{
	    strcpy(qv,qw);
	    }
	  
	if(lenwv != -1){
        if(config.devel == 1){
            debug_inner(qv);
        }
	    if(mysql_query( &mysql[sq].mysql, (const char*)qv) == 0){
			MYSQL_RES *result;
			unsigned int num_fields;
			unsigned int i = 0;
			result = mysql_store_result( &mysql[sq].mysql );
			num_fields = mysql_num_fields(result);
                        rez->rows = mysql_num_rows(result);
                        MYSQL_FIELD *field;
                        if(num_fields != 0 && rez->rows != 0){
                            rez->coolname = (char**)malloc(num_fields * 8);
                            while((field = mysql_fetch_field(result))){
                            rez->coolname[i] = (char*)malloc(field->name_length + 100);
                            bzero(rez->coolname[i],(field->name_length + 100));
                            strcpy(rez->coolname[i],field->name);

                            i++;
                            }
                        }else{
                            rez->coolname = NULL;
                        }
                        i = 0;
			if(num_fields != 0 && rez->rows != 0){
			    MYSQL_ROW row;
			    rez->colun = num_fields;
			    rez->result = (char***)malloc(rez->rows * rez->colun * sizeof(char*) * 2);
			    for(int m = 0; m < rez->rows; m++) rez->result[m] = (char**)malloc(rez->colun * sizeof(char*));
			    int ro = 0;
			    while(row = mysql_fetch_row(result)){
				unsigned long *lengths;
				lengths = mysql_fetch_lengths(result);
				for(i = 0; i < num_fields; i++){
				    if(row[i] != NULL && (int)lengths[i] > 0){
				    int les = (int)lengths[i]+24;
					rez->result[ro][i] = (char*)malloc(les);
					bzero(rez->result[ro][i],les);
					memcpy(rez->result[ro][i],row[i],(int)lengths[i]);
					}else{
					rez->result[ro][i] = (char*)malloc(5);
					bzero(rez->result[ro][i],5);
					rez->result[ro][i][0] = '\0';
				    }
				}
				ro++;
			    }
			}else{ 
			rezz = -1;
                        }
			mysql_free_result(result);
	    } else{
		mysql_error(&mysql[sq].mysql);
		rez->rows = 0;
		rezz = -1;
	    }
	}
	free(qv);
    mysql[sq].busy = 0;
        return rezz;
}

char *InsId(){
    int i = mysql_insert_id(last_ql);
    // debug_inner_int(i);
    char *rezult = (char*)(malloc(12));
    bzero(rezult,12);
    sprintf(rezult,"%i",i);
    return rezult;
}

int InsIdInt(){
    return mysql_insert_id(last_ql);
}

char * setTable(char *qw){
    char *istr;
    if(strstr(qw,"into") || strstr(qw,"INTO")){
        istr = strtok (qw," ");
        istr = strtok (NULL," ");
        istr = strtok (NULL," ");
    }else {
        istr = strtok (qw," ");
        istr = strtok (NULL," ");
    }
    char *tab = malloc(strlen (istr)+1);
    strcpy(tab,istr);
    return tab;
//    debug_inner_c("table: ",*tab);
}

int getMysq(){
    int ms_c = 0;
    for(ms_c = 0; ms_c < config.threed; ms_c++) {
        if(mysql[ms_c].busy == 0){
            mysql[ms_c].busy = 1;
            return ms_c;
        }
    }
    return 0;
}

int execsql(int iq, char *qw, char **par){
    int sq = getMysq();
    
//    
    if(baza_reconect(&mysql[sq].mysql) != 0){

        mysql[sq].busy = 0;
        return -1;
    }
  int lena = 0;
    for(int y = 0 ; y < iq; y++){
     lena += strlen(par[y]);
 	}
    lena += strlen(qw) + 1024;
    char *qv = (char*)malloc(lena + 50);
    bzero(qv,lena + 50);
    int lenq = 0;
    if((lenq = prepareqw(iq, qw, par,qv)) == -1){
            free(qv);
            mysql[sq].busy = 0;
            return -1;
	    }
    if(config.devel == 1){
		debug_inner(qv);
	    }
     int mqs =  mysql_real_query(&mysql[sq].mysql, qv, strlen(qv));
    
    //  debug_inner_int(mqs);   
     if(mqs == 0){
        // debug_inner("table: ");
        last_ql = &mysql[sq].mysql;
		free(qv);
         mysql[sq].busy = 0;
        return 1;
     } else {
        // debug_inner("table no: ");
        last_ql = &mysql[sq].mysql;
		free(qv);
         mysql[sq].busy = 0;
        return 0;
     }               
  }

#ifdef __cplusplus
}
#endif

#endif /* MYMYSQL_H */

