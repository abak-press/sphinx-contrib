#include <memory>
#include <mutex>
#include <unordered_map>
#include "sphinxudf.h"

#ifndef uniqueserialh
#define uniqueserialh

// расчитываемый коэфициент для сортировки
struct Factor {
  unsigned int counter;
  sphinx_uint64_t factor;

  Factor() : counter(1), factor(1) {}

  sphinx_uint64_t calculate_factor(unsigned int p);
};

// Счетчики
typedef std::unordered_map<unsigned int, std::shared_ptr<Factor>> Counters;

struct Storage {
  std::mutex storage_mutex;
  std::shared_ptr<Counters> counters;
};

#ifdef __cplusplus
extern "C" {
#endif

// Далее стандартные объявления UDF

int uniqueserial_ver();

int uniqueserial_init(SPH_UDF_INIT* init, SPH_UDF_ARGS* args, char* error_flag);

void uniqueserial_deinit(SPH_UDF_INIT* init);

sphinx_uint64_t uniqueserial(SPH_UDF_INIT* init, SPH_UDF_ARGS* args, char* error_flag);

#ifdef __cplusplus
}
#endif
#endif
