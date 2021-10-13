// Maximum sizes
#define MAX_BUFFER_SIZE  1024
#define MAX_IP_LENGTH      16
#define MAX_PARAMETER_COUNT 5
#define MAX_METHOD_SIZE    10

// Settings
#define RECIEVE_TIMEOUT 100

// Value replacements
#define NOT_FILE    0
#define IS_FILE     1
#define NO_SWITCHES 0

// Logging values
#define LOGGING_ERROR      1
#define LOGGING_CONNECTION 2
#define LOGGING_SETUP      3
#define LOGGING_SENDING    4

// Logging colors
#define COLOR_RESET      "\e[37m"
#define COLOR_ERROR      "\e[31m"
#define COLOR_CONNECTION "\e[34m"
#define COLOR_SETUP      "\e[32m"
#define COLOR_MESSAGE    "\e[33m"
#define COLOR_SENDING    "\e[35m"

// MIME types
    // Raw types
    #define TYPE_TEXT 1
    #define TYPE_PHP  2
    #define TYPE_JAVASCRIPT 3
    #define TYPE_CSS 4
    #define TYPE_BIN 5

    // Markup types 
    #define TYPE_HTML 6
    #define TYPE_RTF  7
    #define TYPE_PDF  8
    #define TYPE_ODT  9
    #define TYPE_DOC 10

    // Table types
    #define TYPE_XLS 11
    #define TYPE_ODS 12
    #define TYPE_CSV 13

    // Font types
    #define TYPE_OTF 14
    #define TYPE_TTF 15

    // Dictionary types
    #define TYPE_JSON 16
    #define TYPE_XML  17

    // Compressed types
    #define TYPE_ZIP   18
    #define TYPE_7ZIP  19
    #define TYPE_TAR   20
    #define TYPE_RAR   21
    #define TYPE_GZIP  22
    #define TYPE_BZIP  23
    #define TYPE_BZIP2 24

    // Image types
    #define TYPE_WEBP 25
    #define TYPE_TIFF 26
    #define TYPE_SVG  27
    #define TYPE_PNG  28
    #define TYPE_JPEG 29
    #define TYPE_ICON 30
    #define TYPE_GIF  31
    #define TYPE_BMP  32

    // Video types
    #define TYPE_WEBM 33
    #define TYPE_MPEG 34
    #define TYPE_MP4  35

    // Audio types
    #define TYPE_WEBA 36
    #define TYPE_WAV  37
    #define TYPE_OPUS 38
    #define TYPE_MP3  39
    #define TYPE_MIDI 40