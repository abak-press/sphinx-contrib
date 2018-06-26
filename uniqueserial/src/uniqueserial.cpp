#include "uniqueserial.h"

/**
 * Расчет коэфф. в зависимости от входного параметра, в частном случае
 * параметром может выступать коэфициент пакета поделенный на 10
 *
 * Для данного c (company_id например) помечаем всподряд идущие строки p раз одним и тем же коэфициентом
 * если превысили порог p коэфициент увеличиваем на 1 и снова помечаем всподряд идущие строки выборки
 * одним и тем же коэфициентом.
 *
 * Тем самым "вытягиваем" по p строк для каждого c вверх чередуя их по группам;
 * Пример, имеется 3 компании:
 * company1 - платиновый пакет, имеет 6 товаров
 * company2 - платиновый пакет, имеет 3 товара
 * company3 - золотой пакет, 4 товара
 * в данном примере у платинового пакета коеф. 3, у золотого - 2
 *
 * После сортировки по unqueserial получим такой листинг товаров:
 *
 * товар                     p расчитанная позиция
 * company1_product_platinum 3 1
 * company1_product_platinum 3 1
 * company1_product_platinum 3 1
 * company2_product_platinum 3 1
 * company2_product_platinum 3 1
 * company2_product_platinum 3 1
 *
 * company3_product_gold     2 1
 * company3_product_gold     2 1
 *
 * company1_product_platinum 3 2
 * company1_product_platinum 3 2
 * company1_product_platinum 3 2
 *
 * company3_product_gold     2 2
 * company3_product_gold     2 2
 *
 * , где p - постоянный коэфициент, зависящий от пакета, передается аргументом через SELECT в calculate_factor
 *
 * Функция использует блокировку из-за того, что сфинкс может распараллелить один запрос на несколько потоков:
 * См. https://github.com/manticoresoftware/manticoresearch/issues/87 и документацию.
 *
 **/
sphinx_uint64_t Factor::calculate_factor(unsigned int p) {
  if (counter >= p) {
    counter = 1;
    return factor++;
  } else {
    counter++;
    return factor;
  }
}

extern "C" {

int uniqueserial_ver() {
    return SPH_UDF_VERSION;
}

int uniqueserial_init(SPH_UDF_INIT* init, SPH_UDF_ARGS* args, char* error_msg) {
    if (args->arg_count != 2) {
      snprintf(error_msg, SPH_UDF_ERROR_LEN, "uniqueserial() takes 2 arguments");
      return 1;
    }

    if (args->arg_types[0] != SPH_UDF_TYPE_UINT32) {
      snprintf(error_msg, SPH_UDF_ERROR_LEN, "uniqueserial() requires 1st argument to be uint");
      return 1;
    }

    if (args->arg_types[1] != SPH_UDF_TYPE_UINT32) {
      snprintf(error_msg, SPH_UDF_ERROR_LEN, "uniqueserial() requires 2nd argument to be uint");
      return 1;
    }

    init->func_data = new Storage;

    return 0;
}

void uniqueserial_deinit(SPH_UDF_INIT* init) {
    Storage* storage = static_cast<Storage*>(init->func_data);
    delete storage;
}

sphinx_uint64_t uniqueserial(SPH_UDF_INIT* init, SPH_UDF_ARGS* args, char* error_flag) {
    // e.g. company
    unsigned int c = *(unsigned int*)(args->arg_values[0]);
    // e.g. packet
    unsigned int p = *(unsigned int*)(args->arg_values[1]);

    Storage* storage = static_cast<Storage*>(init->func_data);

    std::lock_guard<std::mutex> guard(storage->storage_mutex);

    if (!storage->counters) {
      storage->counters = std::make_shared<Counters>();
    }

    if (!(*storage->counters)[c]) {
      (*storage->counters)[c] = std::make_shared<Factor>();
    }

    return (*storage->counters)[c]->calculate_factor(p);
}

}
