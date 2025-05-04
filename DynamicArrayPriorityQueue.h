#ifndef PROJECT2_DYNAMICARRAYPRIORITYQUEUE_H
#define PROJECT2_DYNAMICARRAYPRIORITYQUEUE_H

#include "IPriorityQueue.h"
#include "DynamicArray.h"
#include "QueueItem.h"
#include "stdexcept"

namespace DataStructures
{

    class DynamicArrayPriorityQueue : public IPriorityQueue
    {
    public:
        int GetCount() const
        {
            return this->elements.GetLength();
        }

        int IsEmpty() const
        {
            return this->GetCount() == 0;
        }

        void Clear()
        {
            this->elements.Clear();
        }

        void Enqueue(int element, int priority)
        {
            this->elements.Add({element,priority});
        }

        int Dequeue()
        {
            if(this->IsEmpty())
            {
                throw std::exception();
            }

            int index = this->GetMaxIndex();
            int element = this->elements[index].element;
            this->elements.RemoveAt(index);
            return element;
        }

        int Peek() const
        {
            if(this->IsEmpty())
            {
                throw std::exception();
            }

            int index = this->GetMaxIndex();
            return this->elements[index].element;
        }

        void Modify(int element, int priority)
        {
            for(int i = 0; i < this->elements.GetLength(); i++)
            {
                if(this->elements[i].element == element)
                {
                    this->elements[i].priority = priority;
                    break;
                }
            }
        }

    private:
        DynamicArray<QueueItem<int, int>> elements;

        int GetMaxIndex() const
        {
            if(this->IsEmpty())
            {
                return -1;
            }

            int maxIndex = 0;
            for(int i = 1; i < this->GetCount(); i++)
            {
                if(this->elements[i].priority > this->elements[maxIndex].priority)
                {
                    maxIndex = i;
                }
            }

            return maxIndex;
        }
    };

} // DataStructures

#endif //PROJECT2_DYNAMICARRAYPRIORITYQUEUE_H
