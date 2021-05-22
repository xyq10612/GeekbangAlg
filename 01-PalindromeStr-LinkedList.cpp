// ---------- 说明 ----------
// 回文字符串的判断，字符串通过单链表存储
// 思路
// 1. 快慢指针先找到中间节点
// 2. 从中间节点之后，将数据逆序
// 3. 头节点、中间节点开始遍历，字符串是否一致
// 4. 还原后半部分的逆序字符串

#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;

struct Node
{
    char ch;
    Node *next;
};

Node* gen_str()
{
    std::string str;
    std::cin >> str;

    Node* result = nullptr;
    Node* cur = nullptr;
    for (auto ch : str)
    {
        Node* node = new Node();
        node->ch = ch;
        node->next = nullptr;

        if (result == nullptr)
        {
            result = node;
        }
        else
        {
            cur->next = node;
        }

        cur = node;
    }

    return result;
}

Node* reverse(Node* begin)
{
    Node* cur = nullptr;
    Node* p = nullptr;

    while (begin->next != nullptr)
    {
        p = begin;
        begin = begin->next;
        p->next = cur;
        cur = p;
    }

    begin->next = cur;
    return begin;
}

bool check(Node* str_list)
{
    // 就一个字符
    if (str_list->next == nullptr)
        return true;

    // 快慢指针找到中间节点
    Node* normal = str_list;
    Node* fast = str_list;
    while (fast->next != nullptr && fast->next->next != nullptr)
    {
        normal = normal->next;
        fast = fast->next->next;
    }

    // 找到了中间节点normal
    // 从normal开始逆序
    Node* center = normal;

    Node* reverse_begin = center->next;
    reverse_begin = reverse(reverse_begin);

    // 比较这两个子串是否相同
    Node* p = str_list;
    Node* q = reverse_begin;
    bool result = true;
    while (q->next != nullptr)
    {
        if (p->ch != q->ch)
        {
            result = false;
            break;
        }

        p = p->next;
        q = q->next;
    }

    // 之前的逆序还原回来
    center->next = reverse(reverse_begin);
    return result;
}

int main()
{
    while (true)
    {
        std::cout << "请先输入一个字符串：";
        Node *str_list = gen_str();
        bool result = check(str_list);
        std::cout << "回文字符串 " << (result ? "true" : "false") << std::endl;

        std::cout << "字符串还原结果：";
        Node *p = str_list;
        while (p != nullptr)
        {
            std::cout << p->ch;
            p = p->next;
        }

        std::cout << std::endl;
    }
}
