#ifndef _FIBONACCIHEAP_HPP_
#define _FIBONACCIHEAP_HPP_

#include <cstring>
#include <cstdio>
#include <algorithm>
#include <assert.h>

#define ERRORCODE 114514

    class fibHeapNode
    {
    public:
        fibHeapNode *left;
        fibHeapNode *right;
        fibHeapNode *parent;

        fibHeapNode *child;
        bool mark;
        int degree;
        int key;

        explicit fibHeapNode(int key_) : key(key_), left(this), right(this), parent(NULL), child(NULL), mark(false), degree(0) {}

        void insert(fibHeapNode *another)
        {
            another->left = this;
            another->right = this->right;
            this->right->left = another;
            this->right = another;
            another->parent = this->parent;
        }

        void addChild(fibHeapNode *p)
        {
            // printf("%d add %d degree=%d\n", key, p->key, degree + 1);
            if (child)
                child->insert(p);
            else
            {
                child = p;
                p->parent = this;
                p->left = p->right = p;
            }
            ++degree;
            p->mark = false;
        }

        void cut(fibHeapNode *min)
        {
            this->mark = false;
            --(parent->degree);
            if (parent->degree == 0)
                parent->child = NULL;
            else
                parent->child = this->right;
            this->left->right = this->right;
            this->right->left = this->left;
            min->insert(this);
        }

        void cascadingCut(fibHeapNode *min)
        {
            if (parent)
                if (mark)
                {
                    this->cut(min);
                    parent->cascadingCut(min);
                }
                else
                    mark = true;
        }
    };

    class fibHeap
    {
    public:
        int nodeNum;
        fibHeapNode *min;
        fibHeapNode *key2node[1001];

        explicit fibHeap() : nodeNum(0), min(NULL) { memset(key2node, 0, sizeof(key2node)); }

        int printRoot(bool print)
        {
            auto end = min->left;
            auto p = min;
            int i = 0;
            while (true)
            {
                if (print)
                    printf("%d,", p->key);
                ++i;
                if (p == end)
                    break;
                p = p->right;
            }
            if(print)
                putchar('\n');
            return i;
        }

        int insert(int key)
        {
            // assert(min);
            auto node = new fibHeapNode(key);
            key2node[key] = node;
            if (nodeNum)
            {
                min->insert(node);
                if (key < min->key)
                    min = node;
            }
            else
            {
                min = node;
            }
            return ++nodeNum;
        }

        int getMin()
        {
            return min ? min->key : ERRORCODE;
        }

        static fibHeap *unionHeap(fibHeap *h1, fibHeap *h2)
        {
            auto newHeap = new fibHeap();
            if (h1->min && h2->min)
            {
                h1->min->right->left = h2->min->left;
                h2->min->left->right = h1->min->right;
                h1->min->right = h2->min;
                h2->min->left = h1->min;

                newHeap->min = h1->min;
                if (h2->min->key < h1->min->key)
                    newHeap->min = h2->min;
            }
            else
                newHeap->min = (h1->min) ? (h1->min) : (h2->min);

            for (int i = 0; i < 1001; ++i)
                newHeap->key2node[i] = h1->key2node[i] ? h1->key2node[i] : h2->key2node[i];

            newHeap->nodeNum = h1->nodeNum + h2->nodeNum;

            return newHeap;
        }

        void remove(fibHeapNode *node)
        {
            --nodeNum;
            node->right->left = node->left;
            node->left->right = node->right;
            key2node[node->key] = NULL;
        }

        void tempRemove(fibHeapNode *node)
        {
            node->right->left = node->left;
            node->left->right = node->right;
        }

        void consolidate()
        {
            fibHeapNode *a[1000];
            for (int i = 0; i < 1000; ++i)
                a[i] = NULL;
            auto p = min;
            auto end = printRoot(false);
            int cnt = 0;
            while (true)
            {
                ++cnt;
                if (p->key < min->key)
                    min = p;
                auto temp = p;
                p = p->right;
                int d = temp->degree;
                while (a[d])
                {
                    if (a[d]->key < temp->key)
                        std::swap(a[d], temp);

                    tempRemove(a[d]);
                    temp->addChild(a[d]);

                    a[d] = NULL;
                    ++d;
                }
                a[d] = temp;
                if (cnt == end)
                    break;
                ;
            }
        }

        int extractMin()
        {
            if (min == NULL)
                return ERRORCODE;
            auto ret = min->key;
            auto p = min->child;
            for (int i = 0; i < min->degree; ++i)
            {
                p->parent = NULL;
                p = p->right;
            }
            if (p)
            {

                min->right->left = min->child->left;
                min->child->left->right = min->right;
                min->right = min->child;
                min->child->left = min;
            }
            --nodeNum;
            min->right->left = min->left;
            min->left->right = min->right;
            if (min->key != -1)
                key2node[min->key] = NULL;
            if (min->right == min)
            {
                min = NULL;
            }
            else
            {
                min = min->right;
                consolidate();
            }
            if (ret != -1)
                key2node[ret] = NULL;
            return ret;
        }

        int decrease(int k, int newKey)
        { // no check
            auto node = key2node[k];
            key2node[k] = NULL;
            if (newKey != -1)
                key2node[newKey] = node;
            node->key = newKey;
            auto father = node->parent;
            if (father && node->key < father->key)
            {
                node->cut(min);
                father->cascadingCut(min);
            }
            if (node->key < min->key)
                min = node;
            return min->key;
        }

        int deleteKey(int key)
        {
            auto node = key2node[key];
            decrease(key, -1);
            extractMin();
            return nodeNum;
        }
    };


#endif //_FIBONACCIHEAP_HPP_
