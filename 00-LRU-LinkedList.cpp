// ---------- 说明 ----------
// 基于链表实现LRU缓存淘汰算法:最近最少使用 //
// ---------- 思路 ---------- //
// 我们维护一个有序单链表，越靠近链表尾部的结点是越早之前访问的。当有一个新的数据被访问时，我们从链表头开始顺序遍历链表。
// 1. 如果此数据之前已经被缓存在链表中了，我们遍历得到这个数据对应的结点，并将其从原来的位置删除，然后再插入到链表的头部。
// 2. 如果此数据没有在缓存链表中，又可以分为两种情况：
//      a) 如果此时缓存未满，则将此结点直接插入到链表的头部；
//      b) 如果此时缓存已满，则链表尾结点删除，将新的数据结点插入链表的头部。

#include <stdio.h>
#include <iostream>
using namespace std;

struct Node
{
    int value;
    Node *next;
};

int list_count = 10;
Node* p_list = nullptr;
int count = 0;

void visit(int value)
{
    Node* cur = p_list;
    Node* pre = nullptr;

    // 如果此数据已经缓存在列表中，将该数据从当前位置删除，放在头部
    while (cur != nullptr)
    {
        if (cur->value == value)
        {
            // 头部节点就是，不用移动到头部，直接返回
            if (cur == p_list)
            {
                return;
            }
            // 从当前位置删除，放到头部，并返回
            else
            {
                pre->next = cur->next;
                cur->next = p_list;
                p_list = cur;
                return;
            }
        }

        pre = cur;
        cur = cur->next;
    }

    // 数据不在列表中，加入缓存

    // 缓存满了，删除尾节点，再加入头部
    // 缓存未满，直接加入列表头部

    //// 走到这一步，说明前面没有找到缓存，也说明while已经跑完了，pre就是尾节点
    if (count >= list_count)
    {
        cur = p_list;
        pre = nullptr;
        while (cur->next != nullptr)
        {
            pre = cur;
            cur = cur->next;
        }

        // pre是尾节点前一个节点
        pre->next = nullptr;
        count--;
    }

    // 加入列表头部
    cur = new Node();
    cur->value = value;
    cur->next = p_list;
    p_list = cur;
    count++;
}

int main()
{
    int value;
    while (true)
    {
        std::cout << "请输入值：";
        std::cin >> value;

        visit(value);

        std::cout << "当前LRU缓存列表变更为:";
        Node* cur = p_list;
        while (cur != nullptr)
        {
            std::cout << cur->value << " ";
            cur = cur->next;
        }

        std::cout << std::endl;
    }
}
