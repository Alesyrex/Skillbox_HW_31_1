#include <iostream>
#include <string>

class Toy
{
    std::string name;
public:
    Toy(std::string _name) : name(_name) {}
    Toy() : Toy("SomeToy") {}
    std::string getName() {return name;}
};

class shared_ptr_toy
{
    Toy* object = nullptr;
    int* count_ptr = nullptr;
public:
    shared_ptr_toy(std::string name)
    {
        object = new Toy(name);
        count_ptr = new int(1);
    }

    shared_ptr_toy()
    {
        object = new Toy("SomeName");
        count_ptr = new int(1);
    }

    shared_ptr_toy(const shared_ptr_toy& ptr_other)
    {
        object = ptr_other.object;
        count_ptr = ptr_other.count_ptr;
        ++(*count_ptr);
    }

    shared_ptr_toy& operator=(const shared_ptr_toy& ptr_other)
    {
        if(this == &ptr_other)
            return *this;
        reset();

        object = ptr_other.object;
        count_ptr = ptr_other.count_ptr;
        ++(*count_ptr);
        return *this;
    }

    void reset()
    {
        if (object != nullptr)
        {
            --(*count_ptr);
            if(*count_ptr == 0)
            {
                delete object;
                delete count_ptr;
            }
        }
        object = nullptr;
        count_ptr = nullptr;
    }

    ~shared_ptr_toy()
    {
        reset();
    }

    std::string get_name_toy()
    {
        return object->getName();
    }
};

shared_ptr_toy make_shared(std::string name)
{
    shared_ptr_toy toy(name);
    return toy;
}

shared_ptr_toy make_shared(const shared_ptr_toy& ptr_other)
{
    shared_ptr_toy toy(ptr_other);
    return toy;
}

int main() {

    shared_ptr_toy A = make_shared("Ball");
    shared_ptr_toy B = make_shared(A);
    shared_ptr_toy C = make_shared("Bone");

    std::cout << A.get_name_toy() << " " << B.get_name_toy() << " " << C.get_name_toy() << std::endl;

    C.reset();
    shared_ptr_toy D = make_shared(B);
    return 0;
}
