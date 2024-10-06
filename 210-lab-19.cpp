#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

struct Node {
    double rating;
    string comments;
    Node* next;
};

class Movie {
private:
    string title;
    Node* ratingHead;
    Node* ratingTail;
    Node* commentsHead;
    Node* commentsTail;

public:
    Movie(string title) {
        this->title = title;
        ratingHead = nullptr;
        ratingTail = nullptr;
        commentsHead = nullptr;
        commentsTail = nullptr;
    }

    void addRating(double rating) {
        Node* newNode = new Node;
        newNode->rating = rating;
        newNode->next = nullptr;
        if (ratingTail == nullptr) {
            ratingHead = newNode;
            ratingTail = newNode;
        }
        else {
            ratingTail->next = newNode;
            ratingTail = newNode;
        }
    }

    void addComment(string comment) {
        Node* newNode = new Node;
        newNode->comments = comment;
        newNode->next = nullptr;
        if (commentsTail == nullptr) {
            commentsHead = newNode;
            commentsTail = newNode;
        }
        else {
            commentsTail->next = newNode;
            commentsTail = newNode;
        }
    }

    void printReviews() {
        Node* ratingTemp = ratingHead;
        Node* commentsTemp = commentsHead;
        int count = 1;
        double sum = 0.0;
        cout << "Reviews for " << title << ":" << endl;
        while (ratingTemp != nullptr) {
            cout << "> Review #" << count << ": " << ratingTemp->rating << ": " << commentsTemp->comments << endl;
            sum += ratingTemp->rating;
            ratingTemp = ratingTemp->next;
            commentsTemp = commentsTemp->next;
            count++;
        }
        if (count > 1) {
            cout << "> Average: " << sum / (count - 1) << endl;
        }
    }
};

int main() {
    srand(time(0));
    vector<Movie> movies;

    ifstream file("reviews.txt");
    if (file.is_open()) {
        string line;
        string title;
        while (getline(file, line)) {
            if (line[0] == '#') {
                title = line.substr(1);
                movies.push_back(Movie(title));
            }
            else {
                movies.back().addComment(line);
                movies.back().addRating(1.0 + (rand() % 5));
            }
        }
        file.close();
    }

    for (int i = 0; i < movies.size(); i++) {
        movies[i].printReviews();
        cout << endl;
    }

    return 0;
}