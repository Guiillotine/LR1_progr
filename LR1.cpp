/*N12.
Дан символьный файл (создать его).
Найти самое длинное слово среди слов, вторая буква которых есть 'а'.
Если таких слов с наибольшей длинной несколько, то найти все. Если таких
слов нет, то сообщить об этом.*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <locale.h>
#include <iostream>
#define N 30
int vvod(char fn[]); //Функция для внесения данных в файл
int vivod(char fn[]);//Функция для вывода данных из файла на экран
int poisk(char fn[]);//Функция для поиска самого длинного слова среди слов, вторая буква которых есть 'а'

int main()
{
	setlocale(LC_ALL, "Rus");
	FILE* file;
	do
	{
		system("cls");
		char fn[N]{}; //Имя файла
		do
		{
			printf(" Все вводы в программе делаются на английском языке\n");
			do {
				printf("\n Введите название файла для записи данных: ");
				gets_s(fn);
			} while (fn[0] == NULL); //Защита от пустого ввода
			//Защита от случайной потери данных
			file = fopen(fn, "r");
			if (file != NULL) printf("\n Файл с таким именем уже существует.\n\n Нажмите пробел, чтобы перезаписать файл или любую другую клавишу,\n чтобы ввести другое название\n");
			else break;
		} while (_getch() != ' ');
		vvod(fn);
		printf("\n Вы ввели: \n\n");
		vivod(fn);
		printf("\n Все слова с наибольшей длиной, вторая буква в которых - \"а\":\n\n");
		poisk(fn);
		printf("\n\n Нажмите любую клавишу для заполнения нового файла или Esc для окончания работы\n программы\n");
	} while (_getch() != 27);
}

//Внесение данных в файл
int vvod(char fn[])
{
	FILE* file;
	int n; //Длина слова
	file = fopen(fn, "w");
	if (file == NULL)
	{
		printf("\n Ошибка! Невозможно окрыть файл для записи\n");
		return 1;
	}

	do
	{
		char word[50]; //Массив для слова
		do {
			printf("\n Введите слово: ");
			gets_s(word);
		} while (word[0] == NULL); //Защита от пустого ввода

		n = strlen(word);
		strcat(word, "\n"); //Добавление ENTER в конец строки 
		for (int i = 0; i <= n; i++)
			putc(word[i], file); //Посимвольное считывание информации из массива в файл
		printf("\n Нажмите любую клавишу для ввода нового слова или Esc для окончания ввода \n");
	} while (_getch() != 27);
	putc('\n', file); //В конец файла помещаем ENTER
	fclose(file);

	return 0;
}

//Вывод данных из файла на экран
int vivod(char fn[])
{
	FILE* file;
	char word[50]{}; //Массив для слова
	file = fopen(fn, "r");
	if (file == NULL)
	{
		printf("\n Ошибка! Невозможно окрыть файл для чтения\n");
		return 1;
	}
	do
	{
		fgets(word, 49, file); //Помещение слова из файла в массив
		printf(" ");
		puts(word);
	} while ((strcmp(word, "\n")) != 0); //Завершить цикл, когда он дойдёт до последнего ENTER
	fclose(file);
	return 0;
}

//Поиск самого КОРОТКОГО слова среди слов, вторая буква которых есть 'а'
int poisk(char fn[])
{
	FILE* file;
	char word[50]{}; //Массив для слова
	int n, min = 100, f = 0; //n - длина слова f - флажок для случая "слов не найдено" 
	file = fopen(fn, "r");
	if (file == NULL)
	{
		printf("\n Ошибка! Невозможно окрыть файл для чтения\n");
		return 1;
	}
	do
	{
		fgets(word, 49, file);
		if (word[1] == 'a') //Условие: вторая буква - а
		{
			f = 1; //Найдено хотя бы одно слово
			n = strlen(word);
			if (n < min) min = n; //Наименьшая длина
			n = 0;
		}
	} while ((strcmp(word, "\n")) != 0);
	if (!f) { printf(" Слов не найдено\n"); return 2; }

	rewind(file);
	do
	{
		fgets(word, 49, file);
		if (word[1] == 'a')
		{
			n = strlen(word);
			if (n == min) { printf(" "); puts(word); } //Печать всех слов, соответствующих условиям
			n = 0;
		}
	} while ((strcmp(word, "\n")) != 0);
	fclose(file);
	return 0;
}