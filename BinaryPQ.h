// Project identifier: 43DE0E0C4C76BFAA6D8C2F5AEAE0518A9C42CF4E

#ifndef BINARYPQ_H
#define BINARYPQ_H


#include <algorithm>
#include "Eecs281PQ.h"
using namespace std;

// A specialized version of the priority queue ADT implemented as a binary
// heap.
template<typename TYPE, typename COMP_FUNCTOR = std::less<TYPE>>
class BinaryPQ : public Eecs281PQ<TYPE, COMP_FUNCTOR> {
    // This is a way to refer to the base class object.
    using BaseClass = Eecs281PQ<TYPE, COMP_FUNCTOR>;

public:
    // Description: Construct an empty PQ with an optional comparison functor.
    // Runtime: O(1)
    explicit BinaryPQ(COMP_FUNCTOR comp = COMP_FUNCTOR()) :
        BaseClass{ comp } {
        // TODO: DONE
    } // BinaryPQ


    // Description: Construct a PQ out of an iterator range with an optional
    //              comparison functor.
    // Runtime: O(n) where n is number of elements in range.
    template<typename InputIterator>
    BinaryPQ(InputIterator start, InputIterator end, COMP_FUNCTOR comp = COMP_FUNCTOR()) :
        BaseClass{ comp } {
        // TODO: DONE
            data.reserve(distance(start, end));
            while (start != end) {
                push(*start);
                start++;
            }
            updatePriorities();

        // These lines are present only so that this provided file compiles.
    
    } // BinaryPQ


    // Description: Destructor doesn't need any code, the data vector will
    //              be destroyed automatically.
    virtual ~BinaryPQ() {
    } // ~BinaryPQ()


    // Description: Assumes that all elements inside the heap are out of
    //              order and 'rebuilds' the heap by fixing the heap
    //              invariant.
    // Runtime: O(n)
    virtual void updatePriorities() {
        // TODO: Implement this function.
        if (data.empty()) {
            return;
        }
        
            for (int x = int(size() - 1); x >= 0; x--) {
                fixDown(x);
            }
        
    } // updatePriorities()


    // Description: Add a new element to the PQ.
    // Runtime: O(log(n))
    virtual void push(const TYPE &val) {
        // TODO: DONE
        data.push_back(val);
        if (data.size() > 1) {
            fixUp(data.size() - 1); //always 1 right?
        }

        // This line is present only so that this provided file compiles.
    } // push()


    // Description: Remove the most extreme (defined by 'compare') element
    //              from the PQ.
    // Note: We will not run tests on your code that would require it to pop
    //       an element when the PQ is empty. Though you are welcome to if
    //       you are familiar with them, you do not need to use exceptions in
    //       this project.
    // Runtime: O(log(n))
    virtual void pop() {
        // TODO: DONE
        /*
        if (empty()) {
            return;
        }
        
        const size_t last = size() - 1;
        //swap(data.back(), data.front());
        swap(data[0], data[last]);
        data.pop_back();

        if (empty()) {
            return;
        }
        
            fixDown(0);  //alwasy 1
         */
        
        swap(data.front(), data.back());
        data.pop_back();
        if (data.size() > 1) {
            uint32_t zero = 0;
            fixDown(zero);
        }
        
            //index here is 0 cuz we are fixing from the top element
    } // pop()


    // Description: Return the most extreme (defined by 'compare') element of
    //              the PQ. This should be a reference for speed. It MUST
    //              be const because we cannot allow it to be modified, as
    //              that might make it no longer be the most extreme element.
    // Runtime: O(1)
    virtual const TYPE &top() const {
        // TODO: Implement this function.

        // These lines are present only so that this provided file compiles.
        return data.front();
    } // top()


    // Description: Get the number of elements in the PQ.
    // Runtime: O(1)
    virtual std::size_t size() const {
        // TODO: Implement this function. Might be very simple,
        // depending on your implementation.
       
        return data.size();
    } // size()


    // Description: Return true if the PQ is empty.
    // Runtime: O(1)
    // TODO: DONE
    virtual bool empty() const {
        return data.empty();
    } // empty()
    
    
    // Translate 1-based indexing into a 0-based vector
    TYPE &getElement(std::size_t i) {
      return data[i - 1];
    }  // getElement()


    const TYPE &getElement(std::size_t i) const {
      return data[i - 1];
    }  // getElement()

    


private:
    // Note: This vector *must* be used for your PQ implementation.
    std::vector<TYPE> data;
    // NOTE: You are not allowed to add any member variables. You don't need
    //       a "heapSize", since you can call your own size() member
    //       function, or check data.size().

    // TODO: Add any additional member functions you require here. For
    //       instance, you might add fixUp() and fixDown().
    void fixDown(size_t index) {
        while (2 * index < size() - 1) {
            size_t temp = 2 * index;
            if (temp < data.size() && this->compare(data[temp], data[temp + 1])) {
                ++temp;
            }
            if (!this->compare(data[index], data[temp])) {
                return;
            }
            swap(data[index], data[temp]);
            index = temp;
        }
    }
    
    
    void fixUp(size_t index) {
        
        while (index > 0 && this->compare(data[index / 2], data[index])) {
            //i think index needs to go first or it can cause an error with bad access
            swap(data[index / 2], data[index]);
            index = index / 2;
        }
         /*
        
        size_t spotter = (index - 1) / 2;
        while (index > 0 && this->compare(data[index], data[spotter])) {
            swap(data[index], data[spotter]);
            index = spotter;
            spotter = (index - 1) / 2;
        }
          */
    }
    
    
    
}; // BinaryPQ


#endif // BINARYPQ_H
