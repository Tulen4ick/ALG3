#define _CRT_SECURE_NO_WARNINGS
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stack>

struct Node {
	int info;
	Node* left;
	Node* right;
};


Node* New(int data){
	Node* V;
	V = (Node*)malloc(sizeof(Node));
	V->info = data;
	V->left = V->right = NULL;
	return V;
};

Node* Add(Node* v, int data){
	if (v == NULL)// добавление нового
		return New(data);
	//поиск места для включения узла в дерево
	if (v->info > data) 
		v->left = Add(v->left, data);
	else 
		v->right = Add(v->right, data);
	return v;
};

void Print_t(Node* v){
	static int n = 0;//считаем уровень
	if (!v) return;// лист – окончание рекурсии
	n++;
	Print_t(v->left); // обход правого поддерева
	printf("(Level %d) %d\n", n, v->info); // вывод информации о вершине
	Print_t(v->right); // обход левого поддерева
	n--;
}

void Print_pre(Node* v) {
	if (v) {
		printf("%d ", v->info);
		Print_pre(v->left);
		Print_pre(v->right);
	}
}

void Print_in(Node* v) {
	if (v) {
		Print_in(v->left);
		printf("%d ", v->info);
		Print_in(v->right);
	}
}

void Print_post(Node* v) {
	if (v) {
		Print_post(v->left);
		Print_post(v->right);
		printf("%d ", v->info);
	}
}

int Height(Node* v) {
	if (!v) {
		return -1;
	}
	else {
		int lh, rh;
		lh = Height(v->left);
		rh = Height(v->right);
		if (lh > rh)
			return (lh+1);
		else
			return (rh+1);
	}
}

int List(Node* v) {
	int l;
	if (!v) {
		l = 0;
	}
	else {
		if ((!v->left) && (!v->right)) {
			l = 1;
		}
		else {
			l = List(v->left) + List(v->right);
		}
	}
	return l;
}

void Print_NotRec(Node* v) {
	std::stack <Node*> steck;
	steck.push(v);
	while (!steck.empty()) {
		Node* t = steck.top();
		steck.pop();
		printf("%d ", t->info);
		if (t->right) steck.push(t->right);
		if (t->left) steck.push(t->left);
	}
}


void DelTree(Node** v){
	if (*v)
	{
		DelTree(&((*v)->left));
		DelTree(&((*v)->right));
		free(*v);
	}
	(*v) = NULL;
}

int main() {
	setlocale(LC_ALL, "Rus");
	int n;
	int val;
	struct Node* root = NULL;
	FILE* fp;
	fp = fopen("Tree.txt", "r");
	int exit = 1;
	while (exit == 1) {
		printf("\nМЕНЮ\n\n");
		printf("1. Прочитать из файла множество (построить дерево)\n");
		printf("2. Прямой обход дерева (рекурсивный)\n");
		printf("3. Поперечный обход дерева (рекурсивный)\n");
		printf("4. Обратный обход дерева (рекурсивный)\n");
		printf("5. Высота дерева\n");
		printf("6. Количество листьев\n");
		printf("7. Прямой обход (нерекурсивный)\n");
		printf("8. Удалить дерево\n");
		printf("9. Выйти из программы\n");
		int n = 0;
		printf("Введите номер операции: \n");
		scanf("%d", &n);
		switch (n) {
		case 1:
			fscanf(fp, "%d", &n);
			for (int i = 0; i < n; ++i) {
				fscanf(fp, "%d", &val);
				printf("%d ", val);
				root = Add(root, val);
			}
			printf("\n");
			Print_t(root);
			break;
		case 2:
			printf("\n\nPre_order: ");
			Print_pre(root);
			break;
		case 3:
			printf("\n\nIn_order: ");
			Print_in(root);
			break;
		case 4:
			printf("\n\nPost_order: ");
			Print_post(root);
			break;
		case 5:
			printf("\nВысота дерева - %d\n", Height(root));
			break;
		case 6:
			printf("Количество листьев - %d\n", List(root));
			break;
		case 7:
			printf("\n\nPre_order (not recursion): ");
			Print_NotRec(root);
			break;
		case 8:
			DelTree(&root);
			break;
		case 9:
			exit = 0;
			break;
		default:
			printf("Неправильный ввод.\n");
		}
	}
	fclose(fp);
	return 0;
}
