#ifndef pair_h
#define pair_h

//------------------------------------------------------------------------------
//                                  PAIR CLASS
//------------------------------------------------------------------------------

class Pair {
protected:

    int key;
    int value;
    
public:
    
    // Constructors
    
    Pair(int key, int value);
    Pair(const Pair& pair);
    virtual ~Pair() {};

    // Operators

    virtual void operator=(const Pair& pair);
    virtual bool operator==(const Pair& pair) const;
    virtual bool operator>(const Pair& pair) const;
    virtual bool operator<(const Pair& pair) const;
    
    // Handling functions

    void addToValue(int i);
    void multiplyValue(int i);

    // Get/Set functions
    
    int getKey() const;
    int getValue() const;
    void setKey(int key);
    void setValue(int value);
};

//------------------------------------------------------------------------------
//                               END OF PAIR CLASS
//------------------------------------------------------------------------------

#endif /* pair_h */
