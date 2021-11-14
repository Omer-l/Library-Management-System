#ifndef Book_h
#define Book_h

class Book
{
    private:
        std::string title;
        std::string author;
        std::string isbn;
        std::string qty_available;
    public:
        Book()
        {

        }

        Book(std::string title, std::string author, std::string isbn, std::string qty_available)
        {
            this->title = title;
            this->author = author;
            this->isbn = isbn;
            this->qty_available = qty_available;
        }

        void toString()
        {
            if(getTitle() != "")
            {
                std::cout << std::endl << "TITLE:      " << this->title << std::endl  << "AUTHOR(S):  " << this->author << std::endl << "ISBN:       " << this->isbn << std::endl << "QTY:        " << this->qty_available << std::endl;
            }
        }

        std::string getTitle()
        {
            return this->title;
        }

        int getQty()
        {
            return atoi(this->qty_available.c_str());
        }

        void setQty(int qty)
        {
            std::stringstream tmp;
            tmp << "" << qty;
            this->qty_available = tmp.str();
        }

        void damagedBook()
        {
            std::stringstream tmp;
            tmp << "" << (atoi(qty_available.c_str()) - 1);
            this->qty_available = tmp.str();
        }

};

bool isISBNvalid(std::string isbn_number)
{
    int n = (int)isbn_number.length();

    if (n != 13)
    {
        return false;
    }
    //sum of digits individually
    int sum = 0;
    //loop through the first 12 digits
    for(int i = 0; i <= 12; i++)
    {
        int value = isbn_number[i] - '0';
        if(0 > value || 10 < value)
        {
            return false;
        }
        if((i+1) % 2 != 0)
        {
            sum += value;
        } else
        {
            sum += (value * 3);
        }
    }
    //is isbn divisible by 10?
    return (sum % 10 == 0 && isbn_number[0] == '9');
}

bool isQtyDigit(std::string qty_available)
{
    if(qty_available.empty())
        return false;
    
    for(char &c : qty_available)
    {
        if(std::isdigit(c) == 0 || qty_available.empty())
        {
            return false;
        }
    }
    return true;
}

bool isTitleFirstLetterCapital(std::string title)
{
    if((title[0] > 96 && title[0] < 123) || title.empty())
    {
        return false;
    }
    return true;
}

#endif
