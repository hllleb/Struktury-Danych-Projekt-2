#ifndef PROJECT2_HEAPPRIORITYQUEUE_H
#define PROJECT2_HEAPPRIORITYQUEUE_H

#include "IPriorityQueue.h"

namespace DataStructures
{
    class HeapPriorityQueue : public IPriorityQueue
    {
    public:
        int GetCount() const
        {
            return this->elements.GetLength();
        }

        bool IsEmpty() const
        {
            return this->elements.GetLength() == 0;
        }

        void Clear()
        {
            this->elements.Clear();
        }

        void Enqueue(int element, int priority)
        {
            this->elements.Add({element, priority});
            this->HeapifyUp(this->GetCount() - 1);
        }

        int Dequeue()
        {
            if (this->IsEmpty())
            {
                throw std::exception();
            }

            int element = this->elements[0].element;
            this->elements[0] = this->elements[this->GetCount() - 1];
            this->elements.RemoveLast();
            this->HeapifyDown(0);
            return element;
        }

        int Peek() const
        {
            if (this->IsEmpty())
            {
                throw std::exception();
            }

            return this->elements[0].element;
        }

        void Modify(int element, int priority)
        {
            int index = -1;

            for (int i = 0; i < this->GetCount(); ++i)
            {
                if (this->elements[i].element == element)
                {
                    index = i;
                    break;
                }
            }

            if (index == -1)
            {
                throw std::runtime_error("Element not found in priority queue.");
            }

            int oldPriority = this->elements[index].priority;
            this->elements[index].priority = priority;

            if (priority < oldPriority)
            {
                HeapifyUp(index);
            }
            else if (priority > oldPriority)
            {
                HeapifyDown(index);
            }
        }

    private:
        DynamicArray<QueueItem<int, int>> elements;

        void HeapifyUp(int index)
        {
            while (index > 0)
            {
                int parent = (index - 1) / 2;
                if (this->elements[index].priority > this->elements[parent].priority)
                {
                    std::swap(this->elements[index], this->elements[parent]);
                    index = parent;
                }
                else
                {
                    break;
                }
            }
        }

        void HeapifyDown(int index)
        {
            int count = this->GetCount();
            while (true)
            {
                int smallest = index;
                int left = 2 * index + 1;
                int right = 2 * index + 2;

                if (left < count && this->elements[left].priority > this->elements[smallest].priority)
                {
                    smallest = left;
                }

                if (right < count && this->elements[right].priority > this->elements[smallest].priority)
                {
                    smallest = right;
                }

                if (smallest != index)
                {
                    std::swap(this->elements[index], this->elements[smallest]);
                    index = smallest;
                }
                else
                {
                    break;
                }
            }
        }
    };

} // DataStructures

#endif //PROJECT2_HEAPPRIORITYQUEUE_H
