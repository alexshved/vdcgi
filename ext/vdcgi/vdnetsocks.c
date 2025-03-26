
#ifndef VDNETSOCKS_H
#define VDNETSOCKS_H
// #include "vdwr/wrap.h"
#include "vdcgi.h"
#include <stdlib.h>
#define h_addr h_addr_list[0]
#ifdef __cplusplus

extern "C"
{
#endif
	int writeSocket(char *mes, int len, int *socet_fd)
	{
		// debug_inner("send req");
		// debug_inner_int(len);
		fd_set wfds;
		struct timeval tv;
		int start_len = len;
		int r = 0;
		int max_fd = -1;
		if (*socet_fd > max_fd)
			max_fd = *socet_fd;

	loop_w:
		FD_ZERO(&wfds);
		FD_SET(*socet_fd, &wfds);
		tv.tv_sec = 3;
		tv.tv_usec = 500;

		select(max_fd + 1, NULL, &wfds, NULL, &tv);
		if (FD_ISSET(*socet_fd, &wfds))
		{

			int s = send(*socet_fd, mes, len, 0);

			if (s > 0)
			{

				r += s;
			}
			else
			{

				return r;
			}

			if (r < start_len)
			{
				len -= s;
				mes += s;
				goto loop_w;
			}
			else
			{
				return r;
			}
		}
		// debug_inner("send");
		// debug_inner_int(r);
		return r;
	}
	int writeSocketSSL(char *mes, int len, SSL *ssl, int *socet_fd)
	{
		int r = 0;
		fd_set wfds;
		struct timeval tv;
		int max_fd = -1;
		FD_ZERO(&wfds);
		FD_SET(*socet_fd, &wfds);
		tv.tv_sec = 3;
		tv.tv_usec = 500;
		if (*socet_fd > max_fd)
			max_fd = *socet_fd;
		select(max_fd + 1, NULL, &wfds, NULL, &tv);
		if (FD_ISSET(*socet_fd, &wfds))
		{
			SSL_write(ssl, mes, len);
			return 1;
		}
		return -1;
	}
	SSL_CTX *InitCTX(void)
	{
		SSL_METHOD *method;
		SSL_CTX *ctx;
		OpenSSL_add_all_algorithms();
		SSL_load_error_strings();
		method = TLSv1_2_client_method();
		ctx = SSL_CTX_new(method);
		SSL_CTX_set_options(ctx, SSL_OP_NO_SSLv2);
		if (ctx == NULL)
		{
			ERR_print_errors_fp(stderr);
			abort();
		}
		return ctx;
	}
	void LoadCertificates(SSL_CTX *ctx, char *CertFile, char *KeyFile)
	{
		if (SSL_CTX_use_certificate_file(ctx, CertFile, SSL_FILETYPE_PEM) <= 0)
		{
			ERR_print_errors_fp(stderr);
			abort();
		}
		if (SSL_CTX_use_PrivateKey_file(ctx, KeyFile, SSL_FILETYPE_PEM) <= 0)
		{
			ERR_print_errors_fp(stderr);
			abort();
		}
		if (!SSL_CTX_check_private_key(ctx))
		{
			//	    fprintf(stderr, "Private key does not match the public certificate\n");
			abort();
		}
	}
	char *readVDSocket(int *socket)
	{

		int buf_size = 1024 * 1024;
		char *buf = malloc(buf_size);
		bzero(buf, buf_size);
		char *tmp = (char *)malloc(buf_size);
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
		FD_SET(*socket, &rfds);
		int max_fd = -1;
		if (*socket > max_fd)
			max_fd = *socket;
		tv.tv_sec = 2;
		tv.tv_usec = 500;
		select(max_fd + 1, &rfds, NULL, NULL, &tv);
		int readMax = 1024 * 1000000;
		int size = 0;

		char *starone;
		int head_s = 0;
		// debug_inner("star read");
		if (FD_ISSET(*socket, &rfds))
		{
			// debug_inner("star read 1");
			do
			{
			rec_r:
				bzero(tmp, buf_size);
				l = recv(*socket, tmp, buf_size, 0);
				// debug_inner("read byte");
				// debug_inner_int(l);
				// debug_inner_c("read loop", tmp);
				char *cont = NULL;
				if (l > 0 && readMax == 1024 * 1000000 && (cont = strstr(buf, "Content-Length")) != NULL)
				{

					char *head = strstr(buf, "\r\n\r\n");
					head_s = head - buf;

					cont += 15;
					char *posit = strstr(cont, "\n");
					char str[100];
					bzero(str, 100);
					strncpy(str, cont, posit - cont);

					readMax = atoi(str) + head_s + 4;
					leh = atoi(str);
				}

				size += l;
				if (l > 0)
				{
					lr += l;
					if (lr >= r)
					{
						r += (buf_size * 2);
						buf = realloc(buf, r);
					}
					write = buf + kr;
					memcpy(write, tmp, l);
					kr += l;
				}
				FD_ZERO(&rfds);
				FD_SET(*socket, &rfds);
				tv.tv_sec = 1;
				tv.tv_usec = 500;
				if (select(max_fd + 1, &rfds, NULL, NULL, &tv) < 1)
				{
					// debug_inner("break 1");
					break;
				}
				if (!FD_ISSET(*socket, &rfds))
				{
					// debug_inner("break 2");
					break;
				}
			} while (l > 0 && readMax > size);
		}
		if (strstr(buf, "Content-Type: image"))
		{
			FILE *fl;

			char *img = strstr(buf, "\r\n\r\n") + 4;
			char filename[100];
			bzero(filename, 100);
			sprintf(filename, "/tmp/%i", randc(1000));

			fl = fopen(filename, "wb+");
			buf[kr + 1] = EOF;
			fwrite(img, 1, kr + 1, fl);
			fclose(fl);
			bzero(buf, kr + 1);
			strcpy(buf, filename);
		}

		free(tmp);
		return buf;
	}
	char *readVDSocketSSL(int *socket, SSL *ssl)
	{
		// fprintf(stderr,"start rad sock\n");
		int l = 0;
		int lr = 0;
		int kr = 0;
		int buf_size = 1024 * 4 * sizeof(char);
		int r = buf_size;
		char *buf = (char *)malloc(buf_size);
		bzero(buf, buf_size);
		char *tmp = (char *)malloc(buf_size);
		bzero(tmp, buf_size);
		int readMax = 1024 * 1000000;
		char *write;
		int oneone = 1;
		int size = 0;
		char *starone;
		int head_s = 0;
		struct timeval timeou;
		fd_set fds;
		do
		{
		start_l:
			l = SSL_read(ssl, tmp, buf_size);

			if (l > 0)
			{
				lr += l;
				if (lr >= r)
				{
					r += (buf_size * 2);
					buf = realloc(buf, r);
				}
				write = buf + kr;
				memcpy(write, tmp, l);
				kr += l;

				char *cont = NULL;
				if (readMax == 1024 * 1000000 && (cont = strstr(buf, "Content-Length")) != NULL)
				{
					char *head = strstr(buf, "\r\n\r\n");
					int head_s = head - buf;
					cont += 15;
					char *posit = strstr(cont, "\n");
					char str[100];
					bzero(str, 100);
					strncpy(str, cont, posit - cont);
					readMax = atoi(str) + head_s + 4;
				}
				else if (readMax == 1024 * 1000000 && (cont = strstr(buf, "HTTP/1.1")) != NULL)
				{
					// printf("buf %s\n",buf);
				}
			}
			// else{
			// printf(" received equal to or less than 0\n")
			int err = SSL_get_error(ssl, l);

			switch (err)
			{
			case SSL_ERROR_NONE:
			{
				int sock = SSL_get_rfd(ssl);
				FD_ZERO(&fds);
				FD_SET(sock, &fds);

				timeou.tv_sec = 5;
				timeou.tv_usec = 0;

				err = select(sock + 1, &fds, NULL, NULL, &timeou);

				if (err > 0)
					goto start_l;
				if (err == 0)
				{
					// timeout...
				}
				else
				{
					// error...
				}
				break;
			}
			case SSL_ERROR_ZERO_RETURN:
			{
				break;
			}
			case SSL_ERROR_WANT_READ:
			{

				int sock = SSL_get_rfd(ssl);
				FD_ZERO(&fds);
				FD_SET(sock, &fds);

				timeou.tv_sec = 5;
				timeou.tv_usec = 0;

				err = select(sock + 1, &fds, NULL, NULL, &timeou);

				if (err > 0)
					goto start_l;
				if (err == 0)
				{
					// timeout...
				}
				else
				{
					// error...
				}
				break;
			}
			default:
			{

				break;
			}
			}

			// break;
			// }
			// }
		} while (l > 0);

		if (strstr(buf, "Content-Type: image"))
		{
			FILE *fl;
			char *img = strstr(buf, "\r\n\r\n") + 4;
			fl = fopen("/tmp/fileload", "wb+");
			buf[kr + 1] = EOF;
			fwrite(img, 1, kr + 1, fl);
			fclose(fl);
			bzero(buf, kr + 1);
			strcpy(buf, "/tmp/fileload");
		}
		free(tmp);

		return buf;
	}

	int socksDialog(int *socet_fd, char *url, int prt, char *socksurl, int socksport, char *scocksLogin, char *scocksPass)
	{
		//    fprintf(stderr,"soket start\n\n");
		if (getConnect(socet_fd, socksurl, socksport) == 1)
		{
			struct hostent *phe;
			struct sockaddr_in sin;
			sin.sin_family = AF_INET;
			char buffer[1024];
			bzero(buffer, 1024);
			buffer[0] = 0x05;
			buffer[1] = 0x01;
			buffer[2] = 0x00;
			char chil[256];
			bzero(chil, 256);
			int lenreq = 3;
			if (writeSocket(&buffer[0], lenreq, socet_fd) > 0)
			{
				char *rez = (char *)malloc(256);
				bzero(rez, 256);
				recv(*socet_fd, rez, 256, 0);

				bzero(chil, 256);
				if (rez[1] == 0x02 && rez[0] == 0x05)
				{
					free(rez);
					bzero(buffer, 1024);
					buffer[0] = 0x05;
					buffer[1] = ((int)strlen(scocksLogin) + '0');
					strncpy(&buffer[1], scocksLogin, strlen(scocksLogin));
					int posit = strlen(scocksLogin) + 1;
					buffer[posit] = ((int)strlen(scocksPass) + '0');
					posit++;
					strncpy(&buffer[posit], scocksPass, strlen(scocksPass));
					posit += strlen(scocksPass);
					posit++;
					if (writeSocket(&buffer[0], posit, socet_fd) > 0)
					{
						rez = readVDSocket(socet_fd);
						if (rez[1] == 0x00 && rez[0] == 0x05)
						{
							free(rez);
							if (getConnect(socet_fd, socksurl, socksport) != 1)
								return -1;
							bzero(buffer, 1024);
							buffer[0] = 0x05;
							buffer[1] = 0x00;
							buffer[2] = 2;
							buffer[3] = 0x03;
							buffer[4] = ((int)strlen(url) + '0');
							strncpy(&buffer[5], url, strlen(url));
							int posit = 5 + strlen(url);
							uint16_t len = htons((unsigned short)prt);
							memcpy(&buffer[posit], &len, sizeof(len));
							posit += sizeof(len);
							posit++;
							if (writeSocket(&buffer[0], posit, socet_fd) > 0)
							{
								rez = readVDSocket(socet_fd);
								if (rez[1] == 0x00 && rez[0] == 0x05)
								{
									if (connect(*socet_fd, (struct sockaddr *)&sin, sizeof(sin)) != 0)
									{
										if (errno == EINPROGRESS)
										{
											//  fprintf(stderr, "wait\n\n");
										}
										else
										{
											perror("Error conect");
										}
										return -1;
									}
									else
									{
										return 1;
									}
								}
								else
								{
									free(rez);
									return -1;
								}
							}
							else
							{
								return -1;
							}
						}
						else
						{
							free(rez);
							return -1;
						}
					}
					else
					{
						free(rez);
						return -1;
					}
				}
				else if (rez[1] == 0x00)
				{
					bzero(buffer, 1024);
					buffer[0] = 0x05;
					buffer[1] = 0x01;
					buffer[2] = 0x00;
					buffer[3] = 0x03;
					int m = strlen(url);
					buffer[4] = m;
					memcpy(&buffer[5], url, m);
					unsigned short port = htons((unsigned short)prt);
					memcpy(&buffer[5 + m], &port, 2);
					struct hostent *target;
					if (writeSocket(&buffer[0], m + 7, socet_fd) > 0)
					{
						int rs = recv(*socet_fd, rez, 256, 0);
						if (rez[0] == 0x05 && rez[1] == 0x00)
						{
							const char *urlrez;
							if (rez[3] == 0x03)
							{
								int posport = 8;
								posport += (int)rez[4];
								urlrez = (char *)malloc(rez[4]);
								bzero(urlrez, rez[4]);
								strncpy(urlrez, &rez[5], rez[4]);
								free(urlrez);
							}
							else if (rez[3] == 0x01)
							{
								int posport = 9;
								unsigned long l_ip = *((unsigned long *)(rez + 4));
								unsigned short port = *((unsigned short *)(rez + 8));
							}
							return 1;
						}
						else
						{
							close(*socet_fd);
							free(rez);
							return -1;
						}
					}
					else
					{
						free(rez);
						return -1;
					}
				}
				else
				{
					free(rez);
					return -1;
				}
			}
		}
		else
		{
			return -1;
		}
	}

	int getConnect(int *socet_fd, char *socksurl, int socksport)
	{
		struct hostent *phe;
		struct sockaddr_in sin;

		memset(&sin, 0, sizeof sin);
		sin.sin_family = AF_INET;
		sin.sin_port = htons((unsigned short)socksport);
		phe = gethostbyname(socksurl);
		if (phe)
		{
			sin.sin_addr.s_addr = *(long *)(phe->h_addr);
		}
		else
		{
			//		fprintf(stderr, "phe\n");
			return -1;
		}
		*socet_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (*socet_fd < 0)
			return -1;
		if (connect(*socet_fd, (struct sockaddr *)&sin, sizeof(sin)) != 0)
		{
			if (errno == EINPROGRESS)
			{
				// fprintf(stderr, "wait\n\n");
			}
			else
			{
				//		    fprintf(stderr, "not started %i\n\n", errno);
				// perror("Error conect");
				return -1;
			}
		}
		else
		{

			return 1;
		}
		return -1;
	}

	int getConnectP(int *socet_fd, unsigned long socksurl, unsigned short socksport)
	{
		//     fprintf(stderr,"socksport %i \n\n",socksport);
		//    fprintf(stderr,"socksport %x %x  \n\n",socksport[0],socksport[1]);
		//     fprintf(stderr,"socksurl %hu \n\n",(in_port_t)socksurl);
		//    fprintf(stderr,"socksurl %s %s \n\n",socksurl,socksport);
		//    struct hostent *phe;
		struct sockaddr_in sin;
		memset(&sin, 0, sizeof sin);
		sin.sin_family = AF_INET;
		sin.sin_port = htons(socksport);
		//    fprintf(stderr,"sin.sin_port  %i %i %i \n\n",sin.sin_port, ntohs(sin.sin_port), socksport );
		sin.sin_addr.s_addr = socksurl;
		//    fprintf(stderr,"sin_addr %s \n\n",(char*)inet_ntoa(sin.sin_addr));
		//	fprintf(stderr,"socet_fd 116 \n\n");
		*socet_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		//    fprintf(stderr,"socet_fd %i \n",*socet_fd);
		if (*socet_fd < 0)
			return -1;
		//    fprintf(stderr,"socet_fd 116 \n\n");
		if (connect(*socet_fd, (struct sockaddr *)&sin, sizeof(sin)) != 0)
		{
			if (errno == EINPROGRESS)
			{
				//		    fprintf(stderr, "wait\n\n");
			}
			else
			{
				//		    fprintf(stderr, "not started2 %i\n\n", errno);
				perror("Error conect");
				return -1;
			}
		}
		else
		{
			// debug_inner("create success \n\n");s
			return 1;
		}
		return -1;
	}

	// int getConnectRezult(int* socet_fd, struct hostent *phe, char *socksport){
	//     struct sockaddr_in sin;
	// 	sin.sin_family = AF_INET;
	// 	memcpy(sin.sin_port,socksport,2);
	// 	if (phe) {
	// 		sin.sin_addr.s_addr = *(long*) (phe->h_addr);
	// 	    } else {
	// //		fprintf(stderr, "phe\n");
	// 		return -1;
	// 	    }
	// 	    *socet_fd = socket(AF_INET, SOCK_STREAM, 0);
	// 	    if (*socet_fd < 0) return -1;
	// 	    if (connect(*socet_fd, (struct sockaddr *) &sin, sizeof (sin)) != 0) {
	// 		if (errno == EINPROGRESS) {
	// 		    fprintf(stderr, "wait\n\n");
	// 		} else {
	// //		    fprintf(stderr, "not started2 %i\n\n", errno);
	// 		    return -1;
	// 		}
	// 	    } else {
	// 		return 1;
	// 	    }
	// 	    return -1;
	// }

	int getVdSocketNoBlock(int *socet_fd, char *url, int prt)
	{

		struct hostent *phe;
		struct sockaddr_in sin;
		sin.sin_family = AF_INET;

		sin.sin_port = htons((unsigned short)prt);
		phe = gethostbyname((const char *)url);

		if (phe)
		{
			sin.sin_addr.s_addr = *(long *)(phe->h_addr);
		}
		else
		{
			return -2;
		}
		*socet_fd = socket(AF_INET, SOCK_STREAM, 0);

		if (*socet_fd < 0)
			return -2;
		fd_set fdset;
		struct timeval tv;
		FD_ZERO(&fdset);
		FD_SET(*socet_fd, &fdset);
		tv.tv_sec = 2;
		tv.tv_usec = 0;
		fcntl(*socet_fd, F_SETFL, O_NONBLOCK);

		if (connect(*socet_fd, (struct sockaddr *)&sin, sizeof(sin)) != 0)
		{

			if (select((*socet_fd) + 1, NULL, &fdset, NULL, &tv) < 1)
			{

				close(*socet_fd);
				return -1;
			}
			else
			{

				return 1;
			}
		}
	}

	int getVdSocket(int *socet_fd, char *url, int prt, char *socksurl, int socksport, char *scocksLogin, char *scocksPass)
	{
		struct hostent *phe;
		struct sockaddr_in sin;
		sin.sin_family = AF_INET;
		if (socksport == 0)
		{
			sin.sin_port = htons((unsigned short)prt);
		}
		else
		{
			sin.sin_port = htons((unsigned short)socksport);
		}

		if (socksport == 0)
		{
			//            debug_inner(url);
			phe = gethostbyname((const char *)url);
		}
		else
		{
			phe = gethostbyname((const char *)socksurl);
		}

		if (phe)
		{
			sin.sin_addr.s_addr = *(long *)(phe->h_addr);
		}
		else
		{
			return -1;
		}

		*socet_fd = socket(AF_INET, SOCK_STREAM, 0);

		if (*socet_fd < 0)
			return -1;
		if (connect(*socet_fd, (struct sockaddr *)&sin, sizeof(sin)) != 0)
		{

			return -1;
		}
		else
		{

			if (socksport == 0)
			{
				return 1;
			}
			else
			{
				//    		fprintf(stderr,"INVOKE socksDialog\n\n");
				if (socksDialog(socet_fd, url, prt, socksurl, socksport, scocksLogin, scocksPass) == 1)
				{
					//                    fprintf(stderr,"rezult socksDialog 1\n\n");
					return 1;
				}
				else
				{
					//                    fprintf(stderr,"rezult socksDialog -1\n\n");
					close(*socet_fd);
					return -1;
				}
			}
		}
		return -1;
	}
	int getVdSocketSSL(SSL *ssl, int *socet_fd, char *url, int prt, char *socksurl, int socksport, char *scocksLogin, char *scocksPass)
	{
		//	 fprintf(stderr, "star1\n\n");
		struct hostent *phe;
		struct sockaddr_in sin;
		sin.sin_family = AF_INET;
		if (socksport == 0)
		{
			sin.sin_port = htons((unsigned short)prt);
		}
		else
		{
			sin.sin_port = htons((unsigned short)socksport);
		}
		fd_set rfds, wfds;
		struct timeval tv;
		int max_fd = -1;
		if (socksport == 0)
		{
			phe = gethostbyname((const char *)url);
		}
		else
		{
			phe = gethostbyname((const char *)socksurl);
		}
		if (phe)
		{
			sin.sin_addr.s_addr = *(long *)(phe->h_addr);
		}
		else
		{
			//		fprintf(stderr, "phe\n");
			return -1;
		}

		*socet_fd = socket(AF_INET, SOCK_STREAM, 0);
		if (*socet_fd < 0)
			return -1;
		if (connect(*socet_fd, (struct sockaddr *)&sin, sizeof(sin)) != 0)
		{
			if (errno == EINPROGRESS)
			{
				fprintf(stderr, "wait\n\n");
			}
			else
			{
				//		    fprintf(stderr, "not started3 %i\n\n", errno);
				return -1;
			}
		}
		else
		{
			if (socksport == 0)
			{
				if (SSL_set_fd(ssl, *socet_fd) == 0)
					ERR_print_errors_fp(stderr);
				return -1;
				if (SSL_connect(ssl) == -1)
				{
					ERR_print_errors_fp(stderr);
					return -1;
				}
				else
				{
					//			fprintf(stderr, "start2\n\n");
					return 1;
				}
			}
			else
			{
			}
		}
		return -1;
	}

#ifdef __cplusplus
}
#endif

#endif /* VDNETSOCKS_H */
