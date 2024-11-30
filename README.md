# Утилита для поиска файлов дубликатов.
Программное обеспечение для поиска файлов с одинаковым содержимым.

# Зависимости (библиотеки, используемые при реализации).
Для корректной работы программы необходимо установить библиотеку Boost.

# Перед работой с утилитой.
Склонировать репозиторий и выполнить сборку.

```git clone https://github.com/Vazcuus/c-_lab7```

Сборка осуществляется через CMake.

# Работа с утилитой.
Перейти в папку build с исполняемым файлом bayan.exe

Утилита принимает на вход пять обязательных параметров (аргументов).

Пример: ./bayan "path/to/scan/directory" "path/to/ignore/directory" "1" "5" "TEXT"

argv[1] - "path/to/scan/directory" - путь к директории, в которой будет происходить сканирование (можно указывать несколько, через запятую в одну строку, "path/to/scan/directory,path/to/scan/directory2")

argv[2] - "path/to/ignore/directory" - путь к директории, которая будет игнорироваться (можно указывать несколько, через запятую в одну строку, "path/to/ignore/directory,path/to/ignore/directory2")

argv[3] - "1" - параметр сканирования, сканировать только данную директорию или все директории, включая вложенные ("1"- все, "0"- только данная)

argv[4] - "5" - длина блока чтения данных из файла

argv[5] - "TEXT" - маска имен файлов (без учета регистра)

