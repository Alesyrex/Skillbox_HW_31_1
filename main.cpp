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
    static int count_ptr;
public:
    shared_ptr_toy(std::string name)
    {
        object = new Toy(name);
        ++count_ptr;
    }

    shared_ptr_toy()
    {
        object = new Toy("SomeName");
        ++count_ptr;
    }

    shared_ptr_toy(const shared_ptr_toy& ptr_other)
    {
        object = ptr_other.object;
        ++count_ptr;
    }

    shared_ptr_toy& operator=(const shared_ptr_toy& ptr_other)
    {
        if(this == &ptr_other)
            return *this;
        if(object != nullptr)
            delete object;

        object = new Toy(*ptr_other.object);
        ++count_ptr;
        return *this;
    }

    void reset()
    {
        std::cout << count_ptr << std::endl;
        if (count_ptr != 0)
        {
            --count_ptr;
            if(count_ptr == 0)
                delete object;
        }
        object = nullptr;
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

int shared_ptr_toy::count_ptr = 0;

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
