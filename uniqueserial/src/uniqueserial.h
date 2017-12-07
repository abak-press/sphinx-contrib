typedef std::unordered_map<sphinx_int64_t,sphinx_int64_t> IntCount;

#ifdef __cplusplus
extern "C" {
#endif

int uniqueserial_ver();

int uniqueserial_init(SPH_UDF_INIT * init, SPH_UDF_ARGS * args, char * error_flag);

void uniqueserial_deinit(SPH_UDF_INIT * init);

sphinx_uint64_t uniqueserial(SPH_UDF_INIT * init, SPH_UDF_ARGS * args, char * error_flag);

#ifdef __cplusplus
}
#endif
