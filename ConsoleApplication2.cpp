#include<stdio.h>
#include<stdlib.h>
#include "stdafx.h"
#include "malloc.h"
#include "windows.h"
#include "string.h"



#define MAX 30
typedef struct node
{
	char s[30];
	struct node* next;
	int count;
}node, *List;
int FindInDict(node **dict, char *s);
void InsertToDict(node **dict, char *s);
void FindTop(node *dict, List top[], int n);
int main()
{
	FILE *fp;
	char ch;
	char word[30];
	int len = 0;
	int c_ch = 0;
	int c_line = 0;
	int c_word = 0;
	node *dict = (node *)calloc(26, sizeof(node));       //���嶯̬���飬��ŵ�����Ӧ���ʵ�ͷ���
	node *top[10] = { 0 };         //�������ǰʮ�ĵ��ʵ�ָ�루�ڴ��ַ��
	int i = 0;
	if ((fopen_s(&fp,"F:\\�������\\ConsoleApplication2\\count.txt","r")) !=0)
	{
		printf_s("���ܴ��ļ�\n");
		getchar();
		exit(1);
	}
	fseek(fp, 0, SEEK_SET);
	while ((ch = fgetc(fp)) != EOF)
		//ע���������(ch=fgetc(fp)),��Ϊ!=���ȼ��ߣ�����!=���Ϊ1������()���ch=1
	{
		c_ch++;
		len = 0;
		while (ch >= 'a'&&ch <= 'z')
		{
			word[len++] = ch;
			ch = fgetc(fp);
			c_ch++;
		}

		if (len != 0)
		{
			word[len] = '\0';
			c_word++;
			if (FindInDict(&dict, word) == 0)

				InsertToDict(&dict, word);

		}
		if (ch == '\n')
			c_line++;
	}

	printf_s("the number of character is:%d\n", c_ch);
	printf_s("the number of line is:%d\n", c_line + 1);
	printf_s("the number of word is:%d\n", c_word);
	FindTop(dict, top, 10);
	for (i = 0; i != 10; ++i)
	{
		if (top[i] != 0)
			printf_s("the top %2d word is %-10s, %d\n", i + 1, top[i]->s, top[i]->count);

	}

	fclose(fp);
	return 0;
}
int FindInDict(node **dict, char *s)
{
	int index = (s[0] - 'a');
	node *p = ((*dict) + index)->next;
	while (p != NULL)
	{
		if (strcmp((p->s), s)<0)
			p = p->next;
		else
		{
			if (strcmp(p->s, s)>0)
				return 0;
			else
			{
				p->count++;
				return 1;
			}
		}
	}
	return 0;
}
void InsertToDict(List *dict, char *s)
{
	int index = (s[0] - 'a');
	node *p = (*dict + index)->next;
	node *word = (node *)malloc(sizeof(node));
	word->count = 1;
	strcpy_s(word->s, s);
	word->next = NULL;
	if (NULL == p)
	{
		(*dict + index)->next = word;
	}
	else
	{
		if (strcmp(s, p->s)<0)
		{
			word->next = p;
			(*dict + index)->next = word;
			return;
		}
		while (p->next != NULL)
		{
			if (strcmp(s, p->next->s)<0)
			{
				word->next = p->next;
				p->next = word;
				return;
			}
			else
				p = p->next;
		}
		if (p->next != word)
			p->next = word;
	}
}
int cmp(const void *a, const void *b)          //List��������������Ԫ�صĵ�ַ
{
	List *i = (List*)a; 
		List *j = (List*)b;
	return ((*j)->count - (*i)->count);
}
void FindTop(List dict, List top[], int n)
{
	node *p = dict;
	node *q = p->next;
	node *tmp[100000] = { 0 };
	int i, index = 0;
	while (p<dict + 26)
	{
		while (q != NULL)
		{
			tmp[index++] = q;
			q = q->next;
		}
		p++;
		q = p->next;
	}
	qsort(tmp, index, sizeof(List), cmp);//������
	for (i = 0; i<n; ++i)
		top[i] = tmp[i];
}

