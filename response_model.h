struct response_model {
    time_t t1;
    time_t t2;
    time_t t3;
    time_t t4;
};

void response_model_fill_with(char*, struct response_model*);
time_t print_response_model(struct response_model*);
int set_system_time(time_t);
