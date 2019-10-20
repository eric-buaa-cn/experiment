#include <iostream>
#include <memory>

class Investment {
public:
    virtual ~Investment() = default;
};

class Stock : public Investment {
public:
    Stock() = default;
    virtual ~Stock() = default;
};

auto InvestmentDeleter = [](Investment* pInvestment) {
    std::cout << "Delete Investment object:" << pInvestment
        << " by lambda function" << std::endl;
    delete pInvestment;
};

void DeleteInvestment(Investment* pInvestment) {
    std::cout << "Delete Investment object:" << pInvestment
        << " by conventional function" << std::endl;
}

class StatelessDeleteInvestmentFunctor {
public:
    StatelessDeleteInvestmentFunctor() = default;
    
    void operator()(Investment* pInvestment) {
        std::cout << "Delete Investment object:" << pInvestment
            << " by stateless functor" << std::endl;
        delete pInvestment;
    }
};

class StatefulDeleteInvestmentFunctor {
public:
    StatefulDeleteInvestmentFunctor() = default;
    
    void operator()(Investment* pInvestment) {
        std::cout << "Delete Investment object:" << pInvestment
            << " by stateful functor" << std::endl;
        delete pInvestment;
    }
private:
    int value_ = 0;
};

int main() {
    {
        auto pInvestment =
            std::unique_ptr<Investment>(new (std::nothrow) Stock);
        std::cout << "sizeof unique_ptr with default deleter:"
            << sizeof(pInvestment) << std::endl;
    }

    {
        auto pInvestment =
            std::unique_ptr<Investment, decltype(InvestmentDeleter)>(
                new (std::nothrow) Stock, InvestmentDeleter);
        std::cout << "sizeof unique_ptr with lambda deleter:"
            << sizeof(pInvestment) << std::endl;
    }
    
    {
        auto pInvestment =
            std::unique_ptr<Investment, void(*)(Investment*)>(
                new (std::nothrow) Stock, DeleteInvestment);
        std::cout << "sizeof unique_ptr with conventional function:"
            << sizeof(pInvestment) << std::endl;
    }
    
    {
        auto pInvestment =
            std::unique_ptr<Investment, StatelessDeleteInvestmentFunctor>(
                new (std::nothrow) Stock, StatelessDeleteInvestmentFunctor{});
        std::cout << "sizeof unique_ptr with stateless functor:"
            << sizeof(pInvestment) << std::endl;
    }
    
    {
        auto pInvestment =
            std::unique_ptr<Investment, StatefulDeleteInvestmentFunctor>(
                new (std::nothrow) Stock, StatefulDeleteInvestmentFunctor{});
        std::cout << "sizeof unique_ptr with stateful functor:"
            << sizeof(pInvestment) << std::endl;
    }
    return 0;
}
