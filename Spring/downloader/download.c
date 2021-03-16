#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

int progress_callback(void *ptr, curl_off_t dltotal, curl_off_t dlnow, curl_off_t ultotal, curl_off_t ulnow) {
    fprintf(stderr, "\r");
    fflush(stderr);
    fprintf(stderr, "Bytes Downloaded %li", dlnow);
    
    return 0;
}

// file helper functions helpfully provided by Parth
size_t fileSize(FILE *f){
    fseek(f, 0L, SEEK_END);
    size_t pos = ftell(f);
    rewind(f);
    return pos;
}

size_t numLines(FILE *f){
    rewind(f);
    size_t fs = fileSize(f);
    size_t i = 0;
    while(ftell(f) < fs){
        char* current = malloc(fs);
        fgets(current,fs,f);
        free(current);
        i++;
    }
    rewind(f);
    return i;
}

void stringify(char* string, FILE *f){
    size_t fs = fileSize(f);
    size_t lines = numLines(f);
    for(int i = 0; i < lines; i++){
        char* line = malloc(fs);
        fgets(line,fs,f);
        string = strcat(string,line);
        free(line);
    }
}

// my code again :)
char *download_url(const char *url) {
    const char *data_store_name = "download_data_store";
    FILE *writer = fopen(data_store_name, "w+");

    CURL *curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);

        curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0); 
        curl_easy_setopt(curl, CURLOPT_XFERINFOFUNCTION, progress_callback); 
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, writer);

        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            fprintf(stderr, "ERROR: curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }

        char *output = malloc(fileSize(writer));
        stringify(output, writer);

        fclose(writer);
        remove(data_store_name);
        curl_easy_cleanup(curl);

        return output;
    }
    
    return NULL;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, argc < 2 ? "Please input a URL" : "Please input just one URL");
        return 1;
    }
    
    const char *download = download_url(argv[1]);
    printf("%s", download);

    return 0;
}
