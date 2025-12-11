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
                (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = av;
            image[i][j].rgbtGreen = av;
            image[i][j].rgbtRed = av;
        }
    }
    return;
}

// Convert image to sepia
BYTE cmp(WORD A)
{
    BYTE B = 255;
    if (B < A)
    {
        return B;
    }
    return (BYTE) A;
}
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE OR = image[i][j];
            image[i][j].rgbtRed =
                cmp((WORD) round(OR.rgbtBlue * 0.189 + OR.rgbtGreen * 0.769 + OR.rgbtRed * 0.393));
            image[i][j].rgbtGreen =
                cmp((WORD) round(OR.rgbtBlue * 0.168 + OR.rgbtGreen * 0.686 + OR.rgbtRed * 0.349));
            image[i][j].rgbtBlue =
                cmp((WORD) round(OR.rgbtBlue * 0.131 + OR.rgbtGreen * 0.534 + OR.rgbtRed * 0.272));
        }
    }
    return;
}

// Reflect image horizontally
void ref(int left, int right, RGBTRIPLE *image)
{
    if (left >= right)
    {
        return;
    }
    RGBTRIPLE tmp = image[left];
    image[left] = image[right];
    image[right] = tmp;
    ref(left + 1, right - 1, image);
}
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // 水平翻转实现一
    //  for (int i = 0; i < height; i++)
    //  {
    //      int left = 0;
    //      int right = width - 1;
    //      while(!(left >= right))
    //      {
    //          RGBTRIPLE tmp = image[i][right];
    //          image[i][right] = image[i][left];
    //          image[i][left] = tmp;
    //          left++;
    //          right--;
    //      }
    //  }

    // 竖直翻转
    //  for (int i = 0;i < width; i++)
    //  {
    //      int high = 0;
    //      int low = height-1;
    //  while(!(high >= low))
    //  {
    //      RGBTRIPLE tmp = image[high][i];
    //      image[high][i] = image[low][i];
    //      image[low][i] = tmp;
    //      high++;
    //      low--;
    //  }
    //  }

    // 水平翻转方式之递归
    for (int i = 0; i < height; i++)
    {
        ref(0, width - 1, image[i]);
    }
    return;
}

// Blur image
// void blur(int height, int width, RGBTRIPLE image[height][width])
// {
//     RGBTRIPLE copy[height][width];
//     for (int i = 0; i < height; i++)
//     {
//         for (int j = 0; j < width; j++)
//         {
//             copy[i][j] = image[i][j];
//         }
//     }
//     for (int i = 0; i < height; i++)
//     {
//         for (int j = 0; j < width; j++)
//         {
//             float cnt = 1.0;
//             int sumgreen = image[i][j].rgbtGreen;
//             int sumred = image[i][j].rgbtRed;
//             int sumblue = image[i][j].rgbtBlue;
//             //左上
//             if (i - 1 >= 0 && j - 1 >= 0)
//             {
//                 cnt++;
//                 sumgreen += copy[i-1][j-1].rgbtGreen;
//                 sumred += copy[i-1][j-1].rgbtRed;
//                 sumblue += copy[i-1][j-1].rgbtBlue;
//             }
//             //上
//             if (i - 1 >= 0)
//             {
//                 cnt++;
//                 sumgreen += copy[i-1][j].rgbtGreen;
//                 sumred += copy[i-1][j].rgbtRed;
//                 sumblue += copy[i-1][j].rgbtBlue;
//             }
//             //右上
//             if (i - 1 >= 0 && j + 1 < width)
//             {
//                 cnt++;
//                 sumgreen += copy[i-1][j+1].rgbtGreen;
//                 sumred += copy[i-1][j+1].rgbtRed;
//                 sumblue += copy[i-1][j+1].rgbtBlue;
//             }
//             //左
//             if ( j - 1 >= 0)
//             {
//                 cnt++;
//                 sumgreen += copy[i][j-1].rgbtGreen;
//                 sumred += copy[i][j-1].rgbtRed;
//                 sumblue += copy[i][j-1].rgbtBlue;
//             }
//             //右
//             if (j + 1 < width)
//             {
//                 cnt++;
//                 sumgreen += copy[i][j+1].rgbtGreen;
//                 sumred += copy[i][j+1].rgbtRed;
//                 sumblue += copy[i][j+1].rgbtBlue;
//             }
//             //左下
//             if (j - 1 >= 0 && i + 1 < height)
//             {
//                 cnt++;
//                 sumgreen += copy[i+1][j-1].rgbtGreen;
//                 sumred += copy[i+1][j-1].rgbtRed;
//                 sumblue += copy[i+1][j-1].rgbtBlue;
//             }
//             //下
//             if (i + 1 < height)
//             {
//                 cnt++;
//                 sumgreen += copy[i+1][j].rgbtGreen;
//                 sumred += copy[i+1][j].rgbtRed;
//                 sumblue += copy[i+1][j].rgbtBlue;
//             }
//             //右下
//             if (i + 1 < height && j + 1 <width)
//             {
//                 cnt++;
//                 sumgreen += copy[i+1][j+1].rgbtGreen;
//                 sumred += copy[i+1][j+1].rgbtRed;
//                 sumblue += copy[i+1][j+1].rgbtBlue;
//             }
//             image[i][j].rgbtGreen = (BYTE)round(sumgreen / cnt);
//             image[i][j].rgbtRed = (BYTE)round(sumred / cnt);
//             image[i][j].rgbtBlue = (BYTE)round(sumblue / cnt);
//         }
//     }
//     return;
// }
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
            int sumgreen = 0;
            int sumred = 0;
            int sumblue = 0;
            for (int n = i - 1; n <= i + 1; n++)
            {
                for (int k = j - 1; k <= j + 1; k++)
                {
                    if (n >= 0 && n < height && k >= 0 && k < width)
                    {
                        cnt++;
                        sumgreen += copy[n][k].rgbtGreen;
                        sumred += copy[n][k].rgbtRed;
                        sumblue += copy[n][k].rgbtBlue;
                    }
                }
            }
            image[i][j].rgbtGreen = (BYTE) round(sumgreen / cnt);
            image[i][j].rgbtRed = (BYTE) round(sumred / cnt);
            image[i][j].rgbtBlue = (BYTE) round(sumblue / cnt);
        }
    }
    return;
}
