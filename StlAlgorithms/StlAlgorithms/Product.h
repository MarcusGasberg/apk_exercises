#pragma once
#include <string>
#include <utility>
#include <vector>

class Product
{
public:
    Product(std::string name, float price, unsigned int sold = 0)
        : name_(std::move(name)), price_(price), sold_(sold)
    {}
    Product()
        : name_(""), price_(0), sold_(0)
    {}

    const std::string& name() const
    {
        return name_;
    }

    float price() const
    {
        return price_;
    }

    void set_price(float new_price)
    {
        price_ = new_price;
    }

    unsigned int sold() const
    {
        return sold_;
    }

    friend std::istream& operator>> (std::istream& i, Product& p)
    {
        return i >> p.name_ >> p.price_ >> p.sold_;
    }
	
    friend std::ostream& operator<< (std::ostream& o, const Product& p)
    {
        return o << p.name_ << " " << p.price_ << " " << p.sold_;
    }

private:
    std::string   name_;
    float         price_;
    int           sold_;
};
typedef std::vector<Product>  ProductList;