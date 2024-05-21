#pragma once

#include <functional>
#include <iostream>
#include <utility>
#include <vector>

namespace test {

class test {
public:
    test() {}
    virtual ~test() = default;

public:
    virtual void onUpdate(float deltaTime) {}
    virtual void onRender() {}
    virtual void onImGuiRender() {}
};

class testMenu: public test {
public:
    testMenu(test *&currenttestPointer): _current(currenttestPointer) {};
    ~testMenu() {};
public:
    void onUpdate(float deltaTime) override;
    void onRender() override;
    void onImGuiRender() override;
public:
    template<typename T>
    void registerTest(const std::string &name) {
        std::cout << "Registering Test" << name << std::endl;
        _listTest.push_back(std::make_pair(name, [](){return new T;}));
    }
private:
    test *&_current;
    std::vector<std::pair<std::string, std::function<test *()>>> _listTest;
};

}