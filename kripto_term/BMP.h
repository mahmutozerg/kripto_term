#include <cstdint>
using namespace std;

#pragma pack(push, 1)
struct BMPHeader {
    uint16_t file_type{ 0x4D42 }; // File type always BM which is 0x4D42
    uint32_t fileSize;      // Size of the BMP file
    uint16_t reserved1;     // Reserved (0)
    uint16_t reserved2;     // Reserved (0)
    uint32_t dataOffset;    // Offset of pixel data

    // Header size
    uint32_t headerSize;    // Size of the header

    // Image dimensions
    int32_t width;           // Image width
    int32_t height;          // Image height

    uint16_t planes;        // Number of color planes (1)
    uint16_t bitDepth;      // Number of bits per pixel

    // Compression method
    uint32_t compression;   // Compression method
    uint32_t imageSize;     // Size of the raw BMP data

    // Preferred resolution
    int32_t xPixelsPerMeter; // Pixels per meter in X axis
    int32_t yPixelsPerMeter; // Pixels per meter in Y axis

    // Number of colors in the palette
    uint32_t colorsUsed;    // Number of colors used
    uint32_t colorsImportant; // Number of important colors

    uint64_t start;


};
#pragma pack(pop)