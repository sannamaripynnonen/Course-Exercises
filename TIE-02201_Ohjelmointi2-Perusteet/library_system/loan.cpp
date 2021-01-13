#include "loan.hh"

Loan::Loan(Book* book, Person* loaner, Date* date) :
    book_(book), loaner_(loaner),
    loan_date_(new Date(date->getDay(), date->getMonth(), date->getYear())),
    due_date_(new Date(date->getDay(), date->getMonth(), date->getYear())),
    today_(date)
{
    renewals_left_=DEFAULT_RENEWAL_AMOUNT,
    due_date_->advance_by_loan_length();

}

Loan::~Loan()
{
    delete loan_date_;
    loan_date_ = nullptr;
    delete due_date_;
    due_date_ = nullptr;
}

Book *Loan::getBook()
{
    return book_;
}

Person *Loan::getPerson()
{
    return loaner_;
}

Date *Loan::getDate()
{
    return due_date_;
}

bool Loan::is_late()
{
    if (today_->operator <(due_date_)){
        return false;
    }
    else{
        return true;
    }
}

bool Loan::can_renew()
{
    if(renewals_left_> 0){
        return true;
    }
    else{
        return false;
    }
}

void Loan::print_all_loan_info()
{
    std::cout << book_->get_title() << " : " << loaner_->get_name() << " : " <<
                 due_date_->to_string() << " : " << is_late() << std::endl;
}

void Loan::print_loan_info()
{
    std::cout << book_->get_title() << " : " << due_date_->to_string() <<
                 " : " << is_late() << std::endl;

}

void Loan::renewal()
{
    --renewals_left_;
}


