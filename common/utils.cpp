#include "utils.h"
#include <IL/il.h>
#include <IL/ilu.h>
#include <IL/ilut.h>

#include <fstream>
float utils::DegreesToRadians(float degrees){
    return degrees * (float)(PI / 180);
}

float utils::RadiansToDegrees(float radians) {
    return radians * (float)(180 / PI);
}

std::string utils::IntToStr(int i) {
    std::stringstream ss;
    ss<<i;
    std::string s;
    ss>>s;
    return s;
}

void utils::PVec3(glm::vec3 v, bool enter) {
    std::cerr<<"("<<v[0]<<","<<v[1]<<","<<v[2]<<")";
    if (enter) std::cerr<<"\n";
}
void utils::ExitOnGLError(const char* error_message) {
#ifdef ERRORCHECK
    std::cerr<<"errorcheck\n";
    const GLenum ErrorValue = glGetError();

    if (ErrorValue != GL_NO_ERROR)
    {
        const char* APPEND_DETAIL_STRING = ": %s\n";
        const size_t APPEND_LENGTH = strlen(APPEND_DETAIL_STRING) + 1;
        const size_t message_length = strlen(error_message);
        char* display_message = (char*)malloc(message_length + APPEND_LENGTH);

        memcpy(display_message, error_message, message_length);
        memcpy(&display_message[message_length], APPEND_DETAIL_STRING, APPEND_LENGTH);

        fprintf(stderr, display_message, gluErrorString(ErrorValue));

        free(display_message);
        exit(EXIT_FAILURE);
    }
#endif
}

//http://r3dux.org/tag/ilutglloadimage/
// Function load a image, turn it into a texture, and return the texture ID as a GLuint for use
GLuint utils::LoadImageTex(const char* theFileName) {
    ILuint imageID;             // Create an image ID as a ULuint
    GLuint textureID;           // Create a texture ID as a GLuint
    ILboolean success;          // Create a flag to keep track of success/failure
    ILenum error;               // Create a flag to keep track of the IL error state
    ilGenImages(1, &imageID);       // Generate the image ID
    ilBindImage(imageID);           // Bind the image

  //std::string lala(theFileName);
  //std::cout<<lala<<"\n";
    success = ilLoadImage(theFileName);     // Load the image file
 
    // If we managed to load the image, then we can start to do things with it...
    if (success) {
        // If the image is flipped (i.e. upside-down and mirrored, flip it the right way up!)
        ILinfo ImageInfo;
        iluGetImageInfo(&ImageInfo);
        if (ImageInfo.Origin == IL_ORIGIN_UPPER_LEFT) {
            iluFlipImage();
        }
 
        // Convert the image into a suitable format to work with
        // NOTE: If your image contains alpha channel you can replace IL_RGB with IL_RGBA
        success = ilConvertImage(IL_RGB, IL_UNSIGNED_BYTE);
 
        // Quit out if we failed the conversion
        if (!success) {
            error = ilGetError();
            std::cout << "Image conversion failed - IL reports error: " << error << " - " << iluErrorString(error) << std::endl;
            exit(-1);
        }
 
        // Generate a new texture
        glGenTextures(1, &textureID);
 
        // Bind the texture to a name
        glBindTexture(GL_TEXTURE_2D, textureID);
        //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT), 0, GL_RGBA, GL_UNSIGNED_BYTE, ilGetData());
        glTexImage2D(GL_TEXTURE_2D,                 // Type of texture
                     0,                             // Pyramid level (for mip-mapping) - 0 is the top level
                     ilGetInteger(IL_IMAGE_FORMAT),    // Image colour depth
                     //GL_RGBA,    // Image colour depth
                     ilGetInteger(IL_IMAGE_WIDTH),  // Image width
                     ilGetInteger(IL_IMAGE_HEIGHT), // Image height
                     0,                             // Border width in pixels (can either be 1 or 0)
                     ilGetInteger(IL_IMAGE_FORMAT), // Image format (i.e. RGB, RGBA, BGR etc.)
                     //GL_RGBA, // Image format (i.e. RGB, RGBA, BGR etc.)
                     GL_UNSIGNED_BYTE,              // Image data type
                     ilGetData());                  // The actual image data itself
 
        // Set texture clamping method
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
 
        // Set texture interpolation method to use linear interpolation (no MIPMAPS)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
 
        // Specify the texture specification
        /*
        glTexImage2D(GL_TEXTURE_2D,                 // Type of texture
                     0,             // Pyramid level (for mip-mapping) - 0 is the top level
                     ilGetInteger(IL_IMAGE_BPP),    // Image colour depth
                     ilGetInteger(IL_IMAGE_WIDTH),  // Image width
                     ilGetInteger(IL_IMAGE_HEIGHT), // Image height
                     0,             // Border width in pixels (can either be 1 or 0)
                     ilGetInteger(IL_IMAGE_FORMAT), // Image format (i.e. RGB, RGBA, BGR etc.)
                     GL_UNSIGNED_BYTE,      // Image data type
                     ilGetData());          // The actual image data itself
        */
#ifdef ERRORCHECK
        utils::ExitOnGLError("Error: no se pudo obtener setear parametros de la textura");
#endif
    }
    else {// If we failed to open the image file in the first place...{
        error = ilGetError();
        std::cout << "Image load failed - IL reports error: " << error << " - " << iluErrorString(error) << std::endl;
        exit(-1);
    }
    ilDeleteImages(1, &imageID); // Because we have already copied image data into texture data we can release memory used by image.
 
    //std::cout << "Texture creation successful." << std::endl;
    return textureID; // Return the GLuint to the texture so you can use it!
}
double utils::GetUnixTime() {
    struct timespec tv;
    if(clock_gettime(CLOCK_REALTIME, &tv) != 0) return 0;
    return (((double) tv.tv_sec) + (double) (tv.tv_nsec / 1000000000.0));
}

// Get current date/time, format is YYYY-MM-DD.HH:mm:ss
std::string utils::GetCurrentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);

    return buf;
}
