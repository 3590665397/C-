#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<Windows.h>
#include <windows.h>
#include <wchar.h>
#include <locale.h>
#define N 80//文章行数
typedef struct line
{
	char str[N];      //存储该行的内容 
	int num;                 //用来记录行号
	struct line *prior;      //用来指向前一行
	struct line *next;       //用来指向下一行
 }LINE;
 
LINE *start;          //指向线性表的第一行
LINE *last;           //指向线性表的最后一行

int Choice(); 
int i,j; 
int ch=0;
void Title()
{
printf(" ____________________________________________________\n\n");
printf(" ****             欢迎使用文章编辑系统           ****  \n");
printf(" ****         作者： xx  学号：xxxxxxxxxxx      ****  \n");
printf(" ____________________________________________________  \n");
}
int menu()
{
	Title();
	printf("|                   【 功能菜单 】                  |\n");
	printf("|                     0.退出系统                    |\n");
	printf("|                     1.输入文章                    |\n");
	printf("|                     2.输出文章                    |\n");
	printf("|                     3.删除字符                    |\n");
	printf("|                     4.添加字符                    |\n");
	printf("|                     5.统计数目                    |\n");
	printf("|                     6.存储文章                    |\n");
	printf("|                     7.打开文章                    |\n");
	printf("-----------------------------------------------------\n");
	printf("                   请输入一个数<0-7>:");
}
void Output()
{
	LINE *p = start;
	while(p != last) //当p所指向的不是最后一行时，循环输出 
	{
		printf("\n\n第%d行|%s",p->num,p->str); //输出行号和字符串 
		p = p->next;//p指向下一行 
	}
	printf("\n\n第%d行|%s\n",last->num,last->str); //当p所指向最后一行时，输出最后一行内容 
	printf("\n");
}
void Input()
{	
	LINE *info,*temp;//行指针，info指向当前行，temp指向info的前驱行 
	char ch;  //ch用于记录输入的字符串 
	int linenum,i;//行计数器,i为行字符数组下标 
	FILE *fp;  //文件指针 
	temp = NULL; //将temp置空                      
	start = (LINE*)malloc(sizeof(LINE)); //生成一行的结点空间 
	info = start;//指向线性表的第一行
	linenum = 1; //行号初值为1 
	printf("请输入文章内容[每行不得超过80个字符(以字符'#'结束)]:\n"); 
	while((ch = getchar())!='#') //当接收到字符不为'#' 
	{
		i = 0;//i为行字符数组下标,初值为0 
		info->str[i] = ch;//将ch即接收到的字符存储到该行中 
		i++;//下标加1 
		while((ch = getchar())!='\n') //从文件中读到一行字符到线性表中 
		{						      //一行中有多少字符就循环多少次 
			info->str[i] = ch;
			i++;
		}	
		info->str[i] ='\0';   
		info->num = linenum++;  //行号存储在线性表中后加一 
		info->next = (LINE*)malloc(sizeof(LINE));//为下一行生成一行的结点空间 
		if (i>=80)  //0~79个字符 
		{
			printf("每行最多输出80个字符！\n"); 
			printf("请重新输入文章！\n");
			Sleep(5000);  //休眠5秒 
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
	int English=0;//英文字母数目 
	int Blank=0;//空格数目 
	int Number=0;//数字数目
	int All=0;//所有文字数目
	int i=0;
	LINE *p = start;
	//首先输出原文章
	printf("\n|>>>                【原文章】               <<<|\n");
	while(p != last) //当p所指向的不是最后一行时，循环输出 
	{
		printf("\n\n第%d行|%s",p->num,p->str); //输出行号和字符串 
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
		p = p->next;//p指向下一行 
	}
	printf("\n\n第%d行|%s\n",last->num,last->str); //当p所指向最后一行时，输出最后一行内容 
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
	printf("文本中的字母个数为：%d\n",English);
	printf("文本中的空格个数为：%d\n",Blank);
	printf("文本中的数字个数为：%d\n",Number);
	printf("文本中所有文字数为：%d\n",All);
}
*/

int CountAll()
{
    int English = 0; // 英文字母数目
    int Blank = 0;   // 空格数目
    int Number = 0;  // 数字数目
    int Chinese = 0; // 汉字数目
    int All = 0;     // 所有文字数目
    LINE *p = start;

    // 设置程序处理GBK编码
    setlocale(LC_CTYPE, "");

    // 首先输出原文章
    printf("\n|>>>                【原文章】               <<<|\n");
    while (p != NULL) // 遍历链表直到到达末尾
    {
        printf("\n\n第%d行|%s", p->num, p->str); // 输出行号和字符串
        int len = strlen(p->str);
        for (int j = 0; j < len; ) // 对于当前行的每个字符
        {
            int mblen_result = mblen(p->str + j, MB_CUR_MAX);
            if (mblen_result == -1) {
                // 非法字符，跳过
                j++;
                continue;
            } else if (mblen_result == 1) {
                // 单字节字符
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
                // 多字节字符（假设为汉字）
                Chinese++;
                j += mblen_result;
            }
            All++; // 每个字符都增加总数
        }
        p = p->next; // p指向下一行
    }
    printf("\n"); 
    printf("文本中的字母个数为：%d\n", English);
    printf("文本中的空格个数为：%d\n", Blank);
    printf("文本中的数字个数为：%d\n", Number);
    printf("文本中的汉字个数为：%d\n", Chinese);
    printf("文本中所有文字数为：%d\n", All);
}
/*int CountString()
{
	Output();    //首先输出原文章 
	char key_s[N]; //定义一个字符数组用于存放输入的字符串 
	getchar();
	printf("\n请输入需要统计数目的字符串：");
	gets(key_s);   //获得字符串 
	LINE *info;
	int i = 0, find_len, found = 0;//found做为if判断条件 
	char substring[N];
	info = start;
	int find_num = 0;             //匹配到的次数 
	find_len = strlen(key_s);//求字符串实际长度 
	while (info)   //查询
	{	
		i = 0;  //行间循环
		while (i <= (strlen(info->str) - find_len))  //行内查找循环
		{	int k=0;
			for(int j=i;j<i+find_len;j++)   // 行内的字符串从第一个开始按定长find_len赋给substring 
			{	
				substring[k] = info->str[j]; 
				k++;
			}
			if (strcmp(substring,key_s) == 0)//比较两个字符串是否相同 
			{	
				find_num++;//相同，将匹配次数加1 
				printf("\n|第%d次出现在：第%d行第%d列\n",find_num,info->num,(i+1+1)/2);
				found = 1;
			}
				i++;
		}
		info = info->next;
	}
	if (found)  //查找成功
		printf("\n该字符串出现的总次数为:%d\n",find_num);
	else   //查找不成功
		printf("\n|》》》          文本中没有该字符串！         《《《|\n\n");
}*/

int CountString()
{
    Output();    // 首先输出原文章
    char key_s[N]; // 定义一个字符数组用于存放输入的字符串
    getchar(); // 吸收之前gets留下的换行符
    printf("\n请输入需要统计数目的字符串：");
    gets(key_s); // 获得字符串
    LINE *info;
    int i = 0, find_len, found = 0; // found做为if判断条件
    int find_num = 0; // 匹配到的次数
    find_len = strlen(key_s); // 求字符串实际长度
    info = start;
    while (info) { // 查询
        char *pos = info->str; // 行内查找起始位置
        while ((pos = strstr(pos, key_s)) != NULL) { // 使用strstr查找字符串
            find_num++; // 相同，将匹配次数加1
            printf("\n|第%d次出现在：第%d行第%ld列\n", find_num, info->num, (long)(pos - info->str + 1));
            found = 1;
            pos++; // 移动到找到的位置之后，继续查找
        }
        info = info->next;
    }
    if (found) { // 查找成功
        printf("\n该字符串出现的总次数为:%d\n", find_num);
    } else { // 查找不成功
        printf("\n|》》》          文本中没有该字符串！         《《《|\n\n");
    }
}
int Del_1()//删除一行字符串函数 
{
	printf("原文本为：\n");
	Output();
	printf("\n请输入要删除行的行号：");
	int linenum; 
	scanf("%d",&linenum);
	LINE * info, *p;
	info = start;
	while ((info->num < linenum) && info)  //寻找要删除的行 
		info = info->next;
	if (info == NULL)
		printf("\n输入的行号不存在\n");
	else
	{
		p = info->next;     //指向要删除的行后面一行 
		if (start == info) //如果删除的是第一行
		{
			start = info->next;
			if (start)  //如果删除后，不为空
				start->prior = NULL;
			else  //删除后为空
				last = NULL;
		}
		else
		{
			info->prior->next = info->next;  //指定行的上一行指向指定行的下一行
			if (info != last) //如果不是最后一行
				info->next->prior = info->prior;  //修改其下一行的指向头的指针 
			else  //如果是最后一行，修改尾指针
				last = info->prior;
		}
		free(info);
		while (p) //被删除行之后的行号减一 
		{
			p->num = p->num - 1;
			p = p->next;
		}
		printf("\n|》》》                删除成功！             《《《|\n");
		Sleep(1000);
		system("cls");
		Title();
		printf("\n|>>>                【 删除字符 】               <<<|\n\n");
		printf("删除过后的文本为：\n"); 
		Output();
		printf("\n");
	}
}
int Del_2()//删除特定字符串函数 
{
	int linenum, position,lenth;  //行，列，删除长度 
	printf("原文本为：\n");
	Output();
	printf("请输入要删除内容所在行，列，删除内容字节长度，中间用空格隔开\n");
	printf("注意：汉字占两个字节\n");
	scanf("%d %d %d",&linenum,&position,&lenth);
	position = (position*2)-1;
	getchar();
	LINE *info=start;
	char rest_str[N];
	if(linenum == 1)
	info = start;
	else
	for(int i=1;i<linenum;i++)     	 //让info指向删除内容所在行 
	info = info->next;      
	if (info == NULL)
		printf("\n该行没有字符！\n");
	else
	{
		if (strlen(info->str) <= (position + lenth))  //本行的字符长度<=待删除的列号+删除长度，直接在当前位置插入'\0'
			info->str[position] = '\0';
		else
		{	int i;
			for(i = position-1;info->str[i+lenth]!='\0';i++)
			info->str[i]=info->str[i+lenth];
			info->str[i]='\0';
		}
		printf("\n|》》》                删除成功！             《《《|\n");
		Sleep(1000);
		system("cls");
		Title();
		printf("\n|>>>                【 删除字符 】               <<<|\n\n");
		printf("删除过后的文本为：\n"); 
		Output();
		printf("\n");
	}
}
int Add_1()//添加一行文本函数 
{
	printf("原文本为：\n");
	Output();
	int linenum; 
	printf("\n请输入插入位置的行号：");
	scanf("%d", &linenum);
	LINE * info, * q, * p;
	p = start;
	q = NULL;
	while (p && p->num != linenum)               
	{
		q = p;				//插入行前面一行 
		p = p->next;	   //插入行后面一行
	}
	if (p == NULL && (q->num + 1) != linenum)	//指定行不存在，不能插入
	{
		printf("\n输入的行号不存在！\n");
		Sleep(1000);
		system("cls");
		Title();
		printf("\n|>>>                【 添加字符 】               <<<|\n");
		Add_1();
	}
	else // 指定行存在，进行插入
	{
		info = (LINE *)malloc(sizeof(LINE));
		printf("请输入要插入的字符串:");
		scanf("%s", info->str);
		info->num = linenum;
		if (linenum == 1)  			  //插入在第一行
		{
			info->next = p;
			p->prior = info;
			info->prior = NULL;
			start = info;
		}
		else if (q->num != linenum)  //插入在最后一行
		{
			q->next = info;
			info->next = p;
			info->prior = q;
		}
		else     //插入在其他行
		{
			q->next = info;
			info->next = p;
			p->prior = info;
			info->prior = q;
		}
		while (p)   //如果不是插入在最后一行，插入行后面的行号都加1
		{
			p->num = p->num + 1;
			p = p->next;
		}
		printf("\n|》》》                添加成功！             《《《|\n");
		Sleep(1000);
		system("cls");
		Title();
		printf("\n|>>>                【 添加字符 】               <<<|\n\n");
		printf("添加过后的文本为：\n"); 
		Output();
		printf("\n");
	}
}
int Add_2()//添加特定字串函数 
{
	printf("原文本为：\n");
	Output(); 
	char string[N]; //定义一个字符数组存放插入的字符串 
	int linenum;  //行号 
	int position; //列号 
	printf("\n请输入插入位置的行号：");
	scanf("%d", &linenum);
	printf("请输入插入位置的列号：");
	scanf("%d", &position);
	position = (position*2)-1; 
	printf("请输入要插入的字符串：");
	scanf("%s", string);
	LINE * info;
	int len, i;
	int lenth;
	char rest_str[N],kongge[2] = { " " };
	info = start;
	while (info && info->num != linenum)   //查询要插入的行
	{
		info = info->next;
	}
	if (info == NULL)
		printf("\n输入的行号不存在！\n");
	else if (position < 0)
		printf("\n输入的列号不存在！\n");
	else    //如果行和列都存在，则进行插入
	{
		lenth = strlen(info->str);
		//strlen()作用是计数器，从内存中的某个位置（可以是字符串开头、中间的某个位置、甚至是某个不确定的内存区域）
		//开始扫描，直到碰到第一个字符串结束符'\0'为止，然后返回计数器值（长度不包括'\0'） 
		if (lenth < position)	//插入列大于本行文件列数
		{
			len = position - lenth - 1;
			for (i = 0; i < len; i++)
			strcat(info->str, kongge);   //将空余的部分插入空格符
			strcat(info->str, string);    //插入字符到列的未尾
		}
		else   //插入列在本行文字的中间
		{
			strcpy(rest_str, &info->str[position - 1]); //strcpy()字符串复制函数，同时也会复制字符串结束符 
			strcpy(&info->str[position - 1], string);
			strcat(info->str, rest_str);  //strcat()作用是在一个字符串末尾增加新的字符：将rest_str字符串拷贝到info->str的字符串末尾，info所指向的字符串要留有足够的空间来容纳要拷贝的字符串 
		}
		printf("\n|》》》                添加成功！             《《《|\n");
		Sleep(1000);
		system("cls");
		Title();
		printf("\n|>>>                【 添加字符 】               <<<|\n\n");
		printf("添加过后的文本为：\n"); 
		Output();
		printf("\n");
	}
} 
int Add()
{
	system("cls");
	Title();
	printf("|                 【 添加字符菜单 】                |\n");
	printf("|                    0.返回上一级                   |\n");
	printf("|                   1.添加一行字符                  |\n");
	printf("|                   2.添加特定字符                  |\n");
	printf("|---------------------------------------------------|\n");
	printf("                  请输入一个数<0-2> :");
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
			printf("输入错误！请重新输入");
			Sleep(1000);
			system("cls");
			Add();
			break;
	}
}

void GetFilePath(char *filePath, int mode) {
    OPENFILENAME ofn;       // 文件选择对话框结构体
    char szFile[N] = "";    // 用于保存文件路径

    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL; // 主窗口句柄
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = "Text Files\0*.TXT\0All Files\0*.*\0"; // 文件过滤器
    ofn.nFilterIndex = 1;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT;

    if (mode == 0) {
        // 打开文件
        ofn.lpstrTitle = "选择要打开的文件";
        if (GetOpenFileName(&ofn)) {
            strcpy(filePath, szFile);
        } else {
            printf("\n|》》》        用户取消了文件选择。          《《《|\n\n");
            exit(0);
        }
    } else {
        // 保存文件
        ofn.lpstrTitle = "选择保存文件的位置";
        if (GetSaveFileName(&ofn)) {
            // 检查是否包含后缀
            if (!strchr(szFile, '.')) {
                strcat(szFile, ".txt"); // 如果没有后缀，添加".txt"
            }
            strcpy(filePath, szFile);
        } else {
            printf("\n|》》》        用户取消了文件选择。          《《《|\n\n");
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

    // 通过文件资源管理器选择文件路径
    GetFilePath(name, 1);

    while ((fp = fopen(name, "w")) == NULL) {
        printf("文件无法创建，请重新选择保存路径：");
        GetFilePath(name, 1);
    }
    while (info) {
        fputs(info->str, fp);
        putc('\n', fp);
        info = info->next;
    }
    fclose(fp);
    printf("\n|》》》                保存成功！             《《《|\n");

    return 0;
}

int Open() {
    char buf[N];   // 缓冲区
    FILE *fp;
    int i = 1;     // 行号计数
    int len;
    char name[256];

    // 通过文件资源管理器选择文件路径
    GetFilePath(name, 0);

    if ((fp = fopen(name, "r")) == NULL) {
        printf("\n|》》》       抱歉！文件不存在,无法打开！       《《|\n\n");
        exit(0);
    }

    // 清空原有线性表
    LINE *current = start, *temp;
    while (current) {
        temp = current->next;
        free(current);
        current = temp;
    }
    start = NULL;
    last = NULL;

    // 创建新线性表并加载数据
    LINE *prev = NULL;
    while (fgets(buf, N, fp) != NULL) {
        len = strlen(buf);

        // 去掉换行符
        if (buf[len - 1] == '\n') {
            buf[len - 1] = '\0';
        }

        // 创建新节点
        LINE *newLine = (LINE *)malloc(sizeof(LINE));
        if (!newLine) {
            printf("\n|》》》              内存不足！            《《《|\n\n");
            fclose(fp);
            exit(0);
        }

        strcpy(newLine->str, buf); // 复制内容到节点
        newLine->num = i++;        // 设置行号
        newLine->prior = prev;    // 前向链接
        newLine->next = NULL;     // 默认没有下一个节点

        if (prev) {
            prev->next = newLine; // 更新前节点的 next 指针
        } else {
            start = newLine; // 第一个节点作为 start
        }

        prev = newLine; // 更新前节点
    }

    last = prev; // 最后一个节点作为 last
    fclose(fp);

    printf("\n|》》》          文件已成功加载到线性表！        《《《|\n");
    return 0;
}



/*
int Save()
{
	char  *p,c; 
	FILE *fp;
    LINE *info=start;
	int i=0; 
    char name[20];//定义一个字符数组用于存放输入的文件路径字符 
	printf("\n请输入保存地址(例如: c:\\a.txt):");
	scanf("%s",name);
	while ((fp=fopen(name,"w"))==NULL)
	{
		printf("文件不存在，请重新输入文件名：");
		scanf("%s",name);
	} 
		while(info)
	{   
		p=info->str; 
        while(*p)  
			putc(*p++, fp);
		putc('\n', fp); //将'\n'写入指定的fp中，并将位置标识符往前移动 
		info = info->next;
	}
    fclose(fp);
	printf("\n|》》》                保存成功！             《《《|\n");	
	
	LINE *temp;
	temp=NULL;
	int inct;
	if ((fp = fopen(name, "r")) == NULL)
	{
		printf("\t文件打不开！\n");
		exit(0);
	}
	
	start = (LINE*)malloc(sizeof(LINE)); //动态生成一行的结点空间
	info = start;
	inct = 1;
	while ((c = fgetc(fp)) != EOF)
	{
		i = 0;
		info->str[i] = c;
		i++;
		while ((c = fgetc(fp)) != '\n')  //从文件中读取一行字符到线性表中，文件中每一行以\n为结束标
		{
			info->str[i] = c;
			i++;
		}
		info->str[i] = '\0';  //线性表中每行末尾的结束标志
		info->num = inct++;  //行号和计数器都加1
		info->next = (LINE*)malloc(sizeof(LINE)); //为下一行动态生成一行的结点空间
		if (!info->next)
		{
			printf("\n|》》》              内存已经用完！           《《《|\n\n");  
			exit(0);
		}
		info->prior = temp;
		temp = info;
		info = info->next;
	}
	temp->next = NULL;
	last = temp;
	free(info);  //释放节点空间 
	start->prior = NULL;
	fclose(fp);
	//读入线性表成功 
} 

int Open()
{
	char buf[N];//缓冲区
	FILE *fp;
	int i=1;  //记录行号 
	int len;
	char name[50]; //定义一个字符数组用于存放输入的文件路径字符 
	printf("\n请输入要打开文件的地址(例如: c:\\a.txt):");
	scanf("%s",name);
	if ((fp = fopen(name, "r")) == NULL)  
	{
		printf("\n|》》》       抱歉！文件不存在,无法打开！       《《|\n\n");
		exit(0); //系统正常退出 
	}
	while(fgets(buf,N,fp)!=NULL)
	{
		len=strlen(buf); 
		//strlen()作用是计数器，从内存中的某个位置（可以是字符串开头、中间的某个位置、甚至是某个不确定的内存区域）
		//开始扫描，直到碰到第一个字符串结束符'\0'为止，然后返回计数器值（长度不包括'\0'） 
		buf[len-1]='\0';
		printf("\n第%d行|%s",i,buf); //按照特定格式输出文字内容 
		i++;   //行号加1 
	}
	printf("\n");
	fclose(fp); //关闭文件 
	return 0;
}*/
int Delete()
{
	system("cls");
	Title();
	printf("|                 【 删除字符菜单 】                |\n");
	printf("|                    0.返回上一级                   |\n");
	printf("|                   1.删除一行字符                  |\n");
	printf("|                   2.删除特定字符                  |\n");
	printf("|---------------------------------------------------|\n");
	printf("                  请输入一个数<0-2> :");
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
			printf("输入错误！请重新输入");
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
	printf("|                 【 统计字符菜单 】                |\n");
	printf("|                    0.返回上一级                   |\n");
	printf("|                   1.各类字符数目                  |\n");
	printf("|                   2.特定字符数目                  |\n");
	printf("|---------------------------------------------------|\n");
	printf("                  请输入一个数<0-2> :");
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
			printf("输入错误！请重新输入\n");
			Sleep(1000);
			system("cls");
			Count();
			break;
	}
} 
int Choice()
{
	scanf("%d",&ch);
	//判断输入的字符是什么字符 
	switch (ch)
	{
		case 0: 
			printf("\n|》》》                退出成功！             《《《|\n\n");
			exit(0); 
			break;
		case 1:
			system("cls");
			Title();
			printf("\n|>>>                【 输入文章 】               <<<|\n\n");
			getchar();
			Input(); 
			break;
		case 2:
			system("cls");
			Title();
			printf("\n|>>>                【 输出文章 】               <<<|\n\n");
			Output();
			break;
		case 3:
			system("cls");
			Title();
			printf("\n|>>>                【 删除字符 】               <<<|\n\n");
			Delete();
			break;
		case 4:
			system("cls");
			Title();
			printf("\n|>>>                【 添加字符 】               <<<|\n\n");
			Add(); 
			break;
		case 5: 
			Count();
			break;
		case 6: 
			system("cls");
			Title();
			printf("\n|>>>                【 存储文章 】               <<<|\n\n");   
			Save();   
			break;
		case 7: 
			system("cls");
			Title();
			printf("\n|>>>                【 打开文章 】               <<<|\n\n");
			Open();
			break;
		default:
			printf("选择错误，重新输入\n");
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
		system("cls");//头文件为 #include<stdlib.h>清屏功能
	}	
}
