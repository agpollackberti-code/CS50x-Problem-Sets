#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{
    //handling for argc <2
    if (argc < 2)
    {
        printf("Please enter a filename");
        return 1;
    }

    FILE *f = fopen(argv[1], "r");
    if (f == NULL)
    {
        return 1;
    }

    //set initials
    int filecount = 0;
    bool readinginprogress = false;

    while (!feof(f))
    {
        //create buffer and allocate memory to it
        unsigned char *buffer;

        buffer = (unsigned char *)malloc(sizeof(unsigned char) * 512);

        while (fread(buffer, sizeof(unsigned char), 512, f) == 512)
        {
            //if we're continuing a read in progress, keep going
            if (readinginprogress == true && !(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0))
            {
                //keep copying;
                char *filenameCont;
                filenameCont = (char *)malloc(sizeof(char) * 8);
                sprintf(filenameCont, "%03i.jpg", (filecount - 1));
                FILE *img = fopen(filenameCont, "a+");
                fwrite(buffer, sizeof(unsigned char), 512, img);
                fclose(img);
                free(filenameCont);
            }

            //look at the first 4 elements of the buffer for sign of a new JPEG
            if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
            {
                filecount++;


                //check filecount to see if this is the first file
                if (filecount == 1)
                {


                    //start copying to new file until end of buffer
                    char *filenameFirst;
                    filenameFirst = (char *)malloc(sizeof(char) * 8);
                    sprintf(filenameFirst, "000.jpg");
                    FILE *img = fopen(filenameFirst, "w");
                    fwrite(buffer, sizeof(unsigned char), 512, img);
                    fclose(img);
                    free(filenameFirst);
                    readinginprogress = true;

                }

                if (filecount > 1)
                {


                    //start copying to new file until end of buffer
                    char *filenameNext;
                    filenameNext = (char *)malloc(sizeof(char) * 8);
                    sprintf(filenameNext, "%03i.jpg", (filecount - 1));
                    FILE *img = fopen(filenameNext, "w");
                    fwrite(buffer, sizeof(unsigned char), 512, img);
                    fclose(img);
                    free(filenameNext);
                    readinginprogress = true;

                }

            }

        }

        //in the end, free buffer and read next window of 512 bytes
        free(buffer);
    }

}
