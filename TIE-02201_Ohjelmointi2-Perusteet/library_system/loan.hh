/* Module: Loan
 * ------------
 * Represents a single loan in the library.
 * ---------------
 * Sannamari Pynnönen
 * sannamari.pynnonen@tuni.fi
 * 245380
 * ---------------
 * TIE-0220x S2019
 * */
#ifndef LOAN_HH
#define LOAN_HH

#include <string>
#include <vector>
#include <iostream>

#include <date.hh>
#include <book.hh>
#include <person.hh>
#include <library.hh>

const int DEFAULT_RENEWAL_AMOUNT = 6;

class Book;
class Person;
class Date;

class Loan
{
public:
    // Constructor
    Loan(Book* book, Person* loaner, Date* date);
    ~Loan();

    // Self-descriptive getters.
    Book* getBook();
    Person* getPerson();
    Date* getDate();

    // Checks if loaned book is late.
    bool is_late();

    // Checks if loan can be renewed.
    bool can_renew();

    // Prints loan info of all loaned books.
    void print_all_loan_info();

    // Prints loan info with book title, due date and if book is late.
    void print_loan_info();

    // Decreases amount of renewals left.
    void renewal();


private:
    Book* book_;
    Person* loaner_;
    Date* loan_date_;
    Date* due_date_;

    // Pointer to today's date.
    Date* today_;

    int renewals_left_;
};

#endif // LOAN_HH
