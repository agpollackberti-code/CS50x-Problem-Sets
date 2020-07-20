#include "helpers.h"
#include "math.h"
#include "stdio.h"
#include "stdlib.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{

    //for each row by height
    for (int i = 0; i < height; i++)
    {
        //for each pixel in the row by width
        for (int j = 0; j < width; j++)
        {
            //average the BGR values, to an int value
            int avg = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);

            //set values to the average
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;

        }

    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{

    //for each row by height
    for (int i = 0; i < height; i++)
    {
        //for each pixel in the row by width
        for (int j = 0; j < width; j++)
        {

            //grab original colors
            int originalBlue = image[i][j].rgbtBlue;
            int originalGreen = image[i][j].rgbtGreen;
            int originalRed = image[i][j].rgbtRed;

            //set values to the average
            int newBlue = round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);
            int newGreen = round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);
            int newRed = round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);

            if (newBlue > 255)
            {
                newBlue = 255;

            }
            if (newGreen > 255)
            {
                newGreen = 255;

            }
            if (newRed > 255)
            {
                newRed = 255;

            }

            image[i][j].rgbtBlue = newBlue;
            image[i][j].rgbtGreen = newGreen;
            image[i][j].rgbtRed = newRed;

        }

    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{

    //for each row by height
    for (int i = 0; i < height; i++)
    {
        //for each pixel in the row by width
        int flipSide = width - 1;
        for (int j = 0; j < width; j++)
        {
            if (flipSide > j)
            {

                int oldBlue = image[i][j].rgbtBlue;
                int oldGreen = image[i][j].rgbtGreen;
                int oldRed = image[i][j].rgbtRed;

                int newBlue = image[i][flipSide].rgbtBlue;
                int newGreen = image[i][flipSide].rgbtGreen;
                int newRed = image[i][flipSide].rgbtRed;

                //left gets the right
                image[i][j].rgbtBlue = newBlue;
                image[i][j].rgbtGreen = newGreen;
                image[i][j].rgbtRed = newRed;

                //right gets the left
                image[i][flipSide].rgbtBlue = oldBlue;
                image[i][flipSide].rgbtGreen = oldGreen;
                image[i][flipSide].rgbtRed = oldRed;

                flipSide--;

            }

        }

    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

    RGBTRIPLE(*image2)[width] = calloc(height, width * sizeof(RGBTRIPLE));

    //for each row by height
    for (int i = 0; i < height; i++)
    {
        //for each pixel in the row by width
        for (int j = 0; j < width; j++)
        {
            //set blur window
            float boxCount = 0.0;

            float totBlue = 0.0;
            float totGreen = 0.0;
            float totRed = 0.0;

            //slide our window across 3 columns
            for (int k = -1; k <= 1; k++)
            {

                int columnWindow = j + k;
                //for each column k, slide our window down across 3 rows
                if ((i >= 0) && (columnWindow >= 0) && (columnWindow < width))
                {
                    boxCount++;
                    totBlue += image[i][j + k].rgbtBlue;
                    totGreen += image[i][j + k].rgbtGreen;
                    totRed += image[i][j + k].rgbtRed;
                }

                if (((i - 1) >= 0) && (columnWindow >= 0) && (columnWindow < width))
                {
                    boxCount++;
                    totBlue += image[i - 1][j + k].rgbtBlue;
                    totGreen += image[i - 1][j + k].rgbtGreen;
                    totRed += image[i - 1][j + k].rgbtRed;
                }

                if (((i + 1) < height) && (columnWindow >= 0) && (columnWindow < width))
                {
                    boxCount++;
                    totBlue += image[i + 1][j + k].rgbtBlue;
                    totGreen += image[i + 1][j + k].rgbtGreen;
                    totRed += image[i + 1][j + k].rgbtRed;
                }

            }

            //Average Blue
            int avgBlue = round(totBlue / boxCount);

            //Average Green
            int avgGreen = round(totGreen / boxCount);

            //Average Red
            int avgRed = round(totRed / boxCount);

            //set center pixel to new value
            image2[i][j].rgbtBlue = avgBlue;
            image2[i][j].rgbtGreen = avgGreen;
            image2[i][j].rgbtRed = avgRed;

        }

    }

    //for each row by height
    for (int i = 0; i < height; i++)
    {
        //for each pixel in the row by width
        for (int j = 0; j < width; j++)
        {

            //set values to the average
            image[i][j].rgbtBlue = image2[i][j].rgbtBlue;
            image[i][j].rgbtGreen = image2[i][j].rgbtGreen;
            image[i][j].rgbtRed = image2[i][j].rgbtRed;

        }

    }



    return;
}
