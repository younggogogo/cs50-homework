#include "helpers.h"
#include <math.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            BYTE av = (BYTE) round(
                (image[i][j].rgbtRed + image[i][j].rgbtBlue + image[i][j].rgbtGreen) / 3.0);
            image[i][j].rgbtRed = av;
            image[i][j].rgbtBlue = av;
            image[i][j].rgbtGreen = av;
        }
    }
    return;
}

void ref(int left, int right, RGBTRIPLE a[])
{
    if (left >= right)
    {
        return;
    }
    RGBTRIPLE TMP = a[left];
    a[left] = a[right];
    a[right] = TMP;
    ref(left + 1, right - 1, a);
}
// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        ref(0, width - 1, image[i]);
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float cnt = 0;
            int sumred = 0;
            int sumgreen = 0;
            int sumblue = 0;
            for (int n = i - 1; n <= i + 1; n++)
            {
                for (int k = j - 1; k <= j + 1; k++)
                {
                    if (n >= 0 && n < height && k >= 0 && k < width)
                    {
                        cnt++;
                        sumred += copy[n][k].rgbtRed;
                        sumblue += copy[n][k].rgbtBlue;
                        sumgreen += copy[n][k].rgbtGreen;
                    }
                }
            }
            image[i][j].rgbtRed = (BYTE) round(sumred / cnt);
            image[i][j].rgbtBlue = (BYTE) round(sumblue / cnt);
            image[i][j].rgbtGreen = (BYTE) round(sumgreen / cnt);
        }
    }
    return;
}
BYTE min(int a)
{
    if (a < 255)
    {
        return a;
    }
    else
    {
        return 255;
    }
}
// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int gxred = 0;
            int gxblue = 0;
            int gxgreen = 0;
            int gyred = 0;
            int gyblue = 0;
            int gygreen = 0;
            for (int n = i - 1, q = 0; n <= i + 1; n++, q++)
            {
                for (int k = j - 1, w = 0; k <= j + 1; k++, w++)
                {
                    if (n >= 0 && n < height && k >= 0 && k < width)
                    {

                        gxred += copy[n][k].rgbtRed * gx[q][w];
                        gxblue += copy[n][k].rgbtBlue * gx[q][w];
                        gxgreen += copy[n][k].rgbtGreen * gx[q][w];
                        gyred += copy[n][k].rgbtRed * gy[q][w];
                        gyblue += copy[n][k].rgbtBlue * gy[q][w];
                        gygreen += copy[n][k].rgbtGreen * gy[q][w];
                    }
                }
            }
            image[i][j].rgbtRed = min(round(sqrt(gxred * gxred + gyred * gyred)));
            image[i][j].rgbtBlue = min(round(sqrt(gxblue * gxblue + gyblue * gyblue)));
            image[i][j].rgbtGreen = min(round(sqrt(gxgreen * gxgreen + gygreen * gygreen)));
        }
    }
    return;
}
