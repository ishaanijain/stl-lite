/*
We are giving you guiding comments to help you fill out this header file.
The indentation of the comments serve as hints to how your code is structured. 

These are HINTS. PLEASE READ THE README.
Anything not specified here will be in the README.
For example, some functions may be const versions while others may not.
Some functions may throw exceptions while others are noexcept.
*/

/* Preprocessor directives. Guard the header file upon include */

/*
Which include directives should you put here?
(hint: we may throw VectorExceptions. We also want to use ostream)
*/


/*
Templated Vector class definition with templated Iterator class member
The template type name can be T
*/



/* Begin by specifying private members of Vector */

    /* We want to nest the Iterator class definition right here */


    /* Write out the private members of Iterator */

        /* there should be an m_container and an index */



    /* Here are our your public members of Iterator*/

        /* Write your constructors here */



        /* Write your operator overloads here.*/
        /* Post and pre increment and decrement operators*/









        /* Overloaded += size_t operator */









        /* Overloaded -= size_t operator */








        /* Overloaded - operator. The right hand side is a const Iterator& */










        /* Overloaded - operator.  The right hand side is a size_t */









        /* Overloaded == operator. The right hand side is a const Iterator& */




        /* Overloaded != operator. The right hand side is const Iterator& */


        /* Overloaded star (*) operator to dereference. This returns a T& */


        /* Overloaded -> operator. This returns a T* */


        /*
        It is correct to add a size_t to an Iterator.
        What keyword should you use to specify these next two overloads? (It's in the README)
        Remember, using + on Iterators is commutative.
        1 + Iterator and Iterator + 1 both return an Iterator that is one forward.
        */






















    /* Specify your private Vector member fields. There should be three */



/* You will define your public Vector members here*/

    /* Default constructor */


    /* An overloaded constructor (see README) */



    /* The begin() function */


    /* The const version of begin(). Note: it returns a const T* type */


    /* The empty() function */


    /* The end() function */




    /* The const version of end(). Note: it returns a const T* */





    /* The front() function */




    /* The const version of front(). Note it returns a const T& this is different from begin()! */




    /* The back() function */




    /* The const version of back(). Note: it returns a const T& */




    /* The push_back() function */









    /* The push_back function that takes an RValue reference (Type of T&&) */









    /* The pop_back() function*/








    /* The capacity() function */


    /* The size() function */


    /* The data() function. Returns type T* */


    /* The const version of data(). Returns type const T* */


    /* 
    The erase function. It takes in a start and end Iterator
    Hints for implementation:
        0 1 2 3 4 5
    We want to delete 1 2 3 4
        0    1    2    3    4    5
             ^start         ^end
    Replace what is at start with what is at end and advance start and end until it reaches the vec.end()
        0    4    2    3    4    5
                  ^s             ^e
        0    4    2    5    4    5
                       ^s            e=vec.end()
    Is anything after what s is now including s used?
    Hint: resize the vector to include only 0 4 2. You will implement resize anyways.
    */











    /* swap_elements(). Takes two iterators. Use std::move ! */






    /* Subscript operator[] overload */


    /* Const version of the subscript operator[] overload */


    /* 
    Overloaded == operator. The right hand side is another const<T>& vector.
    Make sure the sizes of the vectors are equal
    Also check the elements inside are equal.
    */











    /* Overloaded != operator. */


    /* Vector copy constructor. Does a deep copy! */







    /* 
    Vector assignment operator.
    Make sure you don't leak memory here. 
    */









    /* at() function. */









    /* const version of at() */









    /* 
    operator<< 
    We want to write code that can write Vectors to an output stream
    like std::cout << v << std::endl;
    You should use the friend keyword somewhere in here. 
    */






    /*
    Vector resize() function here.
    Allocate a new buffer to move all the old elements from the old one to.
    And then assign that new buffer to the `this`
    Make sure to use std::move() to move data from the old buffer to the new one.
    Make sure you don't leak memory!
    */




















    /*
    clear() function. Make sure the destructor of each element gets called.
    delete[] will automatically do this. 
    But there other ways of implementing this function.
    */






    /* Move constructor here */







    /* 
    Move assignment here
    Make sure there are not memory leaks!
    */









    
    /* The Vector destructor goes here. Make sure there are no leaks */

/* 
And we are finished with this header file! 
If you used an #ifndef #define, what should you add at the very end?
*/
