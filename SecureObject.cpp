#include <iostream>
#include <string>
#include <string.h>


/*! \class SecureKey<T>
 *  \brief Template used to create a secure key
 */
template<unsigned T>
class SecureKey
{
public:

    SecureKey<T>(): valid(false), size(T)
    {
        memset(key, 0x00, size);
        std::cout << "SECURE KEY CONSTRUCTOR" << std::endl;
    }

    SecureKey<T>(const SecureKey<T>& object)
    {
        memcpy(this->key, (const uint8_t *)object, object.getSize());
        this->valid = object.isValid();
        this->size = object.getSize();
        std::cout << "SECURE KEY COPY CONSTRUCTOR" << std::endl;
    }


    SecureKey<T>(SecureKey<T>&& object)
    {
        memcpy(this->key, object(), object.getSize());
        this->valid = object.isValid();
        this->size = object.getSize();
        std::cout << "SECURE KEY MOVE CONSTRUCTOR" << std::endl;
    }


    ~SecureKey<T>()
    {
        memset(key, 0, size);
        std::cout << "SECURE KEY DESTRUCTOR" << std::endl;
    }

    /*!
     *  \brief operator() Overwrite operator function call
     *  \param[in] None
     *  \param[in,out] None
     *  \param[out] None
     */
    uint8_t* operator()() { return key; }

    operator uint8_t *() { return key; }
    operator const uint8_t *() const { return key; }

    uint8_t * getKey() const { return key; }
    constexpr unsigned getSize() const { return size; }
    constexpr bool isValid() const { return valid; }


    void print()
    {
        std::cout << "PRINT INTERNAL KEY " << size << " : " << std::endl;

        for (unsigned idx = 0; idx < size; idx++)
        {
            printf("%2X, ", key[idx]);
        }

        std::cout << std::endl;
    }


private:
    uint8_t key[T];
    bool valid;
    unsigned size;
};


/*! \class SecureObject<T>
 *  \brief Template used to handle a secure object
 */
template<typename T>
class SecureObject
{
public:

    /*!
     *  \brief Default constructor is deleted
     *  \note THIS IS NOT NECCESSARY
     */
    SecureObject<T>() = delete;

    /*! \fn SecureObject<T>
     *  \brief Constructor of the secure object
     */
    SecureObject<T>(const T& obj): object{obj}
    {
        std::cout << "SECURE OBJECT COPY CONSTRUCTOR" << std::endl;
    }

    SecureObject<T>(T&& obj): object{std::move(obj)}
    {
        std::cout << "SECURE OBJECT MOVE CONSTRUCTOR" << std::endl;
    }


    /*! \fn ~SecureObject<T>
     *  \brief Destructor of the secure object
     */
    virtual ~SecureObject<T>()
    {
        std::cout << "SECURE OBJECT DESTRUCTOR" << std::endl;
    }

    /*! \fn Operator function call()
     *  \brief Operator function call
     *  \return T object secure stored.
     */
    T& operator ()()
    {
        return object;
    }

    void print()
    {
        std::cout << "FORCE TO SHOW A TRACE" << std::endl;
    }


private:
    T object;
};

int main(int argc, char *argv[])
{
    SecureObject<int> secInt(0);
    const SecureKey<32> eccKey;
    SecureObject<SecureKey<32>> _secKey{eccKey};
    SecureObject<SecureKey<32>> secKey{SecureKey<32>()};

    std::cout << "SECURE INTEGER WITH VALUE: " << secInt() << std::endl;

    /*! Access to key trough the function call operator. */
    secKey().print();
    secKey()()[0] = 5;
    secKey().print();

    return 0;
}

