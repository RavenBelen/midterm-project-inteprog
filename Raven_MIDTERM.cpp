//Raven Joseph Belen
//IT2B
//MIDTERMS

#include <iostream>
#include <string>
#include <limits>
#include <cctype>
#include <iomanip>
using namespace std;

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define YELLOW  "\033[33m"
#define MAGENTA "\033[35m"
#define GREEN "\033[32m"
#define PINK "\033[38;5;206m"
#define ORANGE "\033[38;5;214m"


class Book {
private:
    string id, isbn, title, author, edition, publication, category;

public:
    Book() {}
    void setBook(string _id, string _isbn, string _title, string _author, string _edition, string _publication, string _category) {
        id = _id;
        isbn = _isbn;
        title = _title;
        author = _author;
        edition = _edition;
        publication = _publication;
        category = _category;
    }
    string getId() 
	{ 
		return id; 
	}
	
    string getCategory() 
	{ 
		return category; 
	}
	
    void displayBook() 
	{
	    cout << "| " << setw(10) << left << id
	         << "| " << setw(10) << left << isbn
	         << "| " << setw(20) << left << title
	         << "| " << setw(15) << left << author
	         << "| " << setw(7) << left << edition
	         << "| " << setw(16) << left << publication
	         << "| " << setw(12) << left << category
	         << " |" << endl;
	}
    void editBook(string _isbn, string _title, string _author, string _edition, string _publication) {
        isbn = _isbn;
        title = _title;
        author = _author;
        edition = _edition;
        publication = _publication;
    }
};

bool isValidId(const string &id) 
	{
	    for (char c : id) {
	        if (!isalnum(c)) return false; 
	    }
	    return true;
	}
	
	bool isValidISBN(const string &isbn) {
	    for (char c : isbn) {
	        if (!isalnum(c)) return false; 
	    }
	    return !isbn.empty();
	}
	
	bool isValidAuthor(const string &author) {
	    for (char c : author) {
	        if (!isalpha(c) && c != ' ') return false; 
	    }
	    return !author.empty();
	}
	
	bool isValidEdition(const string &edition) {
	    for (char c : edition) {
	        if (!isalnum(c) && c != ' ') return false;
	    }
	    return !edition.empty();
	}
	
	bool isValidPublication(const string &publication) {
	    for (char c : publication) {
	        if (!isalnum(c) && c != ' ') return false;
	    }
	    return !publication.empty();
	}

class Library {
private:
    Book* books = nullptr;
    int bookCount = 0;
    int bookCapacity = 10;
    string categories[2] = {"Fiction", "Non-fiction"};

public:
    Library() {
        books = new Book[bookCapacity];
    }
    
    ~Library() 
	{
    if (books) {
        delete[] books;
        books = nullptr;
    }
}
    
    void resizeArray() {
        bookCapacity *= 10;
        Book* newBooks = new Book[bookCapacity];
        for (int i = 0; i < bookCount; i++) {
            newBooks[i] = books[i];
        }
        delete[] books;
        books = newBooks;
    }
    
    bool isValidCategory(string category) 
	{
    	for (char &c : category) c = toupper(c); // Convert entire string to uppercase
    	return (category == "FICTION" || category == "NON-FICTION"); // Only accept exact matches
	}

    
    bool isDuplicateId(string id) {
        for (int i = 0; i < bookCount; i++) {
            if (books[i].getId() == id)
                return true;
        }
        return false;
    }
    
    int getBookCount() { return bookCount; }
    
    void addBook() {
    if (bookCount >= bookCapacity) {
        resizeArray();
    }

    string id, isbn, title, author, edition, publication, category;

    // Category Validation
    do {
        cout << YELLOW << "Enter Category (Fiction/Non-fiction): ";
        getline(cin, category);
        if (!isValidCategory(category)) {
            cout << RED << "Invalid category! Choose Fiction or Non-fiction.\n" << RESET;
        }
    } while (!isValidCategory(category));

    // ID Validation
    do {
        cout << ORANGE << "Enter Book ID: ";
        getline(cin, id);
        for (char &c : id) c = toupper(c); // Convert to uppercase
        if (!isValidId(id)) {
            cout << RED << "Invalid ID! Use alphanumeric characters (no spaces or symbols).\n" << RESET;
        } else if (isDuplicateId(id)) {
            cout << RED << "Duplicate ID! Try again.\n" << RESET;
        }
    } while (!isValidId(id) || isDuplicateId(id));

    // ISBN Validation
    do {
        cout << YELLOW << "Enter ISBN: ";
        getline(cin, isbn);
        if (!isValidISBN(isbn)) {
            cout << RED << "Invalid ISBN! Use only digits (no decimals or symbols).\n" << RESET;
        }
    } while (!isValidISBN(isbn));

    // Title Input
    cout << ORANGE << "Enter Title: ";
    getline(cin, title);

    // Author Validation
    do {
        cout << YELLOW << "Enter Author: ";
        getline(cin, author);
        if (!isValidAuthor(author)) {
            cout << RED << "Invalid author name! Use only letters and spaces.\n" << RESET;
        }
    } while (!isValidAuthor(author));

    // Edition Validation
	do {
	    cout << ORANGE << "Enter Edition: ";
	    getline(cin, edition);
	    if (!isValidEdition(edition)) {
	        cout << RED << "Invalid Edition! Use only letters, numbers, and spaces (no symbols like ;, #, or @).\n" << RESET;
	    }
	} while (!isValidEdition(edition));
	
	// Publication Validation
	do {
	    cout << YELLOW << "Enter Publication: ";
	    getline(cin, publication);
	    if (!isValidPublication(publication)) {
	        cout << RED << "Invalid Publication! Use only letters, numbers, and spaces.\n" << RESET;
	    }
	} while (!isValidPublication(publication));


    books[bookCount].setBook(id, isbn, title, author, edition, publication, category);
    bookCount++;
    cout << GREEN << "Book added successfully!\n" << RESET <<endl;
}


	
void editBook() 
{
    if (bookCount == 0) {
        cout << RED << "No Book in the Inventory\n" << RESET << endl;
        return;
    }

    string id;
    cout << "Enter Book ID to edit: ";
    cin >> id;
    cin.ignore(); 

    for (char &c : id) c = toupper(c); 

    bool found = false; 

    for (int i = 0; i < bookCount; i++) {
        if (books[i].getId() == id) {
            found = true;  

            string isbn, title, author, edition, publication;

            // ISBN Validation
            do {
                cout<< YELLOW << "Enter new ISBN: ";
                getline(cin, isbn);
                if (!isValidISBN(isbn)) {
                    cout << RED << "Invalid ISBN! Only letters and numbers are allowed.\n" << RESET;
                }
            } while (!isValidISBN(isbn));

            // Title Input
            cout << ORANGE << "Enter new Title: ";
            getline(cin, title);

            // Author Validation
            do {
                cout<< YELLOW << "Enter new Author: ";
                getline(cin, author);
                if (!isValidAuthor(author)) {
                    cout << RED << "Invalid author name! Only letters and spaces are allowed.\n" << RESET;
                }
            } while (!isValidAuthor(author));

            // Edition Validation
            do {
                cout<< ORANGE << "Enter new Edition: ";
                getline(cin, edition);
                if (!isValidEdition(edition)) {
                    cout << RED << "Invalid edition! Only letters and numbers are allowed (e.g., '12th Edition').\n" << RESET;
                }
            } while (!isValidEdition(edition));

            // Publication Validation
            do {
                cout<< YELLOW << "Enter new Publication: ";
                getline(cin, publication);
                if (!isValidPublication(publication)) {
                    cout << RED << "Invalid publication! Only letters and spaces are allowed.\n" << RESET;
                }
            } while (!isValidPublication(publication));

            books[i].editBook(isbn, title, author, edition, publication);
            cout << GREEN << "Book edited successfully!\n" << RESET;
            break;  
        }
    }

    if (!found) {  
        cout << RED << "Book not found!\n" << RESET;
    }

    cout<< MAGENTA << "Input any key to continue: ";
    cin.ignore();  
    cin.get();    
}


void searchBook() 
		{
		    if (bookCount == 0) {
		        cout << RED << "No Book in the Inventory\n" << RESET;
		        return;
		    }
		
		    string id;
		    cout << ORANGE << "Enter Book ID to search: ";
		    cin >> ws; 
		    getline(cin, id);
		
		    for (char &c : id) c = toupper(c);
		
		    for (int i = 0; i < bookCount; i++) {
		        string bookId = books[i].getId();
		
		        for (char &c : bookId) c = toupper(c);
		
		        if (bookId == id) {
		            cout << GREEN << "Book Found:\n" << RESET;
		            cout << ORANGE << "+------------+------------+----------------------+-----------------+---------+------------------+--------------+\n";
		            cout << "| Book ID    | ISBN       | Title                | Author          | Edition | Publication      | Category     |\n";
		            cout << PINK << "+------------+------------+----------------------+-----------------+---------+------------------+--------------+\n";
		            books[i].displayBook();
		            cout << ORANGE << "+------------+------------+----------------------+-----------------+---------+------------------+--------------+\n";
		            return;
		        }
		    }
		
		    cout << RED << "Book not found!\n" << RESET;
		    
		    cout << "Input any key to continue: ";
			cin.ignore();
			cin.get();
		}
	

    void deleteBook() 
	{
	    if (bookCount == 0) {
	        cout << RED << "No Book in the Inventory\n" << RESET;
	        return;
	    }
	
	    string id;
	    cout<< ORANGE << "Enter Book ID to delete: ";
	    cin >> ws;  // Clears leading whitespace
	    getline(cin, id);
	
	    // Convert input ID to uppercase
	    for (char &c : id) c = toupper(c);
	
	    for (int i = 0; i < bookCount; i++) {
	        string bookId = books[i].getId();
	
	        // Convert stored Book ID to uppercase for case-insensitive comparison
	        for (char &c : bookId) c = toupper(c);
	
	        if (bookId == id) {
	            cout << YELLOW << "Are you sure you want to delete this book? (Y/N): " << RESET;
	            char confirm;
	            cin >> confirm;
	            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
	
	            if (tolower(confirm) == 'y') {
	                // Shift elements to overwrite the deleted book
	                for (int j = i; j < bookCount - 1; j++) {
	                    books[j] = books[j + 1];
	                }
	                bookCount--;
	                cout << GREEN << "Book deleted successfully!\n" << RESET;
	            } else {
	                cout << MAGENTA << "Deletion canceled.\n" << RESET;
	            }
	            return;
	        }
	    }
	
	    cout << RED << "Book not found!\n" << RESET;
	}

void viewBooksByCategory() {
    if (bookCount == 0) {
        cout << RED << "No Book in the Inventory\n" << RESET;
        return;
    }

    string category;
    char choice;

    do {
        cout << ORANGE << "Enter Category (Fiction/Non-fiction): ";
        cin >> ws;  // Clears leading whitespace
        getline(cin, category);

        // Convert category to uppercase
        for (char &c : category) {
            c = toupper(c);
        }

        if (!isValidCategory(category)) {
            cout << RED << "Invalid category! Choose Fiction or Non-fiction.\n" << RESET;
            continue; // Restart the loop if invalid input
        }

        // Print Table Header
        cout << ORANGE<< "+------------+------------+----------------------+-----------------+---------+------------------+--------------+\n";
        cout << PINK << "| Book ID    | ISBN       | Title                | Author          | Edition | Publication      | Category     |\n";
        cout << ORANGE << "+------------+------------+----------------------+-----------------+---------+------------------+--------------+\n";

        bool found = false;
        for (int i = 0; i < bookCount; i++) {
            string bookCategory = books[i].getCategory();

            // Convert book category to uppercase for case-insensitive comparison
            for (char &c : bookCategory) {
                c = toupper(c);
            }

            if (bookCategory == category) {
                books[i].displayBook();
                found = true;
            }
        }

        if (!found) {
            cout << RED << "No books found in this category.\n" << RESET;
        } else {
            cout<< PINK << "+------------+------------+----------------------+-----------------+---------+------------------+--------------+\n";
        }

        // Ask user if they want to select another category
        cout << YELLOW << "Would you like to select another category? (Y/N): " << RESET;
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer

    } while (tolower(choice) == 'y');
}




    void viewAllBooks() 
	{
	    if (bookCount == 0) {
	        cout << RED << "No Book in the Inventory\n" << RESET;
	        return;
	    }
	
	    // Print table header
	    cout << PINK << "------------------------------------------------------------------------------------------------------------\n";
	    cout << "| " << left << setw(10) << "ID"
	         << "| " << setw(13) << "ISBN"
	         << "| " << setw(25) << "Title"
	         << "| " << setw(20) << "Author"
	         << "| " << setw(8) << "Edition"
	         << "| " << setw(15) << "Publication"
	         << "| " << setw(12) << "Category"
	         << " |\n";
	    cout << MAGENTA <<"------------------------------------------------------------------------------------------------------------\n" << RESET;
	
	    // Print each book
	    for (int i = 0; i < bookCount; i++) {
	        books[i].displayBook();
	    }
	
	    // Print footer
	    cout << PINK << "------------------------------------------------------------------------------------------------------------\n" << RESET;
	}

};

int getMenuChoice() {
    string input;
    int choice;
    bool validInput = false;

    while (!validInput) 
	{
		cout<< PINK <<"-----------------------------------------------"<<endl;
		cout<<"       Raven's Library Management System       "<<endl;
		cout<<"-----------------------------------------------"<<endl;
        cout<<YELLOW<<"1 - Add Book"<<endl;
        cout<<ORANGE<<"2 - Edit Book"<<endl;
        cout<<YELLOW<<"3 - Search Book"<<endl;
        cout<<ORANGE<<"4 - Delete Book"<<endl;
        cout<<YELLOW<<"5 - View Books by Category"<<endl;
        cout<<ORANGE<<"6 - View All Books"<<endl;
        cout<<YELLOW<<"7 - Exit"<<endl;
        cout<<PINK<<"\n-----------------------------------------------"<<endl;
		cout<<ORANGE<<"Enter your choice: "<< RESET;
        getline(cin, input);

        bool isValid = true;
        for (char c : input) {
            if (!isdigit(c)) { 
                isValid = false;
                break;
            }
        }

        if (isValid && input.size() == 1) {
            choice = input[0] - '0'; 
            if (choice >= 1 && choice <= 7) {
                validInput = true; 
            }
        }

        if (!validInput) {
            cout << RED << "Invalid input! Please enter a number between 1 and 7.\n" <<RESET <<endl;
        }
    }

    return choice;
}

int main() {
    Library library;
    int choice;
    do {
        choice = getMenuChoice();
        switch (choice) {
            case 1: library.addBook(); break;
            case 2: library.editBook(); break;
            case 3: library.searchBook(); break;
            case 4: library.deleteBook(); break;
            case 5: library.viewBooksByCategory(); break;
            case 6: library.viewAllBooks(); break;
            case 7: cout<< GREEN << "Thank you for using Library Management System!! \n"; break;
        }
    } while (choice != 7);
    return 0;
}

