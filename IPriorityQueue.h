#ifndef PROJECT2_IPRIORITYQUEUE_H
#define PROJECT2_IPRIORITYQUEUE_H

namespace DataStructures
{

    class IPriorityQueue
    {
    public:
        virtual ~IPriorityQueue(){};
        virtual int GetCount() const = 0;
        virtual bool IsEmpty() const = 0;
        virtual void Clear() = 0;
        virtual void Enqueue(int element, int priority) = 0;
        virtual int Dequeue() = 0;
        virtual int Peek() const = 0;
        virtual void Modify(int element, int priority) = 0;
    };

} // DataStructures

#endif //PROJECT2_IPRIORITYQUEUE_H
