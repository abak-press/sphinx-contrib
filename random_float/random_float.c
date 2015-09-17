#include "sphinxudf.h"
#include <stdio.h>
#include <stdlib.h>

int random_float_ver () {
    return SPH_UDF_VERSION;
}

int random_float_init ( SPH_UDF_INIT * init, SPH_UDF_ARGS * args, char * error_message ) {
    if ( args->arg_count > 0 ) {
        snprintf ( error_message, SPH_UDF_ERROR_LEN, "random_float() takes no one argument" );
        return 1;
    }
    return 0;
}

void random_float_deinit ( SPH_UDF_INIT * init ) {
}

double random_float ( SPH_UDF_INIT * init, SPH_UDF_ARGS * args, char * error_flag ) {
   return (double)rand() / (double)RAND_MAX;
}
