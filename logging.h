#define LOG_RECEIVE 1
#define LOG_SEND 2
#define LOG_ERROR 3

int set_log_file_name(char*, char*);
int log_receive(char*, char*);
int log_send(char*, char*);
int log_error(char*, char*);
int generalised_log(char*, char*, short);
