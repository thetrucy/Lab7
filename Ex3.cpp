#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <cmath>
using namespace std;


class PlaneGeometry {
protected:
    string name;
    string color;
    
public:
    PlaneGeometry();
    PlaneGeometry(const string& name);
    virtual ~PlaneGeometry() = default;

    virtual double calculateArea() const = 0;
    virtual double calculatePerimeter() const = 0;
    virtual void display() const;
    

    string getName() const { return name; }
    

    void setName(const string& name) { this->name = name; }

};

class Triangle : public PlaneGeometry {
private:
    double sideA, sideB, sideC;
    
public:
    Triangle();
    Triangle(double s1, double s2, double s3);
    

    double calculateArea() const override;
    double calculatePerimeter() const override;
    void display() const override;
    

    bool isValid() const;
    string getTriangleType() const;
    

    double getSideA() const { return sideA; }
    double getSideB() const { return sideB; }
    double getSideC() const { return sideC; }
    

    void setSides(double s1, double s2, double s3);
};

class Rectangle : public PlaneGeometry {
protected:
    double length, width;
    
public:
    Rectangle();
    Rectangle(double length, double width);

    double calculateArea() const override;
    double calculatePerimeter() const override;
    void display() const override;
    

    double getLength() const { return length; }
    double getWidth() const { return width; }
    

    virtual void setSize(double length, double width);
};

class Square : public Rectangle {
public:
    Square();
    Square(double side);
    

    void display() const override;

    double getSide() const { return length; }
    void setSide(double side);

    void setSize(double side) { setSize(side, side); }
    void setSize(double length, double width) override;
};

class Book {
protected:
    string title;
    string author;
    string Id;
    int publicationYear;
    bool isAvailable;
    
public:
    Book();
    Book(const string& title, const string& author, const string& Id, int year);
    virtual ~Book() = default;
    

    virtual void display() const;
    virtual string getBookType() const { return "General Book"; }
    

    void borrowBook();
    void returnBook();
    

    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    string getId() const { return Id; }
    int getPublicationYear() const { return publicationYear; }
    bool getAvailability() const { return isAvailable; }
    

    void setTitle(const string& title) { this->title = title; }
    void setAuthor(const string& author) { this->author = author; }
    void setId(const string& Id) { this->Id = Id; }
    void setPublicationYear(int year) { this->publicationYear = year; }
};

class Library {
private:
    string libraryName;
    vector<Book*> books;
    
public:
    Library();
    Library(const string& name);
    ~Library();
    
    void addBook(Book* book);
    void removeBook(const string& Id);
    Book* findBook(const string& Id);
    Book* findBookByTitle(const string& title);

    void displayAllBooks() const;
    void displayAvailableBooks() const;
    void displayBorrowedBooks() const;
    void displayLibraryInfo() const;
    

    string getLibraryName() const { return libraryName; }
    int getTotalBooks() const { return books.size(); }
    

    void setLibraryName(const string& name) { this->libraryName = name; }

};


PlaneGeometry::PlaneGeometry() : name("Unknown Shape"){}

PlaneGeometry::PlaneGeometry(const string& name) 
    : name(name) {}

void PlaneGeometry::display() const {
    cout << "Shape: " << name << endl;
    cout << "Area: " << fixed << setprecision(2) << calculateArea() << endl;
    cout << "Perimeter: " << fixed << setprecision(2) << calculatePerimeter() << endl;
}



Triangle::Triangle() : PlaneGeometry("Triangle"), sideA(0), sideB(0), sideC(0) {}

Triangle::Triangle(double s1, double s2, double s3) 
    : PlaneGeometry("Triangle"), sideA(s1), sideB(s2), sideC(s3) {}

double Triangle::calculateArea() const {
    if (!isValid()) return 0;
    
    double p = calculatePerimeter() / 2;
    return sqrt(p * (p - sideA) * (p - sideB) * (p - sideC)); 
}

double Triangle::calculatePerimeter() const {
    return sideA + sideB + sideC;
}

void Triangle::display() const {
    cout << "\n=== TRIANGLE INFO ===" << endl;
    PlaneGeometry::display();
    cout << "Side A: " << sideA << endl;
    cout << "Side B: " << sideB << endl;
    cout << "Side C: " << sideC << endl;
    cout << "Type: " << getTriangleType() << endl;
    cout << "Valid: " << (isValid() ? "Yes" : "No") << endl;
}

bool Triangle::isValid() const {
    return (sideA + sideB > sideC) && 
           (sideA + sideC > sideB) && 
           (sideB + sideC > sideA) &&
           (sideA > 0) && (sideB > 0) && (sideC > 0);
}

string Triangle::getTriangleType() const {
    if (!isValid()) return "Invalid";
    
    if (sideA == sideB && sideB == sideC) return "Equilateral";
    if (sideA == sideB || sideB == sideC || sideA == sideC) return "Isosceles";
    return "Scalene";
}

void Triangle::setSides(double s1, double s2, double s3) {
    sideA = s1;
    sideB = s2;
    sideC = s3;
}

Rectangle::Rectangle() : PlaneGeometry("Rectangle"), length(0), width(0) {}

Rectangle::Rectangle(double length, double width) 
    : PlaneGeometry("Rectangle"), length(length), width(width) {}

double Rectangle::calculateArea() const {
    return length * width;
}

double Rectangle::calculatePerimeter() const {
    return 2 * (length + width);
}

void Rectangle::display() const {
    cout << "\n=== RECTANGLE INFO ===" << endl;
    PlaneGeometry::display();
    cout << "Length: " << length << endl;
    cout << "Width: " << width << endl;
}

void Rectangle::setSize(double length, double width) {
    this->length = length;
    this->width = width;
}


Square::Square() : Rectangle(0, 0) {
    name = "Square";
}

Square::Square(double side) : Rectangle(side, side) {
    name = "Square";
}

void Square::display() const {
    cout << "\n=== SQUARE INFO ===" << endl;
    PlaneGeometry::display();
    cout << "Side: " << length << endl;
}

void Square::setSide(double side) {
    length = width = side;
}

void Square::setSize(double length, double width) {
    double side = (length + width) / 2;
    this->length = this->width = side;
}

Book::Book() : title("Unknown"), author("Unknown"), Id("000-0000000000"), 
               publicationYear(0), isAvailable(true) {}

Book::Book(const string& title, const string& author, const string& Id, int year) 
    : title(title), author(author), Id(Id), publicationYear(year), isAvailable(true) {}

void Book::display() const {
    cout << "\n=== BOOK INFO ===" << endl;
    cout << "Title: " << title << endl;
    cout << "Author: " << author << endl;
    cout << "Id: " << Id << endl;
    cout << "Publication Year: " << publicationYear << endl;
    cout << "Type: " << getBookType() << endl;
    cout << "Status: " << (isAvailable ? "Available" : "Borrowed") << endl;
}

void Book::borrowBook() {
    if (isAvailable) {
        isAvailable = false;
        cout << "Book '" << title << "' has been borrowed." << endl;
    } else {
        cout << "Book '" << title << "' is already borrowed." << endl;
    }
}

void Book::returnBook() {
    if (!isAvailable) {
        isAvailable = true;
        cout << "Book '" << title << "' has been returned." << endl;
    } else {
        cout << "Book '" << title << "' was not borrowed." << endl;
    }
}


Library::Library() : libraryName("Unnamed Library") {}

Library::Library(const string& name) : libraryName(name) {}

Library::~Library() {
    for (Book* book : books) {
        delete book;
    }
    books.clear();
}

void Library::addBook(Book* book) {
    if (book != nullptr) {
        books.push_back(book);
        cout << "Book '" << book->getTitle() << "' added to library." << endl;
    }
}

void Library::removeBook(const string& Id) {
    for (auto it = books.begin(); it != books.end(); ++it) {
        if ((*it)->getId() == Id) {
            cout << "Book '" << (*it)->getTitle() << "' removed from library." << endl;
            delete *it;
            books.erase(it);
            return;
        }
    }
    cout << "Book with Id " << Id << " not found." << endl;
}

Book* Library::findBook(const string& Id) {
    for (Book* book : books) {
        if (book->getId() == Id) {
            return book;
        }
    }
    return nullptr;
}

Book* Library::findBookByTitle(const string& title) {
    for (Book* book : books) {
        if (book->getTitle() == title) {
            return book;
        }
    }
    return nullptr;
}

void Library::displayAllBooks() const {
    cout << "\n=== ALL BOOKS IN " << libraryName << " ===" << endl;
    if (books.empty()) {
        cout << "No books in the library." << endl;
        return;
    }
    
    for (size_t i = 0; i < books.size(); ++i) {
        cout << (i + 1) << ". ";
        books[i]->display();
    }
}

void Library::displayAvailableBooks() const {
    cout << "\n=== AVAILABLE BOOKS ===" << endl;
    bool hasAvailable = false;
    
    for (size_t i = 0; i < books.size(); ++i) {
        if (books[i]->getAvailability()) {
            cout << (i + 1) << ". ";
            books[i]->display();
            hasAvailable = true;
        }
    }
    
    if (!hasAvailable) {
        cout << "No books available." << endl;
    }
}

void Library::displayBorrowedBooks() const {
    cout << "\n=== BORROWED BOOKS ===" << endl;
    bool hasBorrowed = false;
    
    for (size_t i = 0; i < books.size(); ++i) {
        if (!books[i]->getAvailability()) {
            cout << (i + 1) << ". ";
            books[i]->display();
            hasBorrowed = true;
        }
    }
    
    if (!hasBorrowed) {
        cout << "No books are currently borrowed." << endl;
    }
}

void Library::displayLibraryInfo() const {
    cout << "\n=== LIBRARY INFORMATION ===" << endl;
    cout << "Library Name: " << libraryName << endl;
    cout << "Total Books: " << books.size() << endl;
    
    int available = 0, borrowed = 0;
    for (const Book* book : books) {
        if (book->getAvailability()) available++;
        else borrowed++;
    }
    
    cout << "Available Books: " << available << endl;
    cout << "Borrowed Books: " << borrowed << endl;
}


int main() {
    cout << "\n" << string(60, '=') << endl;
    cout << "PLANE GEOMETRY HIERARCHY DEMONSTRATION" << endl;
    cout << string(60, '=') << endl;
    
    Triangle triangle(3, 4, 5);
    Rectangle rectangle(10, 6);
    Square square(5);
    

    vector<PlaneGeometry*> shapes = {&triangle, &rectangle, &square};
    
    cout << "\nDemonstrating Polymorphism:" << endl;
    for (PlaneGeometry* shape : shapes) {
        shape->display();
        cout << string(40, '-') << endl;
    }
    

    cout << "\nTriangle-specific methods:" << endl;
    Triangle invalidTriangle(1, 2, 10);
    invalidTriangle.display();

    cout << "\n" << string(60, '=') << endl;
    cout << "LIBRARY SYSTEM DEMONSTRATION" << endl;
    cout << string(60, '=') << endl;
    

    Library library("ABC Library");
    

    Book* book1 = new Book("The Sun", "Nguyen Van A", "123123", 2000);
    Book* book2 = new Book("The moon", "Nguyen Thi B", "258456", 2012);
    Book* book3 = new Book("The stars", "Andrew Ng", "85214", 2011);
    Book* book4 = new Book("Something", "Vo Van Ba", "85764", 1879);

    library.addBook(book1);
    library.addBook(book2);
    library.addBook(book3);
    library.addBook(book4);

    library.displayLibraryInfo();
    

    library.displayAllBooks();
    

    cout << "\n=== BORROWING BOOKS ===" << endl;
    book1->borrowBook();
    book3->borrowBook();

    library.displayAvailableBooks();
    library.displayBorrowedBooks();

    cout << "\n=== RETURNING BOOKS ===" << endl;
    book1->returnBook();
    

    library.displayLibraryInfo();
    
    
    return 0;
}