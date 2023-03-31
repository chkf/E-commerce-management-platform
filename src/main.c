#include "main.h"
#include <conio.h>

LinkedList list;
LinkedList m_list;
G_LinkedList g_list,r_list;
B_LinkedList b_list;

int main()
{
    int i=0;
    int command,status=0;
    char* account;
    bool res=0;
    InitList(&list);
    InitList(&m_list);
    InitGList(&g_list);
    InitGList(&r_list);
    InitBList(&b_list);
    readfile();                     //���ļ���ȡ�˺����룬��������
    m_readfile();
    read_goods();
    read_bills();
    read_recommendation();
    home();
    while(1)
    {
        if(status==0)
        {
            printf("press any key to continue\n");
            getch();
            home();
            printf("command>");
            my_scanf(&command,"command error>");
            switch (command)
            {
                case 1:
                    account = login();
                    if(account)status = 1;
                    else
                    {
                        printf("login error\n");
                    }
                    break;
                case 2:
                    account = m_login();
                    if(account)status = 2;
                    else
                    {
                        printf("login error\n");
                    }
                    break;
                case 3:
                    signup();
                    break;
                case 4:
                    m_signup();
                    break;
                case 5:
                    find_password();
                    break;
                case 6:
                    m_find_password();
                    break;
                case 7:
                    return 0;
                    break;
                default:
                    home();
                    printf("command error>");
                    break;
            }
            
        }
        else if(status==1)
        {
            printf("press any key to continue\n");
            getch();
            user_home();
            printf("command>");
            my_scanf(&command,"command error>");
            switch (command)
            {
                case 1:
                    search_goods(account);
                    break;
                case 2:
                    change_password();
                    break;
                case 3:
                    submit_goods(account);
                    break;
                case 4:
                    print_bill_buyer(account);
                    break;
                case 5:
                    delete_goods(account);
                    break;
                case 6:
                    print_bill(account);
                    break;
                case 7:
                    print_goods(account);
                    break;
                case 8:
                    apply_recommendation(account);
                    break;
                case 9:
                    recommended_goods(account);
                    break;
                case 10:
                    goods_info_change(account);
                    break;
                case 11:
                    status = 0;
                    break;
                case 12:
                    return 0;
                    break;
                default:
                    system("cls");
                    user_home();
                    printf("command error>");
                    break;
            }
        }
        else if(status==2)
        {
            //m_user_home();
        }
    }
    return 0;
}

/*��ֹ�������룬�����ܼ�����������ڵ��ô��Ƿ�Ϸ�*/
void my_scanf(int * i,char * error_warn)                    //error_warn�Ǵ�����ʾ
{
    bool res=0;
    while(!res)
    {
        if(!res)res=scanf("%d",i);
        while(getchar()!='\n');                             //û�յ�'\n'�Ϳ���
        if(!res)
        {
            printf(error_warn);
        }
    }
}

void user_home(void)
{
    system("cls");
    printf("command list for user\n");
    printf("    1.search goods\n");
    printf("    2.change password\n");
    printf("    3.submit products\n");
    printf("    4.Bought list\n");
    printf("    5.quit for selling\n");
    printf("    6.Sold list\n");
    printf("    7.selling goods\n");
    printf("    8.apply for recommendation for your goods\n");
    printf("    9.recommended goods\n");
    printf("    10.goods info update\n");
    printf("    11.log out\n");
    printf("    12.exit\n");
}

void m_user_home()
{

}

void home(void)
{
    system("cls");
    printf("         command list         \n");
    printf("1.log in as user\n");
    printf("2.log in as manager\n");
    printf("3.sign up as user\n");
    printf("4.sign up as manager\n");
    printf("5.forget user password\n");
    printf("6.forget manager password\n");
    printf("7.exit\n");
}