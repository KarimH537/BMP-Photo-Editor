// FCI – Programming 1 – 2022 - Assignment 3
// Program Name: RGB_Filters.cpp
// Last Modification Date: 21/4/2022
// Author1 and ID and Group: Karim Mohamed 20210298
// Author2 and ID and Group: Hazem Mohamed Waheed 20210115
// Author3 and ID and Group: Abdelrahman Ashraf 20210199
// Purpose: Editing RGB bitmap pictures

#include <iostream>
#include <cstring>
#include "bmplib.cpp"

using namespace std;
unsigned char image[SIZE][SIZE][RGB];
unsigned char image2[SIZE][SIZE][RGB];
unsigned char new_image[SIZE][SIZE][RGB];

void loadImage();

void black_white();

void invert();

void merge();

void flip();

void rotate();

void darken_lighten();

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
                black_white();
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
                darken_lighten();
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
                for (int k = 0; k < RGB; ++k) {
                    image[i][j][k] = new_image[i][j][k];
                }
            }
        }
    }
}
void loadImage() {
    char imageFileName[100];

    cout << "Enter the source image file name: ";
    cin >> imageFileName;

    strcat(imageFileName, ".bmp");
    readRGBBMP(imageFileName, image);
}

void saveImage() {
    char imageFileName[100];

    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    strcat(imageFileName, ".bmp");
    writeRGBBMP(imageFileName, new_image);
}

void black_white() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (image[i][j][0] + image[i][j][1] + image[i][j][2] > 384) {
                for (int k = 0; k < RGB; ++k) {
                    new_image[i][j][k] = 255;
                }
            } else {
                for (int k = 0; k < RGB; ++k) {
                    new_image[i][j][k] = 0;
                }
            }
        }
    }
}

void invert() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            for (int k = 0; k < 3; ++k) {
                new_image[i][j][k] = 255 - image[i][j][k];
            }
        }
    }
}

void merge() {
    // loading image 2
    char imageFileName[100];
    cout << "Enter the source image file name: ";
    cin >> imageFileName;

    strcat(imageFileName, ".bmp");
    readRGBBMP(imageFileName, image2);

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            for (int k = 0; k < RGB; ++k) {
                new_image[i][j][k] = (image[i][j][k] + image2[i][j][k]) / 2;
            }
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
                new_image[i][j][0] = image[255 - i][j][0];
                new_image[i][j][1] = image[255 - i][j][1];
                new_image[i][j][2] = image[255 - i][j][2];
            }
        }
    }
    else if (tolower(choice) == 'h') {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                new_image[i][j][0] = image[i][255 - j][0];
                new_image[i][j][1] = image[i][255 - j][1];
                new_image[i][j][2] = image[i][255 - j][2];
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
                new_image[i][j][0] = image[255 - i][255 - j][0];
                new_image[i][j][1] = image[255 - i][255 - j][1];
                new_image[i][j][2] = image[255 - i][255 - j][2];
            }
        }
    }

    if (choice == "270") {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 256; j > 0; j--) {
                new_image[256 - j][i][0] = image[i][j][0];
                new_image[256 - j][i][1] = image[i][j][1];
                new_image[256 - j][i][2] = image[i][j][2];
            }
        }
    }
    if (choice == "90") {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                new_image[i][j][0] = image[255 - j][i][0];
                new_image[i][j][1] = image[255 - j][i][1];
                new_image[i][j][2] = image[255 - j][i][2];
            }
        }
    }
}

void darken_lighten() {
    char choice;
    cout << "Do you want to (d)arken or (l)ighten? : ";
    cin >> choice;
    while (choice != 'd' && choice != 'l'){
        cout << "ENTER A VALID INPUT : ";
        cin >> choice;
    }
    if (choice == 'd') {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                for (int k = 0; k < 3; ++k) {
                    new_image[i][j][k] = image[i][j][k] / 2;
                }
            }
        }
    } else if (choice == 'l') {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                for (int k = 0; k < 3; ++k) {
                    new_image[i][j][k] = (image[i][j][k] + 255) / 2;
                }
            }
        }
    }
}

void edge_detection() {
    // change it to black and white
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (image[i][j][0] + image[i][j][1] + image[i][j][2] > 384) {
                for (int k = 0; k < RGB; ++k) {
                    image2[i][j][k] = 255;
                }
            } else {
                for (int k = 0; k < RGB; ++k) {
                    image2[i][j][k] = 0;
                }
            }
        }
    }
    // checking every direction except bottom right and bottom left
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (image2[i][j][0] != image2[i][j + 1][0] || image2[i][j][0] != image2[i][j - 1][0] ||
                image2[i][j][0] != image2[i + 1][j][0] || image2[i][j][0] != image2[i + 1][j + 1][0] ||
                image2[i][j][0] != image2[i + 1][j - 1][0]) {
                for (int k = 0; k < RGB; ++k) {
                    new_image[i][j][k] = 0;
                }
            } else {
                for (int k = 0; k < RGB; ++k) {
                    new_image[i][j][k] = 255;
                }
            }
        }
    }
}

void enlarge() {
    char ch;
    cout << "Which quarter to enlarge 1, 2, 3 or 4? : ";
    cin >> ch;
    while (ch != '1' && ch != '2' && ch != '3' && ch != '4'){
        cout << "ENTER A VALID INPUT : ";
        cin >> ch;
    }
    int a, b;
    if (ch == '1') {
        a = 0;
        for (int i = 0; i < SIZE; i += 2) {
            b = 0;
            for (int j = 0; j < SIZE; j += 2) {
                for (int k = 0; k < 3; ++k) {
                    new_image[i][j][k] = image[a][b][k];
                    new_image[i + 1][j][k] = image[a][b][k];
                    new_image[i][j + 1][k] = image[a][b][k];
                    new_image[i + 1][j + 1][k] = image[a][b][k];
                }
                b += 1;
            }
            a += 1;
        }
    }

    if (ch == '2') {
        a = 0;
        for (int i = 0; i < SIZE; i += 2) {
            b = 128;
            for (int j = 0; j < SIZE; j += 2) {
                for (int k = 0; k < 3; ++k) {
                    new_image[i][j][k] = image[a][b][k];
                    new_image[i + 1][j][k] = image[a][b][k];
                    new_image[i][j + 1][k] = image[a][b][k];
                    new_image[i + 1][j + 1][k] = image[a][b][k];
                }
                b += 1;
            }
            a += 1;
        }
    }
    if (ch == '3') {
        a = 128;
        for (int i = 0; i < SIZE; i += 2) {
            b = 0;
            for (int j = 0; j < SIZE; j += 2) {
                for (int k = 0; k < 3; ++k) {
                    new_image[i][j][k] = image[a][b][k];
                    new_image[i + 1][j][k] = image[a][b][k];
                    new_image[i][j + 1][k] = image[a][b][k];
                    new_image[i + 1][j + 1][k] = image[a][b][k];
                }
                b += 1;
            }
            a += 1;
        }
    }
    if (ch == '4') {
        a = 128;
        for (int i = 0; i < SIZE; i += 2) {
            b = 128;
            for (int j = 0; j < SIZE; j += 2) {
                for (int k = 0; k < 3; ++k) {
                    new_image[i][j][k] = image[a][b][k];
                    new_image[i + 1][j][k] = image[a][b][k];
                    new_image[i][j + 1][k] = image[a][b][k];
                    new_image[i + 1][j + 1][k] = image[a][b][k];
                }
                b += 1;
            }
            a += 1;
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
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            for (int k = 0; k < RGB; ++k) {
                new_image[i][j][k] = 255;
            }
        }
    }
    if (scale == "1") {
        for (int i = 0; i < 126; i++) {
            for (int j = 0; j < 126; j++) {
                new_image[i][j][0] = image[i * 2][j * 2][0];
                new_image[i][j][1] = image[i * 2][j * 2][1];
                new_image[i][j][2] = image[i * 2][j * 2][2];
            }
        }

    } else if (scale == "2") {

        for (int i = 0; i < 86; i++) {
            for (int j = 0; j < 86; j++) {
                new_image[i][j][0] = image[i * 3][j * 3][0];
                new_image[i][j][1] = image[i * 3][j * 3][1];
                new_image[i][j][2] = image[i * 3][j * 3][2];
            }
        }

    } else if (scale == "3") {
        for (int i = 0; i < 64; i++) {
            for (int j = 0; j < 64; j++) {
                new_image[i][j][0] = image[i * 4][j * 4][0];
                new_image[i][j][1] = image[i * 4][j * 4][1];
                new_image[i][j][2] = image[i * 4][j * 4][2];
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
                new_image[i][j][0] = image[i][j][0];
                new_image[i][j][1] = image[i][j][1];
                new_image[i][j][2] = image[i][j][2];
            }
        }
        for (int i = 0; i < SIZE; ++i) {
            for (int j = SIZE / 2; j < SIZE; ++j) {
                new_image[i][j][0] = image[i][255 - j][0];
                new_image[i][j][1] = image[i][255 - j][1];
                new_image[i][j][2] = image[i][255 - j][2];
            }
        }
    }
    // right
    if (choice == 'r') {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE / 2; ++j) {
                new_image[i][j][0] = image[i][255 - j][0];
                new_image[i][j][1] = image[i][255 - j][1];
                new_image[i][j][2] = image[i][255 - j][2];
            }
        }
        for (int i = 0; i < SIZE; ++i) {
            for (int j = SIZE / 2; j < SIZE; ++j) {
                new_image[i][j][0] = image[i][j][0];
                new_image[i][j][1] = image[i][j][1];
                new_image[i][j][2] = image[i][j][2];
            }
        }
    }
    // upper
    if (choice == 'u') {
        for (int i = 0; i < SIZE / 2; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                new_image[i][j][0] = image[i][j][0];
                new_image[i][j][1] = image[i][j][1];
                new_image[i][j][2] = image[i][j][2];
            }
        }
        for (int i = SIZE / 2; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                new_image[i][j][0] = image[255 - i][j][0];
                new_image[i][j][1] = image[255 - i][j][1];
                new_image[i][j][2] = image[255 - i][j][2];
            }
        }
    }
    // downside
    if (choice == 'd') {
        for (int i = SIZE / 2; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                new_image[i][j][0] = image[i][j][0];
                new_image[i][j][1] = image[i][j][1];
                new_image[i][j][2] = image[i][j][2];
            }
        }
        for (int i = 0; i < SIZE / 2; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                new_image[i][j][0] = image[255 - i][j][0];
                new_image[i][j][1] = image[255 - i][j][1];
                new_image[i][j][2] = image[255 - i][j][2];
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
        int r, c;
        r = k < 2 ? 0 : SIZE / 2;
        row = order[k] < '3' ? 0 : SIZE / 2;
        for (int i = row; i < row + SIZE / 2; i++, r++) {
            col = (order[k] - '0') % 2 == 1 ? 0 : SIZE / 2;
            c = k % 2 == 0 ? 0 : SIZE / 2;
            for (int j = col; j < col + SIZE / 2; j++, c++) {
                new_image[r][c][0] = image[i][j][0];
                new_image[r][c][1] = image[i][j][1];
                new_image[r][c][2] = image[i][j][2];
            }
        }
    }
}

void blur() {
    for (int i = 1; i < SIZE-1; i++) {
        for (int j = 1; j < SIZE-1; j++) {
            for(int k = 0; k<3 ; k++)
            new_image[i][j][k] =
                    (image[i][j+1][k] + image[i][j + 2][k] + image[i][j+3][k] + image[i+ 1][j][k] + image[i+2][j][k] +
                     image[i+3][j][k] + image[i + 1][j + 1][k] + image[i + 2][j+2][k] + image[i + 3][j + 3][k]) / 9;
        }
    }

}
