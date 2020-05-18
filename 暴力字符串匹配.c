#include <stdio.h>
#include <string.h>

void main() {
    char main[] = "abcdefghijklmn";
    char sub[] = "jkb";
    int main_index = 0;
    int sub_index = 0;
    while(main_index < strlen(main)  && sub_index < strlen(sub)) {
        if (main[main_index] == sub[sub_index]) {   //判断主串与子串每个元素是否相等
            if (sub_index == strlen(sub) -1) {  //判断子串最后一个元素与主串是否相等，相等则匹配成功，输出
                int index = main_index - sub_index;
                printf("%d\n",index);
            }
            main_index++;
            sub_index++;
        }
        else { 
            main_index = main_index - sub_index + 1;  //匹配失败，回溯到主串匹配开始位置的下一位
            sub_index = 0;  //子串回溯到首位
        }
    }
}