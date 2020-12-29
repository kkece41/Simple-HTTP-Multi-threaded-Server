
#define log_info(M, ...) fprintf(stderr, "[INFO] (%s:%d:%s) " M "\n", __FILE__, __LINE__,__func__, ##__VA_ARGS__)	
