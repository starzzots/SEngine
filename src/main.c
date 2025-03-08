#define CNFG_IMPLEMENTATION
#define CNFGOGL
#include <rawdraw_sf.h>
#undef EXTERN_C
#include <openvr_capi.h>
#define WIDTH 256
#define HEIGHT 256

// Global entry points
intptr_t VR_InitInternal(EVRInitError *peError, EVRApplicationType eType);
void VR_ShutdownInternal();
bool VR_IsHmdPresent();
intptr_t VR_GetGenericInterface(const char *pchInterfaceVersion, EVRInitError *peError);
bool VR_IsRuntimeInstalled();
const char *VR_GetVRInitErrorAsSymbol(EVRInitError error);
const char *VR_GetVRInitErrorAsEnglishDescription(EVRInitError error);

void HandleKey(int keycode, int bDown) {}
void HandleButton(int x, int y, int button, int bDown) {}
void HandleMotion(int x, int y, int mask) {}
int HandleDestroy() { return 0; }

struct VR_IVRSystem_FnTable *oSystem;
struct VR_IVROverlay_FnTable *oOverlay;
VROverlayHandle_t ulHandle1, ulHandle2, ulHandle3, ulHandle4;  // Handles for overlays I need to make this into a funct

// Define CNOVRGetOpenVRFunctionTable
void *CNOVRGetOpenVRFunctionTable(const char *interfacename)
{
    EVRInitError e;
    char fnTableName[128];
    snprintf(fnTableName, sizeof(fnTableName), "FnTable:%s", interfacename);
    void *ret = (void *)VR_GetGenericInterface(fnTableName, &e);
    printf("Getting %s FnTable: %p (%d)\n", fnTableName, ret, e);
    if (!ret)
    {
        exit(1);  // Exit if no function table is returned
    }
    return ret;
}

// Function to initialize OpenVR and create overlays
int SetupOpenVR()
{
    EVRInitError e;
    VR_InitInternal(&e, EVRApplicationType_VRApplication_Overlay);
    if (e != EVRInitError_VRInitError_None)
    {
        printf("Error %d\n", e);
        return -5;
    };

    printf("OpenVR Started Successfully\n");

    oOverlay = (struct VR_IVROverlay_FnTable *)CNOVRGetOpenVRFunctionTable(IVROverlay_Version);
    oSystem = (struct VR_IVRSystem_FnTable *)CNOVRGetOpenVRFunctionTable(IVRSystem_Version);
    if (!oOverlay || !oSystem)
    {
        printf("Error making function tables from OpenVR\n");
        return -420;
    };

    // Create the first overlay
    if (oOverlay->CreateOverlay("panel1-overlay", "Panel 1", &ulHandle1) == EVRInitError_VRInitError_None)
    {
        printf("Overlay 1 created successfully with handle: %llx\n", ulHandle1);
    }
    else
    {
        printf("Error creating overlay 1\n");
        return -421;
    };

    // Create the second overlay
    if (oOverlay->CreateOverlay("panel2-overlay", "Panel 2", &ulHandle2) == EVRInitError_VRInitError_None)
    {
        printf("Overlay 2 created successfully with handle: %llx\n", ulHandle2);
    }
    else
    {
        printf("Error creating overlay 2\n");
        return -422;
    };
    // Create the second overlay
    if (oOverlay->CreateOverlay("panel3-overlay", "Panel 3", &ulHandle3) == EVRInitError_VRInitError_None)
    {
        printf("Overlay 3 created successfully with handle: %llx\n", ulHandle3);
    }
    else
    {
        printf("Error creating overlay 3\n");
        return -422;
    };
    // Create the second overlay
    if (oOverlay->CreateOverlay("panel4-overlay", "Panel 4", &ulHandle4) == EVRInitError_VRInitError_None)
    {
        printf("Overlay 4 created successfully with handle: %llx\n", ulHandle4);
    }
    else
    {
        printf("Error creating overlay 4\n");
        return -422;
    };
    // Set overlay width and color (initial settings for both overlays)
    oOverlay->SetOverlayWidthInMeters(ulHandle1, 0.3);
    oOverlay->SetOverlayColor(ulHandle1, 1, 1, 1);
    oOverlay->SetOverlayWidthInMeters(ulHandle2, 0.3);
    oOverlay->SetOverlayColor(ulHandle2, 1, 1, 1);
    oOverlay->SetOverlayWidthInMeters(ulHandle3, 0.3);
    oOverlay->SetOverlayColor(ulHandle3, 1, 1, 1);
    oOverlay->SetOverlayWidthInMeters(ulHandle4, 0.3);
    oOverlay->SetOverlayColor(ulHandle4, 1, 1, 1);


    VRTextureBounds_t bounds;
    bounds.uMin = 0;
    bounds.uMax = 1;
    bounds.vMin = 0;
    bounds.vMax = 1;
    oOverlay->SetOverlayTextureBounds(ulHandle1, &bounds);
    oOverlay->SetOverlayTextureBounds(ulHandle2, &bounds);
    oOverlay->SetOverlayTextureBounds(ulHandle3, &bounds);
    oOverlay->SetOverlayTextureBounds(ulHandle4, &bounds);

    oOverlay->ShowOverlay(ulHandle1);
    oOverlay->ShowOverlay(ulHandle2);
    oOverlay->ShowOverlay(ulHandle3);
    oOverlay->ShowOverlay(ulHandle4);
    printf("Both overlays shown successfully!\n");

    return 0;
}

// Function to create OpenGL texture
GLuint CreateTexture()
{
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, WIDTH, HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    printf("Texture ID created: %u\n", texture);

    return texture;
}

// Function to update the overlay texture
void UpdateOverlayTexture(GLuint texture, VROverlayHandle_t ulHandle)
{
    glBindTexture(GL_TEXTURE_2D, texture);
    glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 0, 0, WIDTH, HEIGHT, 0);

    struct Texture_t OverlayTexture;
    OverlayTexture.eType = ETextureType_TextureType_OpenGL;
    OverlayTexture.eColorSpace = EColorSpace_ColorSpace_Auto;
    OverlayTexture.handle = (void *)(uintptr_t)texture; // Cast GLuint to void*

    oOverlay->SetOverlayTexture(ulHandle, &OverlayTexture);
    oOverlay->SetOverlaySortOrder(ulHandle, 100); // Ensure overlay is visible
}

// Function to adjust the overlay's properties (size, position, etc.)
void AdjustOverlay(float width, float height, float x, float y, float z, GLuint texture, VROverlayHandle_t ulHandle)
{
    // Adjust the size of the overlay
    oOverlay->SetOverlayWidthInMeters(ulHandle, width);

    // Adjust overlay position using a transform matrix
    struct HmdMatrix34_t transform = {
        1, 0, 0,  x,     // X-axis (left/right)
        0, 1, 0,  y,     // Y-axis (up/down)
        0, 0, 1, z,   // Z-axis (forward/backward)
    };
    oOverlay->SetOverlayTransformAbsolute(ulHandle, ETrackingUniverseOrigin_TrackingUniverseStanding, &transform);

    // Update the texture
    UpdateOverlayTexture(texture, ulHandle);
}

// Main loop where drawing happens
int main()
{
    CNFGSetup("Example App", WIDTH, HEIGHT);

    // Set up OpenVR
    int result = SetupOpenVR();
    if (result != 0)
    {
        return result;
    }

    GLuint texture = CreateTexture();

    while (1)
    {
        CNFGBGColor = 0x000080ff; // Dark Blue Background
        CNFGHandleInput();
        CNFGClearFrame();

        // Change color to white for text
        CNFGColor(0xffffffff);
        CNFGPenX = 1;
        CNFGPenY = 1;
        CNFGDrawText("Panel 1", 4);
        CNFGPenX = 1;
        CNFGPenY = 100;
        CNFGDrawText("Panel 2", 4);

        // Render the textures as quads on the screen with their respective overlays
        glEnable(GL_TEXTURE_2D);  // Enable texture mapping

        // First texture (panel 1)
        glBindTexture(GL_TEXTURE_2D, texture); 
        glBegin(GL_QUADS);  
        glTexCoord2f(0.0f, 0.0f); glVertex2f(-0.5f, -0.5f); // Bottom-left corner
        glTexCoord2f(1.0f, 0.0f); glVertex2f(0.5f, -0.5f);  // Bottom-right corner
        glTexCoord2f(1.0f, 1.0f); glVertex2f(0.5f, 0.5f);   // Top-right corner
        glTexCoord2f(0.0f, 1.0f); glVertex2f(-0.5f, 0.5f);  // Top-left corner
        glEnd();

        glDisable(GL_TEXTURE_2D);  // Disable texture mapping after drawing

        // Display the image and wait for the next frame
        CNFGSwapBuffers();

        // Update the overlay textures with their respective textures
        UpdateOverlayTexture(texture, ulHandle1);
        UpdateOverlayTexture(texture, ulHandle2);
        UpdateOverlayTexture(texture, ulHandle3);
        UpdateOverlayTexture(texture, ulHandle4);
        // Adjust overlays' position and size
        AdjustOverlay(0.5f, 0.5f, -0.5f, -0.5f, -1.0f, texture, ulHandle1);  // Panel 1
        AdjustOverlay(0.5f, 0.5f, 0.5f, -0.5f, -1.0f, texture, ulHandle2);   // Panel 2
        AdjustOverlay(0.5f, 0.5f, -1.5f, -1.5f, -2.0f, texture, ulHandle3);  // Panel 3
        AdjustOverlay(0.5f, 0.5f, 1.5f, 1.5f, -2.0f, texture, ulHandle4);   // Panel 4
    }

    return 0;
}
