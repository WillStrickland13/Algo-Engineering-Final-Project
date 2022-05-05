//
// Created by William Strickland on 5/4/22.
//

#ifndef ASSIGNMENT2_ADJLIST_H
#define ASSIGNMENT2_ADJLIST_H

#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <random>
#include <set>
using namespace std;
using namespace std::chrono;
struct AdjListNode {
    int data;
    struct AdjListNode *next;
    struct AdjListNode *prev;

    int degree;
    AdjListNode(int data, AdjListNode*next, AdjListNode *prev) : data(data), next(next), prev(prev) {}
    AdjListNode(int data) : data(data), next(nullptr), prev(nullptr) {}
    AdjListNode(AdjListNode const &node){
        this->data = node.data;
        this->next = node.next;
        this->prev = node.prev;
    }
    AdjListNode(){
        this->data = 0;
        this->next = nullptr;
        this->prev = nullptr;
    }
};

/*
 * Adjacency List
 */
class AdjList {
public:
    struct AdjListNode *head;
    struct AdjListNode *tail;
    struct AdjListNode *degreeListPointer;
    int color=-1;
    AdjListNode& operator[](int index)
    {
        AdjListNode* node = head;
        for (int i = 0; i < index; i++)
        {
            node = node->next;
        }
        return *node;
    }
    int size()
    {
        int count = 0;
        AdjListNode* node = head;
        while (node != nullptr)
        {
            count++;
            node = node->next;
        }
        return count;
    }
    void addAdjListNode(AdjListNode* newNode)
    {

        if (head == nullptr)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    void addAdjListNode(AdjListNode newNode)
    {

        if (head == nullptr)
        {
            head = &newNode;
            tail = &newNode;
        }
        else
        {
            tail->next = &newNode;
            newNode.prev = tail;
            tail = &newNode;
        }
    }
    void removeAdjListNode(int index){
        cout<<"starting deletion"<<endl;
        AdjListNode* node = head;
        for (int i = 0; i < index; i++)
        {
            node = node->next;
        }
        if (node->prev != nullptr)
        {
            node->prev->next = node->next;
        }
        if (node->next != nullptr)
        {
            node->next->prev = node->prev;
        }
        if (node == head)
        {
            head = node->next;
        }
        if (node == tail)
        {
            tail = node->prev;
        }
        delete node;

        cout<< "Node removed" << endl;
    }

    void removeAdjListNodeByVertex(int v){
        AdjListNode* node = head;
        int i=0;
        while (node != nullptr)
        {
            if (node->data == v)
            {
                if (node->prev != nullptr)
                {
                    node->prev->next = node->next;
                }
                if (node->next != nullptr)
                {
                    node->next->prev = node->prev;
                }
                if (node == head)
                {
                    head = node->next;
                }
                if (node == tail)
                {
                    tail = node->prev;
                }
                return;
            }
            node = node->next;
            i++;
        }
    }

    void printAdjList(){
        AdjListNode* node = head;
        while (node != nullptr)
        {
            cout<<node->data<<" ";
            node = node->next;
        }
        cout<<endl;
    }

};
#endif //ASSIGNMENT2_ADJLIST_H
