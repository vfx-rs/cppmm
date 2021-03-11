
#include "imf_inputfile_.h"
#include "imf_outputfile_.h"

int main()
{
    Imf_2_5_InputFile in;
    Imf_2_5_InputFile_InputFile(&in,
        "/Users/luke/Downloads/openexr-images-1.7.0/ScanLines/CandleGlass.exr",
    1);

    Imf_2_5_OutputFile out;
    Imf_2_5_OutputFile_OutputFile(&out, "copy.exr",
        Imf_2_5_InputFile_header(&in), 1);

    Imf_2_5_OutputFile_copyPixels(&out, &in);

    Imf_2_5_OutputFile_dtor(&out);
    Imf_2_5_InputFile_dtor(&in);

    return 0;
}
