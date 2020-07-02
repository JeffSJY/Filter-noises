#include "filter/filters.h"
#include "filter/filters.cpp"
void menu();
int main()
{
    int op, sizeFactor;
    Mat img = imread("lena.jpg", 0);
    Mat imgColor = imread("lena.jpg", CV_LOAD_IMAGE_COLOR);
    if (!img.data || !imgColor.data)
    {
        cout << "Não possui imagem" << endl;
        return -1;
    }
    do
    {
        menu();
        cin >> op;
        switch (op)
        {
        case 1:
            cout << "Tamanho do zoom:";
            cin >> sizeFactor;
            zoom(imgColor, sizeFactor);
            break;
        case 2:
            median(img);
            break;
        case 3:
            cout << "Grau do sal e pimenta:";
            cin >> sizeFactor; // 5000
            saltAndPepper(img, sizeFactor);
            break;
        case 4:
            filterLaplaciano(img);
            break;
        case 5:
            filterSobel(img);
            break;
        case 6:
            filterPrewitt(img);
            break;
        case 7:
            filterGaussiano(img);
            break;
        case 0:
            break;
        default:
            cout << "# error" << endl;
            break;
        }

    } while (op != 0);

    return 0;
}

void menu()
{
    cout << "   Menu" << endl
         << endl;
    cout << "1 -- zoom" << endl;
    cout << "2 -- mediana" << endl;
    cout << "3 -- sal e pimenta" << endl;
    cout << "4 -- laplaciano" << endl;
    cout << "5 -- Sobel" << endl;
    cout << "6 -- Prewitt" << endl;
    cout << "7 -- gaussiana" << endl;
    cout << "0 -- sair" << endl;
    
}