#include <stdio.h>
#include <string.h>

//定义结构体struct
struct student_data
{
    char name[99];
    float score;

};

// struct 定义的是类型；这里才创建该类型的数组，并定义 count。
struct student_data stu[99];
int flag = 1, count = 0;

//定义函数swap
/*
注意这里要传地址 
如果传的是变量不会改变原变量

1. 参数列表里的 float *x
   这里出现的 * 不是运算符, 而是"类型声明"的一部分,
   它修饰的是 x, 说明 x 是一个指针变量, 类型是 float *(指向 float 的指针),
   x 里存放的是一块 float 内存的"地址"。
   所以这一行没有发生任何"取值"动作, 只是告诉编译器: 请按指针来解析这个参数。
   等价写法: void swap(float* x, float* y)  或  void swap(float  *  x, ...)

2. 函数体里的 *x
   这里的 * 才是解引用运算符 (dereference / 间接访问),
   意思是: 顺着 x 里存的地址, 去访问它指向的那块内存。
       float tmp = *x;  读: 顺着 x 的地址把那块 float 取出来
       *x = *y;         写: 顺着 x 的地址把 y 指向的值写进去

   口诀: 声明处的 * 是"身份"(你是指针); 表达式里的 * 是"动作"(顺着地址去取值)。

   另外别把 & 和 * 混了:
       & 是"取地址"运算符  -> &a 得到变量 a 的地址
       * 是"解引用"运算符  -> *p 通过地址 p 拿到它指向的值
*/
void swap(struct student_data *x, struct student_data *y){
    struct student_data tmp = *x;
    *x = *y;
    *y = tmp;
}

//冒泡排序
/*
为什么调用时写 swap(&stu[i], &stu[i-1]), 而不是 swap(stu[i], stu[i-1])?
因为 stu[i] 是"元素本身", 不是地址。三个东西要分清:

    写法        类型                        是什么
    stu         struct student_data *       数组首元素的地址(数组名会退化成指针)
    stu[i]      struct student_data         第 i 个元素本身(一个完整的结构体值)
    &stu[i]     struct student_data *       第 i 个元素的地址

一句话: 数组名是地址, 但数组元素不是地址。
swap 要的是"地址", 所以必须用 & 取第 i 个元素的地址(门牌号)。

比喻: stu 是整栋楼的位置, stu[i] 是 302 房间里放的东西, &stu[i] 是 302 的门牌号。
      要让 swap 进房间搬东西, 得先给它门牌号。

等价关系(很重要):
    &stu[i]  ≡  stu + i        // 取地址
    stu[i]   ≡  *(stu + i)     // 解引用

所以下面两种写法完全等价:
    swap(&stu[1], &stu[2]);
    swap(stu + 1, stu + 2);

    * 和 & 互为逆运算: stu + i 得到地址, *(stu + i) 又把地址解回元素, 即 stu[i]。
    C 的 [] 下标运算符本质就是 *() 的语法糖。

另外: swap 的参数已经改成 struct student_data *, 所以 *x 解出来的是"一个完整结构体",
而不是 float。指针的类型决定了 * 一次取多少字节(float 取 4 字节, 结构体取整个 sizeof)。
*/


void sort(){
    for(int i = 0; i < count-1; i++){
        for(int j = 0; j < count-1-i; j++){
            if(stu[j].score < stu[j+1].score) 
                swap(&stu[j], &stu[j+1]);
        }

    }
}


//主函数
int main(void){

    while (flag)
    {
        printf("请输入数字使用以下功能\n"
        "1.录入学生姓名及成绩\n"
        "2.查询成绩表\n"
        "3.查询学生成绩及排名\n"
        "4.修改学生成绩\n"
        "5.退出\n");

        int pos = 0;
        scanf("%d", &pos);

        if(pos == 1){
            printf("请输入学生姓名:\n");
            scanf(" %s", stu[count].name);
             /*
            %c 会吃到上一次留下的换行符%d 只吃掉数字，把回车 \n 留在了输入缓冲区。
            紧接着 %c 立刻把它读走，根本不会等你输入名字。

            修法：在 %c 前加一个空格，表示“跳过所有空白字符”：
            */
            printf("请输入学生成绩:\n");
            scanf(" %f", &stu[count].score);
            count++;

            sort();

            
        }
        else if(pos == 2){
            printf("姓名\t成绩\n");
            for(int i = 0; i < count; i++){
                //printf("%s:%d", stu[i].name, sizeof(stu[i].name));
                if(strlen(stu[i].name) == 8) printf("%s%.1f\n", stu[i].name, stu[i].score);
                else printf("%s\t%.1f\n", stu[i].name, stu[i].score);
            }
        }
        else if(pos == 3){

            printf("请输入学生姓名:");
            char name_tmp[99];
            scanf(" %s", name_tmp);

            int found = -1;
            for(int i = 0; i < count; i++){
                if(strcmp(name_tmp, stu[i].name) == 0){
                    found = i;break;
                }
            }

            if(found == -1) printf("没有找到该同学\n");
            else{
                printf("成绩为:%.1f\n", stu[found].score);
            }

        }
        else if(pos == 4){

            printf("请输入学生姓名:");
            char name_tmp[99];
            scanf(" %s", name_tmp);

            int found = -1;
            for(int i = 0; i < count; i++){
                if(strcmp(name_tmp, stu[i].name) == 0){
                    found = i;
                    break;
                }
            }

            if(found == -1) printf("没有找到该同学\n");
            else{
                printf("原成绩为:%.1f,请输入新的成绩:", stu[found].score);
                scanf(" %f", &stu[found].score);
                sort();
            }

        }
        else if(pos == 5){
            flag = 0;
        }

    }
    

    return 0;
}