# SEngine - OpenVR & GLFW Example

This project demonstrates a basic integration of OpenVR, GLFW, and OpenGL in C for VR development using the Oculus Quest 2 and other VR systems. The code provides an example of setting up an overlay using OpenVR and rendering textures in a VR environment with OpenGL.

## Features

- OpenVR Integration
- GLFW for window management and OpenGL context
- Basic OpenGL texture rendering
- Creating and displaying a VR overlay with OpenVR


## Dependencies

- **OpenVR**: To interact with VR hardware, including Oculus Quest 2 and others.
- **GLFW**: For window creation, input handling, and OpenGL context.
- **OpenGL**: For rendering textures in the VR environment.

## Setup and Compilation

1. Clone the repository to your local machine.

    ```bash
    git clone https://github.com/your-username/SEngine.git
    ```

2. Ensure you have the required dependencies installed:
    - **MinGW**: For compiling C code.
    - **OpenVR**: Download and extract OpenVR SDK to the `SEngine/openvr` folder.
    - **GLFW**: Download and configure GLFW for OpenGL support.

3. Build the project using GCC.

    In the `.vscode/tasks.json`, the build configuration is set to use `gcc` from MinGW:

    ```bash
    C:\mingw64\bin\gcc.exe -fdiagnostics-color=always -g ${file} -o ${fileDirname}\\${fileBasenameNoExtension}.exe -lkernel32 -luser32 -lopengl32 -lgdi32 C:\SEngine\lib\openvr_api.lib C:\SEngine\lib\libglfw3.a C:\SEngine\lib\glfw3.dll
    ```

4. Open your terminal or VS Code and run the build task.

5. After compiling, run the generated executable (`main.exe`) to start the VR application.

## Running the Application

To run the application:
1. Make sure your VR hardware (e.g., Oculus Quest 2) is connected and the OpenVR runtime is active.
2. Execute the `main.exe` file to launch the VR application and display the overlay.

## Notes

- Ensure the OpenVR runtime is installed and active for proper VR functionality.
- This project currently supports OpenVR with basic texture rendering in VR overlays.
- Adjust the camera and overlay settings as needed to customize the VR experience.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
