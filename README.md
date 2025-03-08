# SEngine - OpenVR & GLFW Example

This project demonstrates a basic integration of OpenVR, GLFW, and OpenGL in C for VR development using the Oculus Quest 2 and other VR systems. The code provides an example of setting up an overlay using OpenVR and rendering textures in a VR environment with OpenGL.

## Features

- OpenVR Integration
- GLFW for window management and OpenGL context
- Basic OpenGL texture rendering
- Creating and displaying a VR overlay with OpenVR
- Displays 4 panels in VR space when the `main.exe` is run


## Setup and Compilation

1. **Clone the repository** to your local machine:

    ```bash
    git clone https://github.com/starzzots/SEngine.git
    ```

2. **Download the OpenVR SDK**:
    - You can download the OpenVR SDK from the official repository here: [OpenVR GitHub](https://github.com/ValveSoftware/openvr).
    - Once downloaded, look for `openvr_api.lib`: `openvr_capi.h`
    - The folder should look like this:
      ```
      SEngine/
      ├── .vscode/             
      └── lib/
      ```

3. **Install the necessary dependencies**:
    - **MinGW**: For compiling C code.
    - **GLFW**: For window creation, input handling, and OpenGL context.

4. **Important File Placement**:
    The following library files should be placed in the `SEngine/lib/` directory (or your equivalent project directory) to ensure proper linking and functionality:

    - `openvr_api.lib`: This is the OpenVR API library file.
    - `glfw3.a`: This is the GLFW static library.
    - `glfw3.dll`: This is the GLFW dynamic library (DLL).
    - `glfw3.h`: This is the GLFW header file.
    - `openvr_capi.h`: This is the OpenVR C API header file.
    - `rawdraw_sf.h`: This is a custom header for raw drawing functions.

    **Note**: If you have named your project directory something other than `SEngine`, such as `projects/` or another name, make sure to update the paths in the build configuration (`.vscode/tasks.json`) and any related code to reflect your project's actual folder structure. For example, if your project is in a folder called `projects/` and you placed the libraries in `projects/lib/`, you should modify the paths in the `tasks.json` file and any relevant code accordingly.

5. **Build the project** using GCC.

    In the `.vscode/tasks.json`, the build configuration is set to use `gcc` from MinGW:

    ```bash
    C:\mingw64\bin\gcc.exe -fdiagnostics-color=always -g ${file} -o ${fileDirname}\\${fileBasenameNoExtension}.exe -lkernel32 -luser32 -lopengl32 -lgdi32 C:\SEngine\lib\openvr_api.lib C:\SEngine\lib\libglfw3.a C:\SEngine\lib\glfw3.dll
    ```
    or just make sure you are in the main.c file and press f5 and in vscode it should prop you to use gcc just file the steps and it should run build and run the file once pressed. Note: if openvr is not open and you vr headset isnt connected then the program will try                                                                                                                                                                                              to run and crash

6. Open your terminal or VS Code and run the build task.

7. After compiling, run the generated executable (`main.exe`) to start the VR application.

## Running the Application

When you run `main.exe`, it will display **4 panels** in VR space. These panels are rendered as overlays using OpenVR and OpenGL. You can interact with them using your VR system.

To run the application:
1. Make sure your VR hardware (e.g., Oculus Quest 2) is connected and the OpenVR runtime is active.
2. Execute the `main.exe` file to launch the VR application and display the 4 panels in VR space.


## Notes

- Ensure the OpenVR runtime is installed and active for proper VR functionality.
- This project currently supports OpenVR with basic texture rendering in VR overlays, which are displayed as 4 panels in the VR environment.
- Adjust the paths in `tasks.json` and other configurations if your folder structure changes.
![vrtest](https://github.com/user-attachments/assets/18c482e0-d3c8-48a2-bd3d-1ce20c0c03f1)

## GitHub Repository

The source code for this project is hosted on GitHub:

[https://github.com/starzzots/SEngine](https://github.com/starzzots/SEngine)

Feel free to contribute or raise issues!

