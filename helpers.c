#include "helpers.h"
#include <math.h>


void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int avg = round((image[i][j].red + image[i][j].green + image[i][j].blue) / 3.0);
            image[i][j].red = image[i][j].blue = image[i][j].green = avg;
        }
    }
    return;
}


void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sepiaRed = round(.393 * image[i][j].red + .769 * image[i][j].green + .189 * image[i][j].blue);
            int sepiaGreen = round(.349 * image[i][j].red + .686 * image[i][j].green + .168 * image[i][j].blue);
            int sepiaBlue = round(.272 * image[i][j].red + .534 * image[i][j].green + .131 * image[i][j].blue);

            image[i][j].blue = (sepiaBlue > 255) ? 255 : sepiaBlue;
            image[i][j].green = (sepiaGreen > 255) ? 255 : sepiaGreen;
            image[i][j].red = (sepiaRed > 255) ? 255 : sepiaRed;
        }
    }
    return;
}


// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (width / 2); j++)
        {
            // Swap pixels on the opposite side horizontally
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
    return;
}


void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float totalR = 0, totalG = 0, totalB = 0;
            int pixels = 0;

            for (int k = i - 1; k < i + 2; k++)
            {
                for (int l = j - 1; l < j + 2; l++)
                {
                    // Checking if the current pixel index is outside the image
                    if (k < 0 || k >= height || l < 0 || l >= width)
                    {
                        continue;
                    }
                    totalR += temp[k][l].red;
                    totalG += temp[k][l].green;
                    totalB += temp[k][l].blue;
                    pixels++;
                }
            }
            image[i][j].red = round(totalR / pixels);
            image[i][j].green = round(totalG / pixels);
            image[i][j].blue = round(totalB / pixels);
        }
    }
    return;
}


void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }

    // Gx and Gy kernels
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0},  {1, 2, 1}};

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float Gx_red = 0, Gx_blue = 0, Gx_green = 0, Gy_red = 0, Gy_blue = 0, Gy_green  = 0;

            for (int k = i - 1; k < i + 2; k++)
            {
                for (int l = j - 1; l < j + 2; l++)
                {
                    // Checking if the current pixel is outside the image
                    if (k < 0 || k >= height || l < 0 || l >= width)
                    {
                        continue;
                    }
                    // Computing which value from the kernel is to be multiplied
                    int a = k - i + 1;
                    int b = l - j + 1;

                    Gx_red   += temp[k][l].red   * Gx[a][b];
                    Gx_green += temp[k][l].green * Gx[a][b];
                    Gx_blue  += temp[k][l].blue  * Gx[a][b];
                    Gy_red   += temp[k][l].red   * Gy[a][b];
                    Gy_green += temp[k][l].green * Gy[a][b];
                    Gy_blue  += temp[k][l].blue  * Gy[a][b];
                }
            }
            // Calculate Sobel operator
            int red   = round(sqrt(pow(Gx_red, 2) + pow(Gy_red, 2)));
            int green = round(sqrt(pow(Gx_green, 2) + pow(Gy_green, 2)));
            int blue  = round(sqrt(pow(Gx_blue, 2) + pow(Gy_blue, 2)));

            image[i][j].red   = red > 255 ? 255 : red;
            image[i][j].green = green > 255 ? 255 : green;
            image[i][j].blue  = blue > 255 ? 255 : blue;
        }
    }
    return;
}
