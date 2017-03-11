#ifndef DISJOINT_H
#define DISJOINT_H

#include <vector>
#include "Node.h"


class Disjoint
{
    public:

        Disjoint* sentinel;
        unsigned int size;
        int index;
        Node* node;

        Disjoint(Node* root)
        {
            sentinel = this;
            size = 1;
            index = root->index;
            node = root;
        }

        ~Disjoint()
        {}


        void Union(Disjoint* other)
        {
            if(sentinel == other->sentinel)
            {
                return;
            }


            if(size < other->size)
            {

                while(other->sentinel != other->sentinel->sentinel)
                {
                    other->sentinel = other->sentinel->sentinel;
                }

                other->sentinel->size += size;
                other->size = size = other->sentinel->size;

                resetSentinel(other->sentinel);
            }

            else
            {

                while(sentinel != sentinel->sentinel)
                {
                    sentinel = sentinel->sentinel;
                }

                sentinel->size += other->sentinel->size;
                size = other->size = sentinel->size;

                other->resetSentinel(sentinel);
            }
        }


        Disjoint* Find()
        {
            while(sentinel != sentinel->sentinel)
            {
                sentinel = sentinel->sentinel;
            }
            return sentinel;
        }

    private:


        void resetSentinel(Disjoint* newSent)
        {
            if(sentinel == this)
            {
                sentinel = newSent;
                return;
            }

            sentinel->resetSentinel(newSent);
            sentinel = newSent;
        }
};
#endif
