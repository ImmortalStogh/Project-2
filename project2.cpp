#include <cmath>
#include "iostream"

using namespace std;

const int MAX_NUMBER_BOOKS = 1000;

struct book
{
    string title;
    string author;
    int book_code;
    int year;
    bool is_deleted;
};

char selection();
bool redirection(book[], char);

void InsertRecord(book[]);
void DeleteRecord(book[]);
void UnDeleteRecord(book[]);
void PrintBooks(book[]);
void SearchForBook(book[]);

void print_book(book*, int, bool);

int number_of_books = 0;

int main()
{
    book library[MAX_NUMBER_BOOKS];
    while (true)
    {
        char chosen_option = selection();
        bool should_continue = redirection(library, chosen_option);
        if (!should_continue)
        {
            return 0;
        }
    }
}

char selection()
{
    char option;

    cout << "\n***********************";
    cout << "\nPlease enter a command:";
    cout << "\n'A': Add an entry";
    cout << "\n'D': Delete an entry";
    cout << "\n'U': Undelete an entry";
    cout << "\n'P': Print the books";
    cout << "\n'S': Search in the list";
    cout << "\n'Q': Quit";
    cout << "\n***********************" << endl;

    cout << "\nEnter your option: ";
    cin >> option;
    cin.ignore();
    cout << endl;

    return option;
}

bool redirection(book library[], char selection)
{
    switch (selection)
    {
        case 'A':
            InsertRecord(library);
            break;

        case 'D':
            DeleteRecord(library);
            break;

        case 'U':
            UnDeleteRecord(library);
            break;

        case 'P':
            PrintBooks(library);
            break;

        case 'S':
            SearchForBook(library);
            break;

        case 'Q':
            cout << "Quitting..." << endl;
            return false;

        default:
            cout << "Enter a valid input headass" << endl;
            break;
    }
    return true;
}

void InsertRecord(book library[])
{
    if (number_of_books >= MAX_NUMBER_BOOKS)
    {
        cout << "There cannot be more than " << MAX_NUMBER_BOOKS << " in this library" << endl;
        return;
    }

    book* item = &library[number_of_books];
    cout << "Book #" << number_of_books + 1 << endl;

    cout << "Enter the book title: ";
    getline(cin, item->title);

    cout << "Enter the book's author name: ";
    getline(cin, item->author);

    cout << "Enter the book's code: ";
    cin >> item->book_code;

    cout << "Enter the book's publishing year: ";
    cin >> item->year;

    cout << endl;
    number_of_books++;
}

void DeleteRecord(book library[])
{
    int search_code;
    cout << "Enter the book's code: ";
    cin >> search_code;
    cout << endl;
    for(int i = 0; i < number_of_books; i++)
    {
        book* item = &library[i];
        if(search_code == item->book_code)
        {
            if (item->is_deleted)
            {
                cout << "Book has already been deleted" << endl;
            }
            else {
                item->is_deleted = true;
                cout << "The book has been deleted" << endl;
            }
        }
        else {
            cout << "Book does not exist in library" << endl;
        }
    }
}

void UnDeleteRecord(book library[])
{
    int search_code;
    cout << "Enter the book's code: ";
    cin >> search_code;
    cout << endl;
    for(int i = 0; i < number_of_books; i++)
    {
        book* item = &library[i];
        if(search_code == item->book_code)
        {
            if (!item->is_deleted)
            {
                cout << "Book is not deleted" << endl;
            }
            else {
                item->is_deleted = false;
                cout << "The book has been undeleted" << endl;
            }
        }
        else {
            cout << "Book does not exist in library" << endl;
        }
    }
}

void PrintBooks(book library[])
{
    for(int i = 0; i < number_of_books; i++)
    {
        // Does not print deleted books
        print_book(library, i, true);
    }
}

void print_book(book library[], int index, bool only_print_undeleted_books)
{
    book* item = &library[index];

    if (item->is_deleted && only_print_undeleted_books)
    {
        return;
    }

    cout << "\n*********************************************";
    cout << "\nBook #" << index + 1;
    cout << "\nTitle: " << item->title;
    cout << "\nAuthor: " << item->author ;
    cout << "\nCode: " << item->book_code;
    cout << "\nPublishing year: " << item->year;
    if (!only_print_undeleted_books)
    {
        if (item->is_deleted)
        {
            cout << "\nDeleted: true";
        }
        else {
            cout << "\nDeleted: false";
        }
    }
    cout << endl;
}

void SearchForBook(book library[])
{
    int search_code;
    cout << "Enter the book's code: ";
    cin >> search_code;
    cout << endl;

    for(int i = 0; i < number_of_books; i++)
    {
        book* item = &library[i];
        if(search_code == item->book_code)
        {
            // Prints book even if it is deleted
            print_book(library, i, false);
        }
        else {
            cout << "Book does not exist in library" << endl;
        }
    }
}