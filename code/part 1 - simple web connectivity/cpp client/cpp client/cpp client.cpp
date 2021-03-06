// WebPUTcurl.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../libcurl/include/curl/curl.h"

#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>

#pragma comment(lib, "../libcurl/lib/libcurl_a.lib")

void parseTXT(void *ptr, size_t size, size_t nmemb, void *stream)
{
	printf("\n\n");
	printf("Server response:");
	printf((char*)ptr);
	printf("\n\n");
}

int main(int argc, char **argv)
{
	CURL *curl;
	CURLcode res;
	
	curl_global_init(CURL_GLOBAL_ALL);
	
	bool bQuit = false;

	while (bQuit == false)
	{
		printf("1-POST\n");
		printf("2-GET\n");
		printf("X-QUIT\n");

		char ch = getchar();
		fseek(stdin, 0, SEEK_END);

		printf("\n\n");

		if(ch == '1')		//POST
		{
			curl = curl_easy_init();
			curl_slist* headers = NULL;

			//headers = curl_slist_append(headers, "client_id_header");
			headers = curl_slist_append(headers, "application/x-www-form-urlencoded");

			curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
			curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:80/post_newscore/");
			curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST"); /* !!! */

			curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "insert into highscores(name, score) values('Me', 3000)"); /* data goes here */
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, parseTXT);

			res = curl_easy_perform(curl);

			curl_slist_free_all(headers);	
			curl_easy_cleanup(curl);
		}

		if (ch == '2') //GET
		{
			curl = curl_easy_init();
			curl_slist* headers = NULL;

			//headers = curl_slist_append(headers, "client_id_header");
			headers = curl_slist_append(headers, "application/x-www-form-urlencoded");

			curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
			curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:80/get_highscores/");
			curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET"); /* !!! */

			curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "select * from highscores order by score desc"); /* data goes here */
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, parseTXT);

			res = curl_easy_perform(curl);

			curl_slist_free_all(headers);			
			curl_easy_cleanup(curl);
		}

		if ((ch == 'X') || (ch == 'x'))
		{
			bQuit = true;
		}
	}
	
	
	curl_global_cleanup();
	return 0;
}

