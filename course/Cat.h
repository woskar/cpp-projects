#ifndef CAT_H
#define CAT_H

#include <iostream>
#include <string>

class Cat{

private:
    std::string name_;
    int age_;
    bool happy_;
    static int number_of_lives;


public:
    // Default Constructor
    Cat()
    : name_("Ninja-cat")
    , age_(0)
    , happy_(true)
    {
        std::cout << "Cat created with default constructor at " << this << std::endl;
    }

    // Full equipped Constructor
    Cat(std::string newName, int newAge, bool mood)
    : name_(newName)
    , age_(newAge)
    , happy_(mood)
    {
        std::cout << "Cat Created with full constructor" << std::endl;
    }

    // Copy Constructor, this impolementation overrides default
    Cat(const Cat & other)
    : name_(other.name_)
    , age_(other.age_)
    , happy_(other.happy_)
    {
        std::cout << "Cat " << name_ <<" created by copying." << std::endl;
    }

    // Destructor, this overrides default as well
    ~Cat(){
        std::cout << "Cat " << name_ << " destroyed by destructor." << std::endl;
    }

    void setName(std::string newName){
        this->name_ = newName;
    }

    void setAge(int newAge){
        this->age_ = newAge;
    }

    void makeHappy()
    {
        happy_ = true;
    }

    std::string getName() const
    {
        return name_;
    }

    void speak() const {
        std::cout << "Meouwww says "<< name_ << " in "<< this << std::endl;
    }

    void jump() const {
        std::cout << "Jumping on top of bookcase" << std::endl;
    }

    std::string to_string() const
    {
        std::string mood;
        if (happy_) mood = "happy";
        else mood = "sad";

        return "Cat " + name_ + " is " + std::to_string(age_) +
        " years old and " + mood + ".";

    }

    static void showLives()
    {
        std::cout << number_of_lives << " Lives"<< std::endl;
    }
};

// Create Method that returns a pointer to a new cat
// Advantage of *: only pointer gets copied, not Cat itself.
Cat * createCat()
{
    Cat * pointerCat = new Cat();
    pointerCat->setName("Bertie");
    return pointerCat;
}

class WildCat: public Cat
{
public:

    WildCat()
    {
        std::cout << "Empty WildCat constructor called"<< std::endl;
    }

    WildCat(std::string name, int age, bool mood): Cat(name, age, mood)
    {
        std::cout << "Full WildCat constructor called"<< std::endl;
    }

    void run()
    {
        std::cout << "WildCat running away!" << std::endl;
    }
};

#endif
