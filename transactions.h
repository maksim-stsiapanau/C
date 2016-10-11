typedef long time_t; 

//structure include information about transaction
typedef struct {
	char *transaction_name; // name of transaction
	double transaction_response_time; //response time
	time_t time; // time when transaction occurred
	char *server_name; // server ip where transaction occerred
	char *server_port; // server port
} transaction_info;


//dynamic array
typedef struct {
	transaction_info* array;
	size_t used;
	size_t size;
} Array;

Array a;
double trans_time; 
time_t t; 

//new instance description of transaction
transaction_info create_struct(char* transaction_name, double transaction_response_time, time_t time, char* server_name, char* server_port) {

	transaction_info ti;

	ti.transaction_name = (char*)malloc(strlen(transaction_name) + 1);
	memset(ti.transaction_name, 0, strlen(transaction_name) + 1);

	strcpy(ti.transaction_name, transaction_name);

	ti.transaction_response_time = transaction_response_time;
	ti.time = time;

	ti.server_name = (char*)malloc(strlen(server_name) + 1);
	memset(ti.server_name, 0, strlen(server_name) + 1);

	strcpy(ti.server_name, server_name);

	ti.server_port = (char*)malloc(strlen(server_port) + 1);
	memset(ti.server_port, 0, strlen(server_port) + 1);

	strcpy(ti.server_port, server_port);
	return ti;
}

//destroy transaction object
void free_struct(transaction_info *ti) {

	free(ti->transaction_name);
	free(ti->server_name);
	free(ti->server_port);

	ti->transaction_name = NULL;
	ti->server_name = NULL;
	ti->server_port = NULL;
}

//init dynamic array
void init_array(Array *a, int init_size) {

	a->array = (transaction_info*)malloc(init_size * sizeof(transaction_info));
	memset(a->array,0,init_size * sizeof(transaction_info));

	a->used = 0;
	a->size = init_size;
}

//add element to dynamic array
void add_to_array(Array *a, transaction_info element) {

	if (a->used == a->size) {
		a->size *= 2;
		a->array = (transaction_info*)realloc(a->array, a->size * sizeof(transaction_info));
	}
	a->array[a->used++] = element;
}

//destroy dynamic array
void free_array(Array *a) {

	free(a->array);
	a->array = NULL;
	a->used = a->size = 0;
}

