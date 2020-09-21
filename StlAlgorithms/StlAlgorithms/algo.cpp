/*****************************************/
/* Copyright: DevelEdu 2013              */
/* Author: sha                           */
/*****************************************/

#include <fstream>
#include <iostream>
#include <iterator>

#include <algorithm>
#include <numeric>
#include <functional>
#include <sstream>
#include <vector>
#include <string>

#include "Product.h"


constexpr auto PRODUCT_DB_FILE = "product.db";



/**
 * Read products from file
 */
void product_db_read(ProductList& products, const std::string& file_name)
{
    products.clear();
    std::ifstream product_file(file_name.c_str());
    if(!product_file.good())
    {
        std::stringstream s;
        std::cout << "File not found: " << file_name << std::endl;
        return;
    }
	
    const std::istream_iterator<Product> begin_file(product_file);
    const std::istream_iterator<Product> eof;
    std::copy(begin_file, eof, std::back_inserter(products));
}


/**
 * Printout all products
 */
void print_all(const ProductList& products)
{
    std::cout << "##################################################" << std::endl;
    std::cout << "Printing out all products..." << std::endl;
    std::cout << "----------------------------" << std::endl;

    const std::ostream_iterator<Product> product_out(std::cout, "\r\n");
    std::copy(products.begin(), products.end(), product_out);
    std::cout << "##################################################" << std::endl;
}



/**
   Add item
*/
void add_item(ProductList& pl)
{
    Product to_add;
    std::cin >> to_add;
    pl.push_back(to_add);
}


/**
   Write data to db file
*/
void product_db_write(const ProductList& products, const std::string& file_name)
{
	std::ofstream product_file(file_name.c_str());
    if (!product_file.good())
    {
        std::stringstream s;
        std::cout << "File not found: " << file_name << std::endl;
        return;
    }

    const std::ostream_iterator<Product> file_iterator(product_file);
	
    std::copy(products.begin(), products.end(), file_iterator);
}


/**
 * Print poorly selling products
 */
void print_poorly_selling_products(const ProductList& products)
{
	const std::ostream_iterator<Product> product_out(std::cout, "\r\n");
    std::remove_copy_if(products.begin(), products.end(), product_out, [](const Product& p) { return p.sold() > 10; });
}


/**
 * Set a discount on all products - Using for_each()
 */
void add_discount_using_for_each(ProductList& products)
{
    std::for_each(products.begin(), products.end(), [](Product& p) { p.set_price(p.price() * 0.9f); });
}


/**
 * Set a discount on all products - Using transform()
 */
void add_discount_using_transform(
    ProductList& products)
{
    const std::ostream_iterator<Product> product_out(std::cout, "\r\n");
    
    auto get_discount = []()
    {
        float discount;
        std::cout << "Specify discount af float: ";
        std::cin >> discount;
        discount = std::clamp(discount,.1f, .9f);
        return [discount](Product& p1) mutable {  p1.set_price(p1.price() * discount); return p1; };
    };
    std::transform(products.begin(), products.end(), product_out, get_discount());
}


/**
 * Calculate the total amount of sold products
 */
void calc_total_sold_products(const ProductList& products)
{
	const auto sold_total = std::accumulate(products.begin(), products.end(), 0, [](auto total, const Product& p) { return total + p.sold(); });
    std::cout << "Amount sold: " << sold_total << std::endl;
}


/**
 * Setting discount using bind2nd - OPTIONAL
 */


int main()
{
    bool        running = true;
    ProductList pl;

    while (running)
    {
        char choice;

        std::cout << "********************" << std::endl;
        std::cout << "Help menu: " << std::endl;
        std::cout << "'1' Read product database" << std::endl;
        std::cout << "'2' Print all items" << std::endl;
        std::cout << "'3' Add item" << std::endl;
        std::cout << "'4' Write product database" << std::endl;
        std::cout << "'5' Print poorly selling products" << std::endl;
        std::cout << "'6' Set a discount on all products (using for_each() )" << std::endl;
        std::cout << "'7' Set a discount on all products (using transform() )" << std::endl;
        std::cout << "'8' Calculate the total amount of sold products" << std::endl;


        std::cout << "'q' Quit" << std::endl;
        std::cout << "Your choice: ";
        std::cin >> choice;

        switch (choice)
        {
        case '1':
            product_db_read(pl, PRODUCT_DB_FILE);
            break;

        case '2':
            print_all(pl);
            break;

        case '3':
            add_item(pl);
            break;

        case '4':
            product_db_write(pl, PRODUCT_DB_FILE);
            break;

        case '5':
            print_poorly_selling_products(pl);
            break;

        case '6':
            add_discount_using_for_each(pl);
            break;

        case '7':
            add_discount_using_transform(pl);
            break;

        case '8':
            calc_total_sold_products(pl);
            break;

        case 'q':
        case 'Q':
            running = false;
        }


    }
}
