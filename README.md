# Std-Success Quiz App
A simple quiz app

# Dependencies
## Windows
You will need dll libraries required by gtkmm, use ldd **executable** in MSYS2 to find out which ones you need
## Linux
The required libraries can be downloaded using your package manager, usually gtkmm-4.0 and gtkmm-4.0-dev(el)

# Compilation
``
meson setup build
meson compile -C build
``  
The executable will be located in the build folder.
