#include <stdio.h>
#include <stdlib.h>

char * pre = "model name";
const char * get_model_name() {
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen("/proc/cpuinfo", "r");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }

    while ((read = getline( & line, & len, fp)) != -1) { 
        
        if (strncmp(pre, line, strlen(pre)) == 0) {
            return line;
        }
    }

    fclose(fp);
    if (line) {
        free(line);
    }
    return "unknown";
}

int main(void) {
    //read hostname
    char hostname[1024];
    gethostname(hostname, 1024);

    //cpu model from file
    char * model_name = get_model_name();
    
    char m_name[255];
    memcpy( m_name, &model_name[strlen(pre)+3], strlen(model_name));
    m_name[strlen(model_name)] = '\0';
    
    printf("Hello World from %s CPU #%s \n", hostname, m_name);

    return 0;
}