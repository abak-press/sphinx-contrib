# sphinx-contrib

Хранилище UDF для sphinx.

### Установка (руками)

1) Компилируем на машине со сфинксом

```
make
```

2) Кладем '.so'-файлы в папку, указанную в качестве plugin_dir в конфиге searchd (по умолчанию /usr/lib/sphinx-2.2/lib/)

```
make install
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

