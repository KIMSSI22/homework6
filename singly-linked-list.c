#include<stdio.h>
#include<stdlib.h>

typedef struct Node {  //노드를 구성하는 구조체
	int key;  //노드가 가질 수 있는 값
	struct Node* link;  //다음 노드를 가르키는 포인터
} listNode;

typedef struct Head {  //첫번째 노드를 가르키는 구조체
	struct Node* first;  //첫 노드를 가르키는 포인터
}headNode;

//함수 선언
headNode* initialize(headNode* h);
int freeList(headNode* h);

int insertFirst(headNode* h, int key);
int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);

int deleteFirst(headNode* h);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);

int main()
{
    printf("[----- [김민서] [2022040010] -----]");
	char command;
	int key;
	headNode* headnode=NULL;

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

        //입력 받은 command 값에 따른 케이스
		switch(command) {
		case 'z': case 'Z':
			headnode = initialize(headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


headNode* initialize(headNode* h) {  //연결리스트 초기화
	if(h != NULL)
		freeList(h);

	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;  //첫번째 포인터 초기화
	return temp;
}


int freeList(headNode* h){  //연결리스트 해제
	listNode* p = h->first;

	listNode* prev = NULL;  //구조체 해제
	while(p != NULL) {
		prev = p;
		p = p->link;
		free(prev);
	}
	free(h);
	return 0;
}


int insertNode(headNode* h, int key) {  //새로운 노드 삽입
	listNode* node = (listNode*)malloc(sizeof(listNode));  //키값을 가지는 동적 노드
	node->key = key;
	node->link = NULL;

	if (h->first == NULL)
	{
		h->first = node;
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = h->first;

	while(n != NULL) {  //정렬에 맞게 연결리스트에 삽입
		if(n->key >= key) {
			if(n == h->first) {
				h->first = node;
				node->link = n;
			} else { 
				node->link = n;
				trail->link = node;
			}
			return 0;
		}

		trail = n;
		n = n->link;
	}

	trail->link = node;
	return 0;
}


int insertLast(headNode* h, int key) {  //연결리스트 마지막에 삽입
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->link = NULL;

	if (h->first == NULL)
	{
		h->first = node;
		return 0;
	}

	listNode* n = h->first;
	while(n->link != NULL) {
		n = n->link;
	}
	n->link = node;
	return 0;
}

int insertFirst(headNode* h, int key) {  //연결리스트 처음에 삽입
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;

	node->link = h->first;
	h->first = node;

	return 0;
}

int deleteNode(headNode* h, int key) {  //노드 삭제
	if (h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = NULL;

	while(n != NULL) {  //key 값인 노드 삭제
		if(n->key == key) {
			if(n == h->first) {
				h->first = n->link;
			} else { 
				trail->link = n->link;
			}
			free(n);
			return 0;
		}

		trail = n;
		n = n->link;
	}

	printf("cannot find the node for key = %d\n", key);
	return 0;

}


int deleteLast(headNode* h) {  //마지막 노드 삭제
	if (h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = NULL;

	if(n->link == NULL) {  //연결리스트 마지막 노드 삭제
		h->first = NULL; 
		free(n);
		return 0;
	}

	while(n->link != NULL) {
		trail = n;
		n = n->link;
	}

	trail->link = NULL;
	free(n);

	return 0;
}

int deleteFirst(headNode* h) {  //첫번째 노드 삭제
	if (h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}
	listNode* n = h->first;

	h->first = n->link;
	free(n);

	return 0;
}

int invertList(headNode* h) {  //연결리스트 도치
	if(h->first == NULL) {
		printf("nothing to invert...\n");
		return 0;
	}
	listNode *n = h->first;
	listNode *trail = NULL;
	listNode *middle = NULL;

	while(n != NULL){
		trail = middle;
		middle = n;
		n = n->link;
		middle->link = trail;
	}

	h->first = middle;

	return 0;
}

void printList(headNode* h) {  //연결리스트 노드 출력
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;
		i++;
	}

	printf("  items = %d\n", i);
}