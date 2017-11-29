#include <unordered_map>
#include "sphinxudf.h"
#include "uniqueserial.h"

extern "C" {

int uniqueserial_ver()
{
    return SPH_UDF_VERSION;
}

int uniqueserial_init(SPH_UDF_INIT * init, SPH_UDF_ARGS * args, char * error_msg)
{
    if (args->arg_count != 1)
    {
      snprintf(error_msg, SPH_UDF_ERROR_LEN, "uniqueserial() takes 1 argument");
      return 1;
    }

    if (args->arg_types[0] != SPH_UDF_TYPE_UINT32)
    {
      snprintf(error_msg, SPH_UDF_ERROR_LEN, "uniqueserial() requires 1st argument to be uint");
      return 1;
    }

    // init map for uint key only!
    // attribute => counter
    init->func_data = new IntCount();

    return 0;
}

void uniqueserial_deinit(SPH_UDF_INIT * init)
{
    if (init->func_data)
    {
      IntCount *counters = static_cast<IntCount*>(init->func_data);
      delete counters;
    }
}

sphinx_uint64_t uniqueserial(SPH_UDF_INIT * init, SPH_UDF_ARGS * args, char * error_flag)
{
    sphinx_uint64_t res = *(sphinx_uint64_t*)args->arg_values[0];
    IntCount *counters = static_cast<IntCount*>(init->func_data);

    return ++(*counters)[res];
}

}
