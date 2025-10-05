#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

class Ticket
{
public:
  int seatNumber;
  string movieName;
  float price;
  bool isBooked;

  Ticket(int num = 0, string name = "Movie", float p = 150.0)
  {
    seatNumber = num;
    movieName = name;
    price = p;
    isBooked = false;
  }
};

class BookingSystem
{
private:
  Ticket seats[10];
  int totalSeats;
  string fileName = "bookings.txt";

public:
  BookingSystem()
  {
    totalSeats = 10;
    for (int i = 0; i < totalSeats; i++)
    {
      seats[i] = Ticket(i + 1, "Inception", 150.0);
    }
  }

  void displaySeats()
  {
    cout << "\nSeat Status:\n";
    for (int i = 0; i < totalSeats; i++)
    {
      cout << "Seat " << setw(2) << seats[i].seatNumber << " - ";
      if (seats[i].isBooked)
        cout << "Booked\n";
      else
        cout << "Available\n";
    }
  }

  void bookTicket()
  {
    int seatNum;
    string name;
    displaySeats();
    cout << "\nEnter seat number to book: ";
    cin >> seatNum;

    if (seatNum < 1 || seatNum > totalSeats)
    {
      cout << "Invalid seat number.\n";
      return;
    }

    if (seats[seatNum - 1].isBooked)
    {
      cout << "Sorry, seat already booked.\n";
      return;
    }

    cout << "Enter your name: ";
    cin >> name;

    seats[seatNum - 1].isBooked = true;

    // Dynamic pricing: price increases by 10 per booked seat
    seats[seatNum - 1].price += seatNum * 10;

    ofstream file(fileName, ios::app);
    file << "Name: " << name
         << ", Seat: " << seatNum
         << ", Price: " << seats[seatNum - 1].price << "\n";
    file.close();

    cout << "Ticket booked successfully!\n";
  }

  void viewBookings()
  {
    ifstream file(fileName);
    if (!file)
    {
      cout << "No bookings yet.\n";
      return;
    }
    cout << "\nCurrent Bookings:\n";
    string line;
    while (getline(file, line))
    {
      cout << line << "\n";
    }
    file.close();
  }
};

int main()
{
  BookingSystem system;
  int choice;

  cout << "🎟 Movie Ticket Booking System 🎟\n";

  while (true)
  {
    cout << "\n1. View Seats\n2. Book Ticket\n3. View All Bookings\n4. Exit\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
      system.displaySeats();
      break;
    case 2:
      system.bookTicket();
      break;
    case 3:
      system.viewBookings();
      break;
    case 4:
      cout << "Thank you for using the system!\n";
      return 0;
    default:
      cout << "Invalid choice. Try again.\n";
    }
  }
}