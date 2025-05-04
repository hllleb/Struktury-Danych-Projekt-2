#ifndef PROJECT2_ARRAYPRIORITYQUEUE_H
#define PROJECT2_ARRAYPRIORITYQUEUE_H

#include "IPriorityQueue.h"
#include "LinkedList.h"

namespace DataStructures
{
    class LinkedListPriorityQueue : public IPriorityQueue
    {
    public:
        int GetCount() const
        {
            return this->elements.GetCount();
        }

        int IsEmpty() const
        {
            return this->elements.IsEmpty();
        }

        void Clear()
        {
            return this->elements.Clear();
        }

        void Enqueue(int element, int priority)
        {
            this->elements.AddLast({element, priority});
        }

        int Dequeue()
        {
            if(this->IsEmpty())
            {
                throw std::exception();
            }

            auto node = GetMaxNode();
            int element = node->GetValue().element;
            this->elements.RemoveNode(node);
            return element;
        }

        int Peek() const
        {
            if(this->IsEmpty())
            {
                throw std::exception();
            }

            auto node = GetMaxNode();
            return node->GetValue().element;
        }

        void Modify(int element, int priority)
        {
            if(this->IsEmpty())
            {
                throw std::exception();
            }

            auto node = this->elements.GetFirst();
            for(int i = 0; i < this->elements.GetCount(); i++)
            {
                if(node->GetValue().element == element)
                {
                    node->SetValue({element, priority});
                    break;
                }

                node->GetNext();
            }
        }

    private:
        LinkedList<QueueItem<int, int>> elements;

        LinkedListNode<QueueItem<int, int>>* GetMaxNode()
        {
            auto node = this->elements.GetFirst();
            auto maxNode = node;

            for(int i = 1; i < this->elements.GetCount(); i++)
            {
                node = node->GetNext();
                if(node->GetValue().priority > maxNode->GetValue().priority)
                {
                    maxNode = node;
                }
            }

            return maxNode;
        }

        const LinkedListNode<QueueItem<int, int>>* GetMaxNode() const
        {
            auto node = this->elements.GetFirst();
            auto maxNode = node;

            for(int i = 1; i < this->elements.GetCount(); i++)
            {
                node = node->GetNext();
                if(node->GetValue().priority > maxNode->GetValue().priority)
                {
                    maxNode = node;
                }
            }

            return maxNode;
        }
    };

} // DataStructures

#endif //PROJECT2_ARRAYPRIORITYQUEUE_H
