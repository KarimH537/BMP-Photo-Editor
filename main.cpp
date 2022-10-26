// FCI – Programming 1 – 2022 - Assignment 3
// Program Name: GreyScale_Filters.cpp
// Last Modification Date: 21/4/2022
// Author1 and ID and Group: Karim Mohamed 20210298
// Author2 and ID and Group: Hazem Mohamed Waheed 20210115
// Author3 and ID and Group: Abdelrahman Ashraf 20210199
// Purpose: Editing grey scale bitmap pictures


#include <iostream>
#include <cstring>
#include "bmplib.cpp"

using namespace std;
unsigned char image[SIZE][SIZE];
unsigned char image2[SIZE][SIZE];
unsigned char new_image[SIZE][SIZE];

void loadImage();

void blackandwhite();

void invert();

void merge();

void flip();

void rotate();

void darkenorlighten();

void edge_detection();

void enlarge();

void shrink();

void mirror();

void shuffle();

void blur();

void saveImage();

int main() {
    bool flag = true;
    loadImage();
    while (flag) {
        char choice;

        cout << "\n1)Black and White\n2)Invert\n3)Merge\n4)flip\n5)Rotate\n6)Darken or Lighten\n7)Edge detection\n8)Enlarge\n9)Shrink\na) Mirror 1/2 Image\nb)Shuffle\nc)Blur\ns)Save\ne)Exit"
             << endl;
        cin >> choice;
        switch (tolower(choice)) {
            case 's':
                saveImage();
                break;
            case 'e':
                flag = false;
                break;
            case '1':
                blackandwhite();
                break;
            case '2':
                invert();
                break;
            case '3':
                merge();
                break;
            case '4':
                flip();
                break;
            case '5':
                rotate();
                break;
            case '6':
                darkenorlighten();
                break;
            case '7':
                edge_detection();
                break;
            case '8':
                enlarge();
                break;
            case '9':
                shrink();
                break;
            case 'a':
                mirror();
                break;
            case 'b':
                shuffle();
                break;
            case 'c':
                blur();
                break;
            default:
                cout << "NOT A VALID OPTION";
                break;
        }
        // returning the saved new image in image
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                    image[i][j] = new_image[i][j];

            }
        }
    }
}

void loadImage() {
    char imageFileName[100];


    cout << "Enter the source image file name: ";
    cin >> imageFileName;


    strcat(imageFileName, ".bmp");
    readGSBMP(imageFileName, image);
}


void saveImage() {
    char imageFileName[100];

    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    strcat(imageFileName, ".bmp");
    writeGSBMP(imageFileName, new_image);
}

void blackandwhite() {
    long long avg;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            avg += image[i][j];
        }
    }
    avg /= (SIZE * SIZE);
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (image[i][j] > avg)
                new_image[i][j] = 255;
            else
                new_image[i][j] = 0;
        }
    }

}

void invert() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            new_image[i][j] = 255 - image[i][j];
        }
    }


}

void merge() {
    char image2FileName[100];

    cout << "Enter the source second image file name: ";
    cin >> image2FileName;


    strcat(image2FileName, ".bmp");
    readGSBMP(image2FileName, image2);

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            new_image[i][j] = (image[i][j] + image2[i][j]) / 2;

        }
    }

}

void flip() {
    char choice;
    cout << "Flip (h)orizontally or (v)ertically ? : ";
    cin >> choice;
    while (choice != 'v' && choice != 'h'){
        cout << "ENTER A VALID INPUT : ";
        cin >> choice;
    }
    cout << "\n";
    if (tolower(choice) == 'v') {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                new_image[i][j] = image[255 - i][j];
            }
        }
    }
    if (tolower(choice) == 'h') {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                new_image[i][j] = image[i][255 - j];
            }
        }
    }

}

void rotate() {
    string choice;
    cout << "Enter angle to rotate: ";
    cin >> choice;
    while (choice != "90" && choice != "180" && choice != "270"){
        cout << "ENTER A VALID INPUT : ";
        cin >> choice;
    }

    if (choice == "180") {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                new_image[i][j] = image[255 - i][255 - j];
            }
        }
    }

    if (choice == "90") {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 256; j > 0; j--) {
                new_image[256 - j][i] = image[i][j];
            }
        }
    }
    if (choice == "270") {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                new_image[i][j] = image[255 - j][i];
            }
        }
    }


}


void darkenorlighten() {
    char choice;
    cout << "Do you want to (d)arken or (l)ighten? : ";
    cin >> choice;
    while (choice != 'd' && choice != 'l'){
        cout << "ENTER A VALID INPUT : ";
        cin >> choice;
    }
    //lighten
    if ((char) tolower(choice) == 'l') {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (image[i][j] + (image[i][j] / 2) <= 255) {
                    new_image[i][j] = image[i][j] + ((image[i][j]) / 2);
                } else image[i][j] = 255;
            }
        }
    }
    // Darken
    if ((char) tolower(choice) == 'd') {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                new_image[i][j] = image[i][j] - ((image[i][j]) / 2);
            }
        }
    }

}


void edge_detection() {
    // changing image to black and white
    long long avg;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            avg += image[i][j];
        }
    }
    avg /= (SIZE * SIZE);
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (image[i][j] > avg)
                image[i][j] = 255;
            else
                image[i][j] = 0;
        }
    }
    // edge detection algorithm
    // only checking from the left or the right or downwards
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (image[i][j] != image[i][j + 1] || image[i][j] != image[i][j - 1] || image[i][j] != image[i + 1][j]) {
                new_image[i][j] = 0;
            } else {
                new_image[i][j] = 255;
            }
        }
    }

}
void enlarge(){
    char ch;
    cout << "Which quarter to enlarge 1, 2, 3 or 4? : ";
    cin >> ch;
    while (ch != '1' && ch != '2' && ch != '3' && ch != '4'){
        cout << "ENTER A VALID INPUT : ";
        cin >> ch;
    }
    if (ch == '1'){
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< SIZE; j++) {

                new_image[i][j] = image[i/2][j/2];
            }
        }
    }

    if (ch == '2'){
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< SIZE; j++) {

                new_image[i][j] = image[i/2][j/2+SIZE/2];
            }
        }
    }

    if (ch == '3'){
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< SIZE; j++) {

                new_image[i][j] = image[i/2+SIZE/2][j/2];
            }
        }
    }

    if (ch == '4'){
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< SIZE; j++) {

                new_image[i][j] = image[i/2+SIZE/2][j/2+SIZE/2];
            }
        }
    }


}
void shrink() {
    string scale;
    cout << "Shrink by:\n1)1/2\n2)1/3\n3)1/4\n";
    cin >> scale;
    while (scale != "1" && scale != "2" && scale != "3"){
        cout << "ENTER A VALID INPUT : ";
        cin >> scale;
    }

    if (scale == "1") {
        for (int i = 0; i < 126; i++) {
            for (int j = 0; j < 126; j++) {
                new_image[i][j] = image[i * 2][j * 2];
            }
        }

    } else if (scale == "2") {
        for (int i = 0; i < 86; i++) {
            for (int j = 0; j < 86; j++) {
                new_image[i][j] = image[i * 3][j * 3];
            }
        }

    } else if (scale == "3") {
        for (int i = 0; i < 64; i++) {
            for (int j = 0; j < 64; j++) {
                new_image[i][j] = image[i * 4][j * 4];
            }
        }

    }



}


void mirror() {

    char choice;
    cout << "Mirror (l)eft, (r)ight, (u)pper, (d)own side? : ";
    cin >> choice;
    while (choice != 'l' && choice != 'e' && choice != 'f' && choice != 't'){
        cout << "ENTER A VALID INPUT : ";
        cin >> choice;
    }
    cout << '\n';
    choice = tolower(choice);
    // left
    if (choice == 'l') {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE / 2; ++j) {
                new_image[i][j] = image[i][j];
            }
        }
        for (int i = 0; i < SIZE; ++i) {
            for (int j = SIZE / 2; j < SIZE; ++j) {
                new_image[i][j] = image[i][255 - j];
            }
        }
    }
    // right
    if (choice == 'r') {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE / 2; ++j) {
                new_image[i][j] = image[i][255 - j];
            }
        }
        for (int i = 0; i < SIZE; ++i) {
            for (int j = SIZE / 2; j < SIZE; ++j) {
                new_image[i][j] = image[i][j];
            }
        }
    }
    // upper
    if (choice == 'u') {
        for (int i = 0; i < SIZE / 2; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                new_image[i][j] = image[i][j];
            }
        }
        for (int i = SIZE / 2; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                new_image[i][j] = image[255 - i][j];
            }
        }
    }
    // downside
    if (choice == 'd') {
        for (int i = SIZE / 2; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                new_image[i][j] = image[i][j];
            }
        }
        for (int i = 0; i < SIZE / 2; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                new_image[i][j] = image[255 - i][j];
            }
        }
    }

}

void shuffle() {
    int row, col;
    string order;
    cout << "Enter the order without spaces: ";
    cin.clear();
    cin.sync();

    getline(cin, order);
    for (int k = 0; k < 4; k++) {
        int r = 0, c = 0;
        r = k < 2 ? 0 : SIZE / 2;
        row = order[k] < '3' ? 0 : SIZE / 2;
        for (int i = row; i < row + SIZE / 2; i++, r++) {
            col = (order[k] - '0') % 2 == 1 ? 0 : SIZE / 2;
            c = k % 2 == 0 ? 0 : SIZE / 2;
            for (int j = col; j < col + SIZE / 2; j++, c++)
                new_image[r][c] = image[i][j];

        }
    }

}

void blur() {
    for (int i = 1; i < SIZE-1; i++) {
        for (int j = 1; j < SIZE-1; j++) {
            new_image[i][j] =
                    (image[i][j+1] + image[i][j + 2] + image[i][j+3] + image[i+ 1][j] + image[i+2][j] +
                     image[i+3][j] + image[i + 1][j + 1] + image[i + 2][j+2] + image[i + 3][j + 3]) / 9;
        }
    }

}
