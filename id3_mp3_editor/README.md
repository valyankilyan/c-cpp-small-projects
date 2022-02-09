# Редактор текстовой метаинформации MP3 файлов
Проект исполнен как лабораторная работа к курсу программирования на языке C <br>

## Сборка
    make
## Использование
    $ ./id3_editor 
    id3-editor> help
    It's a program that helps you edit tags in mp3 file
    there are some commands that will help you with it:

    exit - Exit from subshell and from program as well
    open - Open mp3 file. You should write > open <filename>
    show - Show all tags we found
    add - Add tag to the file > add <tag_name> <tag_data>
    delete - Delete tag > delete <tag_name>
    save - Save file > save || > save <new_filename>
    close - Close file with current tags
    help - Get help..
    id3-editor> 

## Текст лабораторной работы
Реализовать редактор текстовой метаинформации mp3 файла. <br>
В качестве стандарта метаинформации принимаем ID3v2. <br>
Редактор представлять из себя консольную программу
принимающую в качестве аргументов имя файла, а также одну из выбранных команд:
1. ```show``` - отображение всей метаинформации в виде таблицы
2. ```set=prop_name value=prop_value``` - выставляет значение
определенного поля метаинформации с именем prop_name в
значение prop_value
3. ```get=prop_name``` - вывести определенное поле
метаинформации с именем prop_name <br>

### Примечание.
При выполнения данной работы разрешается
использовать только стандартную библиотеку языка С.
Исключением может являться процесс разбора аргументов
командной строки.