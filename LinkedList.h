#ifndef PROJEKT1_LINKEDLIST_H
#define PROJEKT1_LINKEDLIST_H

#include "LinkedListNode.h"

namespace DataStructures
{
    /// \brief Represents a circular doubly-linked list
    /// \tparam T Type parameter
    template<typename T>
    class LinkedList
    {
    public:
        /// \brief Constructs an empty list
        LinkedList() : head(nullptr), count(0)
        {
        }

        /// \brief Copy constructor
        /// \param list List to copy from
        LinkedList(const LinkedList &list) : head(nullptr), count(0)
        {
            LinkedListNode<T> *current = list.head;
            if (current != nullptr)
            {
                do
                {
                    this->AddLast(current->GetValue());
                    current = current->GetNext();
                }
                while (current != list.head);
            }
        }

        /// \brief Destructs the list freeing up the memory used to store its items
        ~LinkedList()
        {
            this->Clear();
        }

        /// \brief Returns the pointer to the first node of the list
        /// \return Pointer to the first node of the list
        const LinkedListNode<T> *GetFirst() const
        {
            return this->head;
        }

        /// \brief Returns the pointer to the last node of the list
        /// \return Pointer to the last node of the list
        const LinkedListNode<T> *GetLast() const
        {
            return this->head == nullptr ? nullptr : this->head->previous;
        }

        /// \brief Returns the pointer to the first node of the list
        /// \return Pointer to the first node of the list
        LinkedListNode<T> *GetFirst()
        {
            return this->head;
        }

        /// \brief Returns the pointer to the last node of the list
        /// \return Pointer to the last node of the list
        LinkedListNode<T> *GetLast()
        {
            return this->head == nullptr ? nullptr : this->head->previous;
        }

        /// \brief Returns the current number of elements in the list
        /// \return Current number of elements
        int GetCount() const
        {
            return this->count;
        }

        /// \brief Adds a new item at the given \p index position in the list
        /// \param index A zero-based index in the array
        /// \param value An item to add
        void AddAt(int index, T value)
        {
            if (index >= this->count)
            {
                throw std::invalid_argument("Index is outside the list");
            }

            if (index == 0)
            {
                this->AddFirst(value);
            }

            auto node = this->head;
            for (int i = 0; i < index; i++)
            {
                node = node->next;
            }

            AddBefore(node, value);
        }

        /// \brief Removes an item at the given \p index position in the array
        /// \param index A zero-based index in the array
        void RemoveAt(int index)
        {
            if (index >= this->count)
            {
                throw std::invalid_argument("Index is outside the list");
            }

            if (index == 0)
            {
                return this->RemoveFirst();
            }

            auto node = this->head;
            for (int i = 0; i < index; i++)
            {
                node = node->next;
            }

            Remove(node);
            --this->count;
        }

        /// \brief Adds a new \p value item to the beginning of the list
        /// \param value An item to add
        void AddFirst(T value)
        {
            auto node = new LinkedListNode(this, value);
            if (this->IsEmpty())
            {
                this->head = node;
                this->head->previous = this->head->next = this->head;
            }
            else
            {
                AddBefore(this->head, node);
                this->head = node;
            }

            this->count++;
        }

        /// \brief Adds a new \p value item to the end of the list
        /// \param value An item to add
        void AddLast(T value)
        {
            auto node = new LinkedListNode(this, value);
            if (this->IsEmpty())
            {
                this->head = node;
                this->head->previous = this->head->next = this->head;
            }
            else
            {
                AddBefore(this->head, node);
            }

            this->count++;
        }

        /// \brief Adds a new \p value item before the given \p node
        /// \param value An item to add
        void AddBefore(LinkedListNode<T> *node, T value)
        {
            if (node == nullptr || node->GetList() != this)
            {
                throw std::exception();
            }

            auto newNode = new LinkedListNode(this, value);
            AddBefore(node, newNode);
            this->count++;
        }

        /// \brief Adds a new \p value item after the given \p node
        /// \param value An item to add
        void AddAfter(LinkedListNode<T> *node, T value)
        {
            if (node == nullptr || node->GetList() != this)
            {
                throw std::exception();
            }

            auto newNode = new LinkedListNode(this, value);
            AddAfter(node, newNode);
            this->count++;
        }

        /// \brief Removes all the elements from the list
        void Clear()
        {
            if (this->IsEmpty())
            {
                return;
            }

            LinkedListNode<T>* current = this->head;
            LinkedListNode<T>* nextNode = nullptr;
            this->head->previous->next = nullptr;
            while (current != nullptr)
            {
                nextNode = current->next;
                delete current;
                current = nextNode;
            }

            this->head = nullptr;
            this->count = 0;
        }

        /// \brief Removes the first items of the list
        void RemoveFirst()
        {
            if (this->IsEmpty())
            {
                throw std::exception();
            }

            auto secondNode = this->head->next;
            auto lastNode = this->head->previous;
            Remove(this->head);
            --this->count;

            if (this->count > 0)
            {
                lastNode->next = secondNode;
                secondNode->previous = lastNode;
                this->head = secondNode;
            }
            else
            {
                this->head = nullptr;
            }
        }

        /// \brief Removes the last item of the list
        void RemoveLast()
        {
            if (this->IsEmpty())
            {
                throw std::exception();
            }

            auto lastPreviousNode = this->GetLast()->previous;
            Remove(this->GetLast());
            --this->count;

            if (this->count > 0)
            {
                lastPreviousNode->next = this->head;
                this->head->previous = lastPreviousNode;
            }
            else
            {
                this->head = nullptr;
            }
        }

        /// \brief Determines whether the \p value item is present in the list
        /// \param value An item to search for
        /// \return \a true if the \p value item was found, \a false otherwise
        bool Contains(T value) const
        {
            LinkedListNode<T> *node = this->head;
            for (int i = 0; i < this->count; i++)
            {
                if (node->item == value)
                {
                    return true;
                }

                node = node->next;
            }

            return false;
        }

        /// \brief Searches the list for the first present \p value item
        /// \param value An item to search for
        /// \return Node containing \p value item, nullptr otherwise
        LinkedListNode<T> *Find(T value)
        {
            LinkedListNode<T> *node = this->head;
            for (int i = 0; i < this->count; i++)
            {
                if (node->item == value)
                {
                    return node;
                }

                node = node->next;
            }

            return nullptr;
        }

        /// \brief Searches the list for the first present \p value item
        /// \param value An item to search for
        /// \return Node containing \p value item, nullptr otherwise
        const LinkedListNode<T> *Find(T value) const
        {
            LinkedListNode<T> *node = this->head;
            for (int i = 0; i < this->count; i++)
            {
                if (node->item == value)
                {
                    return node;
                }

                node = node->next;
            }

            return nullptr;
        }

        /// \brief Searches the list for the last present \p value item
        /// \param value An item to search for
        /// \return Node containing \p value item, nullptr otherwise
        LinkedListNode<T> *FindLast(T value)
        {
            LinkedListNode<T> *node = this->GetLast();
            for (int i = 0; i < this->count; i++)
            {
                if (node->item == value)
                {
                    return node;
                }

                node = node->previous;
            }

            return nullptr;
        }

        /// \brief Searches the list for the last present \p value item
        /// \param value An item to search for
        /// \return Node containing \p value item, nullptr otherwise
        const LinkedListNode<T> *FindLast(T value) const
        {
            LinkedListNode<T> *node = this->GetLast();
            for (int i = 0; i < this->count; i++)
            {
                if (node->item == value)
                {
                    return node;
                }

                node = node->previous;
            }

            return nullptr;
        }

        /// \brief Determines whether the list is empty
        /// \return \a true if the list has no elements, \a false otherwise
        bool IsEmpty() const
        {
            return this->head == nullptr;
        }

        /// \brief Creates a dynamic array containing all of the items from the list
        /// \return A copy of the created array
        DynamicArray<T> ToArray() const
        {
            int capacity = 4;
            while (capacity < this->count)
            {
                capacity *= 2;
            }

            DynamicArray<T> array(capacity);
            auto node = this->head;
            for (int i = 0; i < this->count; i++)
            {
                array.Add(node->item);
                node = node->next;
            }

            return array;
        }

    private:
        LinkedListNode<T> *head;
        int count;

        static void AddBefore(LinkedListNode<T> *node, LinkedListNode<T> *newNode)
        {
            newNode->next = node;
            newNode->previous = node->previous;
            node->previous->next = newNode;
            node->previous = newNode;
        }

        static void AddAfter(LinkedListNode<T> *node, LinkedListNode<T> *newNode)
        {
            newNode->previous = node;
            newNode->next = node->next;
            node->next->previous = newNode;
            node->next = newNode;
        }

        static void Remove(LinkedListNode<T> *node)
        {
            node->next->previous = node->previous;
            node->previous->next = node->next;
            delete node;
        }
    };
}

#endif //PROJEKT1_LINKEDLIST_H
