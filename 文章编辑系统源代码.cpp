#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<Windows.h>
#include <windows.h>
#include <wchar.h>
#include <locale.h>
#define N 80//��������
typedef struct line
{
	char str[N];      //�洢���е����� 
	int num;                 //������¼�к�
	struct line *prior;      //����ָ��ǰһ��
	struct line *next;       //����ָ����һ��
 }LINE;
 
LINE *start;          //ָ�����Ա�ĵ�һ��
LINE *last;           //ָ�����Ա�����һ��

int Choice(); 
int i,j; 
int ch=0;
void Title()
{
printf(" ____________________________________________________\n\n");
printf(" ****             ��ӭʹ�����±༭ϵͳ           ****  \n");
printf(" ****         ���ߣ� xx  ѧ�ţ�xxxxxxxxxxx      ****  \n");
printf(" ____________________________________________________  \n");
}
int menu()
{
	Title();
	printf("|                   �� ���ܲ˵� ��                  |\n");
	printf("|                     0.�˳�ϵͳ                    |\n");
	printf("|                     1.��������                    |\n");
	printf("|                     2.�������                    |\n");
	printf("|                     3.ɾ���ַ�                    |\n");
	printf("|                     4.����ַ�                    |\n");
	printf("|                     5.ͳ����Ŀ                    |\n");
	printf("|                     6.�洢����                    |\n");
	printf("|                     7.������                    |\n");
	printf("-----------------------------------------------------\n");
	printf("                   ������һ����<0-7>:");
}
void Output()
{
	LINE *p = start;
	while(p != last) //��p��ָ��Ĳ������һ��ʱ��ѭ����� 
	{
		printf("\n\n��%d��|%s",p->num,p->str); //����кź��ַ��� 
		p = p->next;//pָ����һ�� 
	}
	printf("\n\n��%d��|%s\n",last->num,last->str); //��p��ָ�����һ��ʱ��������һ������ 
	printf("\n");
}
void Input()
{	
	LINE *info,*temp;//��ָ�룬infoָ��ǰ�У�tempָ��info��ǰ���� 
	char ch;  //ch���ڼ�¼������ַ��� 
	int linenum,i;//�м�����,iΪ���ַ������±� 
	FILE *fp;  //�ļ�ָ�� 
	temp = NULL; //��temp�ÿ�                      
	start = (LINE*)malloc(sizeof(LINE)); //����һ�еĽ��ռ� 
	info = start;//ָ�����Ա�ĵ�һ��
	linenum = 1; //�кų�ֵΪ1 
	printf("��������������[ÿ�в��ó���80���ַ�(���ַ�'#'����)]:\n"); 
	while((ch = getchar())!='#') //�����յ��ַ���Ϊ'#' 
	{
		i = 0;//iΪ���ַ������±�,��ֵΪ0 
		info->str[i] = ch;//��ch�����յ����ַ��洢�������� 
		i++;//�±��1 
		while((ch = getchar())!='\n') //���ļ��ж���һ���ַ������Ա��� 
		{						      //һ�����ж����ַ���ѭ�����ٴ� 
			info->str[i] = ch;
			i++;
		}	
		info->str[i] ='\0';   
		info->num = linenum++;  //�кŴ洢�����Ա��к��һ 
		info->next = (LINE*)malloc(sizeof(LINE));//Ϊ��һ������һ�еĽ��ռ� 
		if (i>=80)  //0~79���ַ� 
		{
			printf("ÿ��������80���ַ���\n"); 
			printf("�������������£�\n");
			Sleep(5000);  //����5�� 
			system("cls");
			Title();
			Input();
		}
		info->prior = temp;
		temp = info;
		info = info->next;
 	} 
 	temp->next = NULL;
 	last = temp;
 	free(info);
 	start->prior = NULL;
}

/*int CountAll()
{
	int English=0;//Ӣ����ĸ��Ŀ 
	int Blank=0;//�ո���Ŀ 
	int Number=0;//������Ŀ
	int All=0;//����������Ŀ
	int i=0;
	LINE *p = start;
	//�������ԭ����
	printf("\n|>>>                ��ԭ���¡�               <<<|\n");
	while(p != last) //��p��ָ��Ĳ������һ��ʱ��ѭ����� 
	{
		printf("\n\n��%d��|%s",p->num,p->str); //����кź��ַ��� 
			while(i<strlen(p->str))
			{
				if(isdigit(p->str[i]))
				{
					Number++;
				}
				else if(p->str[i]==32) 
				{
					Blank++;
				}
				else if(isupper(p->str[i])||islower(p->str[i])) 
				{
					English++;
				}
				i++;
			}
		p = p->next;//pָ����һ�� 
	}
	printf("\n\n��%d��|%s\n",last->num,last->str); //��p��ָ�����һ��ʱ��������һ������ 
	while(i<strlen(last->str))
	{
		if(isdigit(last->str[i]))
		{
			Number++;
		}
		else if(last->str[i]==32) 
		{
			Blank++;
		}
		else if(isupper(last->str[i])||islower(last->str[i])) 
		{
			English++;
		}
			i++;
		}
	printf("\n"); 
	printf("�ı��е���ĸ����Ϊ��%d\n",English);
	printf("�ı��еĿո����Ϊ��%d\n",Blank);
	printf("�ı��е����ָ���Ϊ��%d\n",Number);
	printf("�ı�������������Ϊ��%d\n",All);
}
*/

int CountAll()
{
    int English = 0; // Ӣ����ĸ��Ŀ
    int Blank = 0;   // �ո���Ŀ
    int Number = 0;  // ������Ŀ
    int Chinese = 0; // ������Ŀ
    int All = 0;     // ����������Ŀ
    LINE *p = start;

    // ���ó�����GBK����
    setlocale(LC_CTYPE, "");

    // �������ԭ����
    printf("\n|>>>                ��ԭ���¡�               <<<|\n");
    while (p != NULL) // ��������ֱ������ĩβ
    {
        printf("\n\n��%d��|%s", p->num, p->str); // ����кź��ַ���
        int len = strlen(p->str);
        for (int j = 0; j < len; ) // ���ڵ�ǰ�е�ÿ���ַ�
        {
            int mblen_result = mblen(p->str + j, MB_CUR_MAX);
            if (mblen_result == -1) {
                // �Ƿ��ַ�������
                j++;
                continue;
            } else if (mblen_result == 1) {
                // ���ֽ��ַ�
                char ch = *(p->str + j);
                if (isdigit(ch))
                {
                    Number++;
                }
                else if (ch == ' ')
                {
                    Blank++;
                }
                else if (isupper(ch) || islower(ch))
                {
                    English++;
                }
                j++;
            } else {
                // ���ֽ��ַ�������Ϊ���֣�
                Chinese++;
                j += mblen_result;
            }
            All++; // ÿ���ַ�����������
        }
        p = p->next; // pָ����һ��
    }
    printf("\n"); 
    printf("�ı��е���ĸ����Ϊ��%d\n", English);
    printf("�ı��еĿո����Ϊ��%d\n", Blank);
    printf("�ı��е����ָ���Ϊ��%d\n", Number);
    printf("�ı��еĺ��ָ���Ϊ��%d\n", Chinese);
    printf("�ı�������������Ϊ��%d\n", All);
}
/*int CountString()
{
	Output();    //�������ԭ���� 
	char key_s[N]; //����һ���ַ��������ڴ��������ַ��� 
	getchar();
	printf("\n��������Ҫͳ����Ŀ���ַ�����");
	gets(key_s);   //����ַ��� 
	LINE *info;
	int i = 0, find_len, found = 0;//found��Ϊif�ж����� 
	char substring[N];
	info = start;
	int find_num = 0;             //ƥ�䵽�Ĵ��� 
	find_len = strlen(key_s);//���ַ���ʵ�ʳ��� 
	while (info)   //��ѯ
	{	
		i = 0;  //�м�ѭ��
		while (i <= (strlen(info->str) - find_len))  //���ڲ���ѭ��
		{	int k=0;
			for(int j=i;j<i+find_len;j++)   // ���ڵ��ַ����ӵ�һ����ʼ������find_len����substring 
			{	
				substring[k] = info->str[j]; 
				k++;
			}
			if (strcmp(substring,key_s) == 0)//�Ƚ������ַ����Ƿ���ͬ 
			{	
				find_num++;//��ͬ����ƥ�������1 
				printf("\n|��%d�γ����ڣ���%d�е�%d��\n",find_num,info->num,(i+1+1)/2);
				found = 1;
			}
				i++;
		}
		info = info->next;
	}
	if (found)  //���ҳɹ�
		printf("\n���ַ������ֵ��ܴ���Ϊ:%d\n",find_num);
	else   //���Ҳ��ɹ�
		printf("\n|������          �ı���û�и��ַ�����         ������|\n\n");
}*/

int CountString()
{
    Output();    // �������ԭ����
    char key_s[N]; // ����һ���ַ��������ڴ��������ַ���
    getchar(); // ����֮ǰgets���µĻ��з�
    printf("\n��������Ҫͳ����Ŀ���ַ�����");
    gets(key_s); // ����ַ���
    LINE *info;
    int i = 0, find_len, found = 0; // found��Ϊif�ж�����
    int find_num = 0; // ƥ�䵽�Ĵ���
    find_len = strlen(key_s); // ���ַ���ʵ�ʳ���
    info = start;
    while (info) { // ��ѯ
        char *pos = info->str; // ���ڲ�����ʼλ��
        while ((pos = strstr(pos, key_s)) != NULL) { // ʹ��strstr�����ַ���
            find_num++; // ��ͬ����ƥ�������1
            printf("\n|��%d�γ����ڣ���%d�е�%ld��\n", find_num, info->num, (long)(pos - info->str + 1));
            found = 1;
            pos++; // �ƶ����ҵ���λ��֮�󣬼�������
        }
        info = info->next;
    }
    if (found) { // ���ҳɹ�
        printf("\n���ַ������ֵ��ܴ���Ϊ:%d\n", find_num);
    } else { // ���Ҳ��ɹ�
        printf("\n|������          �ı���û�и��ַ�����         ������|\n\n");
    }
}
int Del_1()//ɾ��һ���ַ������� 
{
	printf("ԭ�ı�Ϊ��\n");
	Output();
	printf("\n������Ҫɾ���е��кţ�");
	int linenum; 
	scanf("%d",&linenum);
	LINE * info, *p;
	info = start;
	while ((info->num < linenum) && info)  //Ѱ��Ҫɾ������ 
		info = info->next;
	if (info == NULL)
		printf("\n������кŲ�����\n");
	else
	{
		p = info->next;     //ָ��Ҫɾ�����к���һ�� 
		if (start == info) //���ɾ�����ǵ�һ��
		{
			start = info->next;
			if (start)  //���ɾ���󣬲�Ϊ��
				start->prior = NULL;
			else  //ɾ����Ϊ��
				last = NULL;
		}
		else
		{
			info->prior->next = info->next;  //ָ���е���һ��ָ��ָ���е���һ��
			if (info != last) //����������һ��
				info->next->prior = info->prior;  //�޸�����һ�е�ָ��ͷ��ָ�� 
			else  //��������һ�У��޸�βָ��
				last = info->prior;
		}
		free(info);
		while (p) //��ɾ����֮����кż�һ 
		{
			p->num = p->num - 1;
			p = p->next;
		}
		printf("\n|������                ɾ���ɹ���             ������|\n");
		Sleep(1000);
		system("cls");
		Title();
		printf("\n|>>>                �� ɾ���ַ� ��               <<<|\n\n");
		printf("ɾ��������ı�Ϊ��\n"); 
		Output();
		printf("\n");
	}
}
int Del_2()//ɾ���ض��ַ������� 
{
	int linenum, position,lenth;  //�У��У�ɾ������ 
	printf("ԭ�ı�Ϊ��\n");
	Output();
	printf("������Ҫɾ�����������У��У�ɾ�������ֽڳ��ȣ��м��ÿո����\n");
	printf("ע�⣺����ռ�����ֽ�\n");
	scanf("%d %d %d",&linenum,&position,&lenth);
	position = (position*2)-1;
	getchar();
	LINE *info=start;
	char rest_str[N];
	if(linenum == 1)
	info = start;
	else
	for(int i=1;i<linenum;i++)     	 //��infoָ��ɾ������������ 
	info = info->next;      
	if (info == NULL)
		printf("\n����û���ַ���\n");
	else
	{
		if (strlen(info->str) <= (position + lenth))  //���е��ַ�����<=��ɾ�����к�+ɾ�����ȣ�ֱ���ڵ�ǰλ�ò���'\0'
			info->str[position] = '\0';
		else
		{	int i;
			for(i = position-1;info->str[i+lenth]!='\0';i++)
			info->str[i]=info->str[i+lenth];
			info->str[i]='\0';
		}
		printf("\n|������                ɾ���ɹ���             ������|\n");
		Sleep(1000);
		system("cls");
		Title();
		printf("\n|>>>                �� ɾ���ַ� ��               <<<|\n\n");
		printf("ɾ��������ı�Ϊ��\n"); 
		Output();
		printf("\n");
	}
}
int Add_1()//���һ���ı����� 
{
	printf("ԭ�ı�Ϊ��\n");
	Output();
	int linenum; 
	printf("\n���������λ�õ��кţ�");
	scanf("%d", &linenum);
	LINE * info, * q, * p;
	p = start;
	q = NULL;
	while (p && p->num != linenum)               
	{
		q = p;				//������ǰ��һ�� 
		p = p->next;	   //�����к���һ��
	}
	if (p == NULL && (q->num + 1) != linenum)	//ָ���в����ڣ����ܲ���
	{
		printf("\n������кŲ����ڣ�\n");
		Sleep(1000);
		system("cls");
		Title();
		printf("\n|>>>                �� ����ַ� ��               <<<|\n");
		Add_1();
	}
	else // ָ���д��ڣ����в���
	{
		info = (LINE *)malloc(sizeof(LINE));
		printf("������Ҫ������ַ���:");
		scanf("%s", info->str);
		info->num = linenum;
		if (linenum == 1)  			  //�����ڵ�һ��
		{
			info->next = p;
			p->prior = info;
			info->prior = NULL;
			start = info;
		}
		else if (q->num != linenum)  //���������һ��
		{
			q->next = info;
			info->next = p;
			info->prior = q;
		}
		else     //������������
		{
			q->next = info;
			info->next = p;
			p->prior = info;
			info->prior = q;
		}
		while (p)   //������ǲ��������һ�У������к�����кŶ���1
		{
			p->num = p->num + 1;
			p = p->next;
		}
		printf("\n|������                ��ӳɹ���             ������|\n");
		Sleep(1000);
		system("cls");
		Title();
		printf("\n|>>>                �� ����ַ� ��               <<<|\n\n");
		printf("��ӹ�����ı�Ϊ��\n"); 
		Output();
		printf("\n");
	}
}
int Add_2()//����ض��ִ����� 
{
	printf("ԭ�ı�Ϊ��\n");
	Output(); 
	char string[N]; //����һ���ַ������Ų�����ַ��� 
	int linenum;  //�к� 
	int position; //�к� 
	printf("\n���������λ�õ��кţ�");
	scanf("%d", &linenum);
	printf("���������λ�õ��кţ�");
	scanf("%d", &position);
	position = (position*2)-1; 
	printf("������Ҫ������ַ�����");
	scanf("%s", string);
	LINE * info;
	int len, i;
	int lenth;
	char rest_str[N],kongge[2] = { " " };
	info = start;
	while (info && info->num != linenum)   //��ѯҪ�������
	{
		info = info->next;
	}
	if (info == NULL)
		printf("\n������кŲ����ڣ�\n");
	else if (position < 0)
		printf("\n������кŲ����ڣ�\n");
	else    //����к��ж����ڣ�����в���
	{
		lenth = strlen(info->str);
		//strlen()�����Ǽ����������ڴ��е�ĳ��λ�ã��������ַ�����ͷ���м��ĳ��λ�á�������ĳ����ȷ�����ڴ�����
		//��ʼɨ�裬ֱ��������һ���ַ���������'\0'Ϊֹ��Ȼ�󷵻ؼ�����ֵ�����Ȳ�����'\0'�� 
		if (lenth < position)	//�����д��ڱ����ļ�����
		{
			len = position - lenth - 1;
			for (i = 0; i < len; i++)
			strcat(info->str, kongge);   //������Ĳ��ֲ���ո��
			strcat(info->str, string);    //�����ַ����е�δβ
		}
		else   //�������ڱ������ֵ��м�
		{
			strcpy(rest_str, &info->str[position - 1]); //strcpy()�ַ������ƺ�����ͬʱҲ�Ḵ���ַ��������� 
			strcpy(&info->str[position - 1], string);
			strcat(info->str, rest_str);  //strcat()��������һ���ַ���ĩβ�����µ��ַ�����rest_str�ַ���������info->str���ַ���ĩβ��info��ָ����ַ���Ҫ�����㹻�Ŀռ�������Ҫ�������ַ��� 
		}
		printf("\n|������                ��ӳɹ���             ������|\n");
		Sleep(1000);
		system("cls");
		Title();
		printf("\n|>>>                �� ����ַ� ��               <<<|\n\n");
		printf("��ӹ�����ı�Ϊ��\n"); 
		Output();
		printf("\n");
	}
} 
int Add()
{
	system("cls");
	Title();
	printf("|                 �� ����ַ��˵� ��                |\n");
	printf("|                    0.������һ��                   |\n");
	printf("|                   1.���һ���ַ�                  |\n");
	printf("|                   2.����ض��ַ�                  |\n");
	printf("|---------------------------------------------------|\n");
	printf("                  ������һ����<0-2> :");
	scanf("%d",&ch);
	switch (ch)
	{
		case 0: 
			system("cls");
			menu();
			Choice(); 
			break;
		case 1:
			Add_1(); 
			break;
		case 2:
			Add_2();
			break;
		default:
			printf("�����������������");
			Sleep(1000);
			system("cls");
			Add();
			break;
	}
}

void GetFilePath(char *filePath, int mode) {
    OPENFILENAME ofn;       // �ļ�ѡ��Ի���ṹ��
    char szFile[N] = "";    // ���ڱ����ļ�·��

    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL; // �����ھ��
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = "Text Files\0*.TXT\0All Files\0*.*\0"; // �ļ�������
    ofn.nFilterIndex = 1;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT;

    if (mode == 0) {
        // ���ļ�
        ofn.lpstrTitle = "ѡ��Ҫ�򿪵��ļ�";
        if (GetOpenFileName(&ofn)) {
            strcpy(filePath, szFile);
        } else {
            printf("\n|������        �û�ȡ�����ļ�ѡ��          ������|\n\n");
            exit(0);
        }
    } else {
        // �����ļ�
        ofn.lpstrTitle = "ѡ�񱣴��ļ���λ��";
        if (GetSaveFileName(&ofn)) {
            // ����Ƿ������׺
            if (!strchr(szFile, '.')) {
                strcat(szFile, ".txt"); // ���û�к�׺�����".txt"
            }
            strcpy(filePath, szFile);
        } else {
            printf("\n|������        �û�ȡ�����ļ�ѡ��          ������|\n\n");
            exit(0);
        }
    }
}


int Save() {
    char c;
    FILE *fp;
    LINE *info = start;
    int i = 0;
    char name[256];

    // ͨ���ļ���Դ������ѡ���ļ�·��
    GetFilePath(name, 1);

    while ((fp = fopen(name, "w")) == NULL) {
        printf("�ļ��޷�������������ѡ�񱣴�·����");
        GetFilePath(name, 1);
    }
    while (info) {
        fputs(info->str, fp);
        putc('\n', fp);
        info = info->next;
    }
    fclose(fp);
    printf("\n|������                ����ɹ���             ������|\n");

    return 0;
}

int Open() {
    char buf[N];   // ������
    FILE *fp;
    int i = 1;     // �кż���
    int len;
    char name[256];

    // ͨ���ļ���Դ������ѡ���ļ�·��
    GetFilePath(name, 0);

    if ((fp = fopen(name, "r")) == NULL) {
        printf("\n|������       ��Ǹ���ļ�������,�޷��򿪣�       ����|\n\n");
        exit(0);
    }

    // ���ԭ�����Ա�
    LINE *current = start, *temp;
    while (current) {
        temp = current->next;
        free(current);
        current = temp;
    }
    start = NULL;
    last = NULL;

    // ���������Ա���������
    LINE *prev = NULL;
    while (fgets(buf, N, fp) != NULL) {
        len = strlen(buf);

        // ȥ�����з�
        if (buf[len - 1] == '\n') {
            buf[len - 1] = '\0';
        }

        // �����½ڵ�
        LINE *newLine = (LINE *)malloc(sizeof(LINE));
        if (!newLine) {
            printf("\n|������              �ڴ治�㣡            ������|\n\n");
            fclose(fp);
            exit(0);
        }

        strcpy(newLine->str, buf); // �������ݵ��ڵ�
        newLine->num = i++;        // �����к�
        newLine->prior = prev;    // ǰ������
        newLine->next = NULL;     // Ĭ��û����һ���ڵ�

        if (prev) {
            prev->next = newLine; // ����ǰ�ڵ�� next ָ��
        } else {
            start = newLine; // ��һ���ڵ���Ϊ start
        }

        prev = newLine; // ����ǰ�ڵ�
    }

    last = prev; // ���һ���ڵ���Ϊ last
    fclose(fp);

    printf("\n|������          �ļ��ѳɹ����ص����Ա�        ������|\n");
    return 0;
}



/*
int Save()
{
	char  *p,c; 
	FILE *fp;
    LINE *info=start;
	int i=0; 
    char name[20];//����һ���ַ��������ڴ��������ļ�·���ַ� 
	printf("\n�����뱣���ַ(����: c:\\a.txt):");
	scanf("%s",name);
	while ((fp=fopen(name,"w"))==NULL)
	{
		printf("�ļ������ڣ������������ļ�����");
		scanf("%s",name);
	} 
		while(info)
	{   
		p=info->str; 
        while(*p)  
			putc(*p++, fp);
		putc('\n', fp); //��'\n'д��ָ����fp�У�����λ�ñ�ʶ����ǰ�ƶ� 
		info = info->next;
	}
    fclose(fp);
	printf("\n|������                ����ɹ���             ������|\n");	
	
	LINE *temp;
	temp=NULL;
	int inct;
	if ((fp = fopen(name, "r")) == NULL)
	{
		printf("\t�ļ��򲻿���\n");
		exit(0);
	}
	
	start = (LINE*)malloc(sizeof(LINE)); //��̬����һ�еĽ��ռ�
	info = start;
	inct = 1;
	while ((c = fgetc(fp)) != EOF)
	{
		i = 0;
		info->str[i] = c;
		i++;
		while ((c = fgetc(fp)) != '\n')  //���ļ��ж�ȡһ���ַ������Ա��У��ļ���ÿһ����\nΪ������
		{
			info->str[i] = c;
			i++;
		}
		info->str[i] = '\0';  //���Ա���ÿ��ĩβ�Ľ�����־
		info->num = inct++;  //�кźͼ���������1
		info->next = (LINE*)malloc(sizeof(LINE)); //Ϊ��һ�ж�̬����һ�еĽ��ռ�
		if (!info->next)
		{
			printf("\n|������              �ڴ��Ѿ����꣡           ������|\n\n");  
			exit(0);
		}
		info->prior = temp;
		temp = info;
		info = info->next;
	}
	temp->next = NULL;
	last = temp;
	free(info);  //�ͷŽڵ�ռ� 
	start->prior = NULL;
	fclose(fp);
	//�������Ա�ɹ� 
} 

int Open()
{
	char buf[N];//������
	FILE *fp;
	int i=1;  //��¼�к� 
	int len;
	char name[50]; //����һ���ַ��������ڴ��������ļ�·���ַ� 
	printf("\n������Ҫ���ļ��ĵ�ַ(����: c:\\a.txt):");
	scanf("%s",name);
	if ((fp = fopen(name, "r")) == NULL)  
	{
		printf("\n|������       ��Ǹ���ļ�������,�޷��򿪣�       ����|\n\n");
		exit(0); //ϵͳ�����˳� 
	}
	while(fgets(buf,N,fp)!=NULL)
	{
		len=strlen(buf); 
		//strlen()�����Ǽ����������ڴ��е�ĳ��λ�ã��������ַ�����ͷ���м��ĳ��λ�á�������ĳ����ȷ�����ڴ�����
		//��ʼɨ�裬ֱ��������һ���ַ���������'\0'Ϊֹ��Ȼ�󷵻ؼ�����ֵ�����Ȳ�����'\0'�� 
		buf[len-1]='\0';
		printf("\n��%d��|%s",i,buf); //�����ض���ʽ����������� 
		i++;   //�кż�1 
	}
	printf("\n");
	fclose(fp); //�ر��ļ� 
	return 0;
}*/
int Delete()
{
	system("cls");
	Title();
	printf("|                 �� ɾ���ַ��˵� ��                |\n");
	printf("|                    0.������һ��                   |\n");
	printf("|                   1.ɾ��һ���ַ�                  |\n");
	printf("|                   2.ɾ���ض��ַ�                  |\n");
	printf("|---------------------------------------------------|\n");
	printf("                  ������һ����<0-2> :");
	scanf("%d",&ch);
	switch (ch)
	{
		case 0: 
			system("cls");
			menu();
			Choice(); 
			break;
		case 1:
			Del_1(); 
			break;
		case 2:
			Del_2();
			break;
		default:
			printf("�����������������");
			Sleep(1000);
			system("cls");
			Delete();
			break;
	}
} 
int Count()
{
	system("cls");
	Title();
	printf("|                 �� ͳ���ַ��˵� ��                |\n");
	printf("|                    0.������һ��                   |\n");
	printf("|                   1.�����ַ���Ŀ                  |\n");
	printf("|                   2.�ض��ַ���Ŀ                  |\n");
	printf("|---------------------------------------------------|\n");
	printf("                  ������һ����<0-2> :");
	scanf("%d",&ch);
	switch (ch)
	{
		case 0: 
			system("cls");
			menu();
			Choice(); 
			break;
		case 1:
			CountAll(); 
			break;
		case 2:
			CountString();
			break;
		default:
			printf("�����������������\n");
			Sleep(1000);
			system("cls");
			Count();
			break;
	}
} 
int Choice()
{
	scanf("%d",&ch);
	//�ж�������ַ���ʲô�ַ� 
	switch (ch)
	{
		case 0: 
			printf("\n|������                �˳��ɹ���             ������|\n\n");
			exit(0); 
			break;
		case 1:
			system("cls");
			Title();
			printf("\n|>>>                �� �������� ��               <<<|\n\n");
			getchar();
			Input(); 
			break;
		case 2:
			system("cls");
			Title();
			printf("\n|>>>                �� ������� ��               <<<|\n\n");
			Output();
			break;
		case 3:
			system("cls");
			Title();
			printf("\n|>>>                �� ɾ���ַ� ��               <<<|\n\n");
			Delete();
			break;
		case 4:
			system("cls");
			Title();
			printf("\n|>>>                �� ����ַ� ��               <<<|\n\n");
			Add(); 
			break;
		case 5: 
			Count();
			break;
		case 6: 
			system("cls");
			Title();
			printf("\n|>>>                �� �洢���� ��               <<<|\n\n");   
			Save();   
			break;
		case 7: 
			system("cls");
			Title();
			printf("\n|>>>                �� ������ ��               <<<|\n\n");
			Open();
			break;
		default:
			printf("ѡ�������������\n");
			Sleep(1000);
			system("cls");
			menu();
			Choice();
			break;
	}
}

int main()
{
	while(1)
	{
		menu();
		Choice();
		system("pause"); 
		system("cls");//ͷ�ļ�Ϊ #include<stdlib.h>��������
	}	
}
