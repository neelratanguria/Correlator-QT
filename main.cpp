#include "mainwindow.h"
#include <QApplication>
#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <math.h>
#include <fstream>
#include <string>
#include <string.h>
#include <QDebug>



#define TIME_FLEX99O12B  0.1179648 // in seconds
#define FIRSTDELAY   1.25E-8	// Sample time in seconds
typedef BYTE (__cdecl* USBINITIALIZE)();       //Initialize the correlator, no argument.
// return true if successful.
typedef void (__cdecl* USBSTART)(BYTE automode);     //Start correlator,
// automode: 1 auto correlate, 0 cross correlate
typedef BYTE (__cdecl* USBUPDATE)(float *ElapsedTime, unsigned short int *nTrace,
                float *corr, float *traceA, float *traceB);
//ElapsedTime : The time since Start() function is called.  This is the actual measurement time.
//nTrace : The number of elements in traceA and traceB.
//corr   : Normalized correlation function, 288 elements
//TraceA : Intensity history since laset update function is called.  Each element is averaged over 0.1048576 seconds
// Return : true if successful, false : fatal error with the device.  This may be due to correlator being disconnected during
// a measurement.
typedef void (__cdecl* USBSTOP)(void);  // Stop the correlator.
typedef void (__cdecl* USBFREE)(void);  // Call this function to clean up when finished.
using namespace std;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();


    int					i,j, k;
        float				ElapsedTime;
        unsigned short int	tracecnt;
        float				corr[288];
        float				DelayTime[288];
        float				traceA[512];
        float				traceB[512];
        double				IntensityA, IntensityB;
            int                             mnint;
        FILE				*stream;
        char				filename[256],filenumber[5];
        HINSTANCE hDLL;               // Handle to DLL
        USBSTART Start;    // Function pointer
        USBSTOP Stop;    // Function pointer
        USBINITIALIZE Initialize;    // Function pointer
        USBUPDATE Update;    // Function pointer
        USBFREE Usbfree;    // Function pointer

        BYTE mode;
            int runNumber;

        int	DurationTime;

        DurationTime = 10;
              runNumber = 1;
              mode = 0;

        for(i=0;i<16;i++)
                DelayTime[i] = (i+1)*FIRSTDELAY;
            for(j=1;j<35;j++)
                for(i=0;i<8;i++)
                    DelayTime[i+(j-1)*8+16] = DelayTime[(j-1)*8+16+i-1]+FIRSTDELAY*(float)pow(2,j);

        string strFilenname = "a.dll";

        LPCWSTR Filename = L"a.dll";
        hDLL = LoadLibrary(Filename);
        if (hDLL != NULL)
            {
                qDebug() << "DLL loaded";
            }


    return a.exec();
}
