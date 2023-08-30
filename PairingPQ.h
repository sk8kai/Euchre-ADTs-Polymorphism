// Project identifier: 43DE0E0C4C76BFAA6D8C2F5AEAE0518A9C42CF4E

#ifndef PAIRINGPQ_H
#define PAIRINGPQ_H

#include "Eecs281PQ.h"
#include <deque>
#include <utility>
#include <algorithm>
using namespace std;

// A specialized version of the priority queue ADT implemented as a pairing
// heap.
template<typename TYPE, typename COMP_FUNCTOR = std::less<TYPE>>
class PairingPQ : public Eecs281PQ<TYPE, COMP_FUNCTOR> {
    // This is a way to refer to the base class object.
    using BaseClass = Eecs281PQ<TYPE, COMP_FUNCTOR>;

public:
    // Each node within the pairing heap
    class Node {
        public:
            // TODO: After you add add one extra pointer (see below), be sure
            //       to initialize it here.
            explicit Node(const TYPE &val)
                : elt{ val }, child{ nullptr }, sibling{ nullptr }
            {}

            // Description: Allows access to the element at that Node's
            //              position. There are two versions, getElt() and a
            //              dereference operator, use whichever one seems
            //              more natural to you.
            // Runtime: O(1) - this has been provided for you.
            const TYPE &getElt() const { return elt; }
            const TYPE &operator*() const { return elt; }

            // The following line allows you to access any private data
            // members of this Node class from within the PairingPQ class.
            // (ie: myNode.elt is a legal statement in PairingPQ's add_node()
            // function).
            friend PairingPQ;

        private:
            TYPE elt;
            Node *child;
            Node *sibling;
            // TODO: Add one extra pointer (parent or previous) as desired.
            Node *parent;
    }; // Node


    // Description: Construct an empty pairing heap with an optional
    //              comparison functor.
    // Runtime: O(1)
    explicit PairingPQ(COMP_FUNCTOR comp = COMP_FUNCTOR()) :
        BaseClass{ comp } {
        // TODO: Implement this function.
            numNodes = 0;
            root = nullptr;
    } // PairingPQ()


    // Description: Construct a pairing heap out of an iterator range with an
    //              optional comparison functor.
    // Runtime: O(n) where n is number of elements in range.
    template<typename InputIterator>
    PairingPQ(InputIterator start, InputIterator end, COMP_FUNCTOR comp = COMP_FUNCTOR()) :
        BaseClass{ comp } {
        // TODO: Implement this function.
            numNodes = 0;
            root = nullptr;
            while (start != end) {
                push(*start++);
            }

        // These lines are present only so that this provided file compiles.
       
    } // PairingPQ()


    // Description: Copy constructor.
    // Runtime: O(n)
    PairingPQ(const PairingPQ &other) :
        BaseClass{ other.compare } {
        // TODO: Implement this function.
        // NOTE: The structure does not have to be identical to the original,
        //       but it must still be a valid pairing heap.
        //PairingPQ(other.begin(), other.end())
            
            root = nullptr;
            numNodes = 0;
            deque<Node*> tracker;
            if (other.root) { //if not null, execute
                tracker.push_back(other.root);
                
                Node *ptr = nullptr;
                while (!tracker.empty()) {
                    ptr = tracker.front();
                    
                    //child first
                    if (ptr->child) {
                        tracker.push_back(ptr->child);
                    }
                    if (ptr->sibling) {
                        tracker.push_back(ptr->sibling);
                    }
                    push(ptr->elt);
                    
                    tracker.pop_front();
                    //TODO: DEBUG
                }
                
            }
        
            
    } // PairingPQ()


    // Description: Copy assignment operator.
    // Runtime: O(n)
    PairingPQ &operator=(const PairingPQ &rhs) {
        PairingPQ other(rhs);
        swap(root, other.root);
        swap(numNodes, other.numNodes);
        return *this;
    } // operator=()


    // Description: Destructor
    // Runtime: O(n)
    ~PairingPQ() {
/*
        deque<Node*> nodes;

        if (root) {
            Node* node;
            nodes.push_back(root);

            while (!nodes.empty()) {
                node = nodes.front();
                if (node->sibling) {
                    nodes.push_back(node->sibling);
                }
                if (node->child) {
                    nodes.push_back(node->child);
                }

                delete node;
                nodes.pop_front();
                numNodes--;
            }
        }
 */
        if (root) {
               deleteNow(root);
               numNodes = 0;
               root = nullptr;
        }
        
        
        
    } // ~PairingPQ()
    
    //help function added
    void deleteNow(Node* node) {
        if (node) {
            deleteNow(node->child);
            deleteNow(node->sibling);
            delete node;
        }
    }


    // Description: Assumes that all elements inside the pairing heap are out
    //              of order and 'rebuilds' the pairing heap by fixing the
    //              pairing heap invariant. You CANNOT delete 'old' nodes
    //              and create new ones!
    // Runtime: O(n)
    virtual void updatePriorities() {
        // TODO: Implement this function.
        deque<Node*> family;
        Node *ptr = root;
        if (ptr->child) {
            family.push_back(ptr->child);
        }
        ptr->child = nullptr;
        
        while (!family.empty()) {
            ptr = family.front();
            if (ptr->child) {
                family.push_back(ptr->child);
                //pusback child
            }
            if (ptr->sibling) {
                family.push_back(ptr->sibling);
            }
            ptr->parent = nullptr;
            ptr->sibling = nullptr;
            ptr->child = nullptr;
            root = meld(root, ptr);
            family.pop_front();
        }
    } // updatePriorities()


    // Description: Add a new element to the pairing heap. This is already
    //              done. You should implement push functionality entirely in
    //              the addNode() function, and this function calls
    //              addNode().
    // Runtime: O(1)
    virtual void push(const TYPE &val) {
        addNode(val);
       // numNodes++;
    } // push()


    // Description: Remove the most extreme (defined by 'compare') element
    //              from the pairing heap.
    // Note: We will not run tests on your code that would require it to pop
    //       an element when the pairing heap is empty. Though you are
    //       welcome to if you are familiar with them, you do not need to use
    //       exceptions in this project.
    // Runtime: Amortized O(log(n))
    virtual void pop() {
        // TODO: Implement this function.
        deque<Node*> family;
        Node *ptr = root->child;
        
        if (!ptr) {
            delete root;
            root = nullptr;
        }
        else {
            while (ptr) {
                family.push_back(ptr);
                ptr = ptr->sibling;
            }
            while (family.size() > 1) {  //TODO: SWITCH TO >
                ptr = family.front();
                ptr->sibling = nullptr;
                ptr->parent = nullptr;
                family.pop_front();
                family.front()->parent =nullptr;
                family.front()->sibling = nullptr;
                family.push_back(meld(ptr, family.front()));
                family.pop_front();
/*
            Node *one = family.front();
            family.pop_front();
            Node *two = family.front();
            family.pop_front();
            Node *three = meld(one, two);
            family.push_back(three);
 */
            }
            delete root;
            root = family.front();
            family.pop_front();
            //--numNodes; is this running twice?
        }
        --numNodes;
        return;
    } // pop()


    // Description: Return the most extreme (defined by 'compare') element of
    //              the pairing heap. This should be a reference for speed.
    //              It MUST be const because we cannot allow it to be
    //              modified, as that might make it no longer be the most
    //              extreme element.
    // Runtime: O(1)
    virtual const TYPE &top() const {
        // TODO: Implement this function
        return root->elt;
        // These lines are present only so that this provided file compiles.
        //static TYPE temp; // TODO: Delete this line
        //return temp;      // TODO: Delete or change this line
    } // top()


    // Description: Get the number of elements in the pairing heap.
    // Runtime: O(1)
    virtual std::size_t size() const {
        // TODO: Implement this function
        return numNodes; // TODO: Delete or change this line
    } // size()

    // Description: Return true if the pairing heap is empty.
    // Runtime: O(1)
    virtual bool empty() const {
        // TODO: Implement this function
        if (numNodes == 0) {
            return true;
        }
        return false; // TODO: Delete or change this line
    } // empty()


    // Description: Updates the priority of an element already in the pairing
    //              heap by replacing the element refered to by the Node with
    //              new_value. Must maintain pairing heap invariants.
    //
    // PRECONDITION: The new priority, given by 'new_value' must be more
    //               extreme (as defined by comp) than the old priority.
    //
    // Runtime: As discussed in reading material.
    void updateElt(Node* node, const TYPE &new_value) {
        // TODO: Implement this function
        node->elt = new_value;
        if (node->parent) {
            if (this->compare(node->parent->elt, node->elt)) {
                Node *relation = node->parent->child;
                if (relation == node) {
                    node->parent->child = node->sibling;
                }
                else {
                    //Node * ptr = node->parent->sibling;
                    //relocating above pointer, lead to confusion in earlier branches
                    while (node != relation->sibling) {
                        relation = relation->sibling;
                    }
                    relation->sibling = node->sibling;
                    //or was the error cause this wasn't in the while loop?
                    
                }
                node->parent = nullptr;
                node->sibling = nullptr;
                root = meld(root, node);
            }
        }
        //updatePriorities();

        // These lines are present only so that this provided file compiles.
    } // updateElt()


    // Description: Add a new element to the pairing heap. Returns a Node*
    //              corresponding to the newly added element.
    // NOTE: Whenever you create a node, and thus return a Node *, you must
    //       be sure to never move or copy/delete that node in the future,
    //       until it is eliminated by the user calling pop(). Remember this
    //       when you implement updateElt() and updatePriorities().
    // Runtime: O(1)
    Node* addNode(const TYPE &val) {
        // TODO: Implement this function
        numNodes++;
        Node *ptr = new Node(val);
        if (root) {
            root = meld(ptr, root);
        }
        else {
            root = ptr;
        }
        return ptr;
        

        // This line is present only so that this provided file compiles.
    } // addNode()


private:
    // TODO: Add any additional member variables or member functions you
    //       require here.
    uint32_t numNodes;
    Node *root;
    Node *meld(Node *a, Node *b) {
        //b is greater than a
        if (this->compare(a->getElt(), b->getElt())) {
            a->sibling = b->child;
            a->parent = b;
            b->child = a;
            return b;
        }
        else { ///a is greater than b
            b->sibling = a->child;
            b->parent = a;
            a->child = b;
            return a;
        }
    }

    // NOTE: For member variables, you are only allowed to add a "root
    //       pointer" and a "count" of the number of nodes. Anything else
    //       (such as a deque) should be declared inside of member functions
    //       as needed.
};


#endif // PAIRINGPQ_H
