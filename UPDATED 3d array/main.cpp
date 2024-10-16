#include <iostream>
#include <string>

using namespace std;

const int STORED_POST = 50;
const int STORED_COMMENTS = 50;
const int STORED_SUBCOMMENTS = 50;

int main() {
    string posts[STORED_POST][STORED_COMMENTS][STORED_SUBCOMMENTS];
    int commentCount[STORED_POST] = {0};
    int subCommentCount[STORED_POST][STORED_COMMENTS] = {0};

    int postCount = 0;
    string input;
    int choice;

    // ninakaw ko sa stackoverflow
    auto getValidNumber = [](const string& prompt) -> int {
        string input;
        int number;

        while (true) {
            cout << prompt;
            cin >> input;

            bool isValid = true;

            // for checking if integer lng sya, ch-check niya lahat ng characters
            for (char c : input) {
                if (c < '0' || c > '9') {
                    isValid = false;
                    break;
                }
            }

            // tsaka niya lng iv-validate pagka nacheck niya na lahat
            if (isValid) {
                number = stoi(input);
                break;
            } else {
                cout << "INVALID INPUT. Please enter a valid number." << endl;
            }
        }

        return number;
    };
        //pinaiksi ko ung menu
    do {
        cout << "-------------\nMAIN MENU\n1. ADD A POST\n2. ADD A COMMENT\n3. ADD A SUBCOMMENT\n4. VIEW ALL POSTS\n5. EXIT\n-------------\n";
        choice = getValidNumber("INPUT YOUR CHOICE (1-5): ");

        cin.ignore();

        switch (choice) {
            case 1: {
                if (postCount < STORED_POST) {
                    cout << "ENTER THE POST #" << postCount + 1 << ": ";
                    getline(cin, posts[postCount][0][0]);
                    cout << "POST #" << postCount + 1 << " ADDED SUCCESSFULLY!" << endl;
                    postCount++;
                } else {
                    cout << "MAXIMUM POSTS HAVE BEEN REACHED\n";
                }
                break;
            }

            case 2: {
                if (postCount == 0) {
                    cout << "NO POSTS AVAILABLE.\n";
                    break;
                }

                for (int i = 0; i < postCount; i++) {
                    cout << i + 1 << ": " << posts[i][0][0] << endl;
                }

                int postNum = getValidNumber("ENTER THE POST NUMBER TO ADD A COMMENT TO (1 TO " + to_string(postCount) + "): ");

                if (postNum >= 1 && postNum <= postCount) {
                    if (commentCount[postNum - 1] < STORED_COMMENTS) {
                        cout << "ENTER COMMENT #" << commentCount[postNum - 1] + 1 << " FOR POST #" << postNum << ": ";
                        getline(cin, posts[postNum - 1][commentCount[postNum - 1]][0]);
                        commentCount[postNum - 1]++;
                        cout << "COMMENT #" << commentCount[postNum - 1] << " ADDED SUCCESSFULLY TO POST #" << postNum << "!" << endl;
                    } else {
                        cout << "MAXIMUM COMMENTS HAVE BEEN REACHED\n";
                    }
                } else {
                    cout << "INVALID POST NUMBER.\n";
                }
                break;
            }

            case 3: {
                if (postCount == 0) {
                    cout << "NO POSTS AVAILABLE.\n";
                    break;
                }

                for (int i = 0; i < postCount; i++) {
                    cout << i + 1 << ": " << posts[i][0][0] << endl;
                }

                int postNum = getValidNumber("ENTER THE POST NUMBER TO ADD A SUBCOMMENT TO (1 TO " + to_string(postCount) + "): ");

                if (postNum >= 1 && postNum <= postCount) {
                    if (commentCount[postNum - 1] == 0) {
                        cout << "NO COMMENTS AVAILABLE FOR THIS POST.\n";
                        break;
                    }

                    for (int j = 1; j <= commentCount[postNum - 1]; j++) {
                        cout << "COMMENT #" << j << ": " << posts[postNum - 1][j][0] << "\n";
                    }

                    int commentNum = getValidNumber("ENTER THE COMMENT NUMBER TO ADD A SUBCOMMENT TO (1 TO " + to_string(commentCount[postNum - 1]) + "): ");

                    if (commentNum >= 1 && commentNum <= commentCount[postNum - 1]) {
                        if (subCommentCount[postNum - 1][commentNum - 1] < STORED_SUBCOMMENTS) {
                            cout << "ENTER SUBCOMMENT #" << subCommentCount[postNum - 1][commentNum - 1] + 1 << " FOR COMMENT #" << commentNum << " IN POST #" << postNum << ": ";
                            getline(cin, posts[postNum - 1][commentNum][subCommentCount[postNum - 1][commentNum - 1]]);
                            subCommentCount[postNum - 1][commentNum - 1]++;
                            cout << "SUBCOMMENT ADDED SUCCESSFULLY!" << endl;
                        } else {
                            cout << "MAXIMUM SUBCOMMENTS HAVE BEEN REACHED\n";
                        }
                    } else {
                        cout << "INVALID COMMENT NUMBER.\n";
                    }
                } else {
                    cout << "INVALID POST NUMBER.\n";
                }
                break;
            }

            case 4: {
                cout << "\n----ALL POSTS----\n";
                for (int i = 0; i < postCount; i++) {
                    cout << "POST #" << (i + 1) << ": " << posts[i][0][0] << "\n";
                    for (int j = 1; j <= commentCount[i]; j++) {
                        cout << "COMMENT #" << j << ": " << posts[i][j][0] << "\n";
                        for (int k = 1; k <= subCommentCount[i][j - 1]; k++) {
                            cout << "SUBCOMMENT #" << k << ": " << posts[i][j][k] << "\n";
                        }
                    }
                }
                break;
            }

            case 5: {
                cout << "EXITING...\n";
                break;
            }

            default:
                cout << "INVALID CHOICE. TRY AGAIN :)\n";
                break;
        }
    } while (choice != 5);

    return 0;
}
