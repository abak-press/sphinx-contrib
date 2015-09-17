# sphinx-contrib

Хранилище UDF для sphinx.

### Установка (руками)

1) Компилируем на машине со сфинксом (sphinxudf.h должен лежать рядом с исходником udf)

```
storage> gcc -fPIC -shared -o ./random_float.so ./random_float.c
```

2) Кладем '.so'-файл в папку, указанную в качестве plugin_dir в конфиге searchd

```
storage> cp ./random_float.so /home/index/sphinx/slave/plugins
```

Рестартуем searchd.

3) Создаем UDF

```
mysql> CREATE FUNCTION random_float RETURNS float SONAME 'random_float.so';
```

### Автоматизация создания UDF при перезапуске searchd.

В конфиге searchd добавляем секцию

```
sphinxql_state = /home/index/sphinx/slave/conf/state.sql
```

### Литература

1. http://sphinxsearch.com/docs/current/sphinx-udfs.html
2. http://sphinxsearch.com/docs/current/conf-sphinxql-state.html

