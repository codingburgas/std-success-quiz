# Std-Success Quiz App
A simple quiz app

# Dependencies
## Windows
You will need dll libraries required by gtkmm, use ldd **executable** in MSYS2 to find out which ones you need
## Linux
The required libraries can be downloaded using your package manager, usually gtkmm-4.0 and gtkmm-4.0-dev(el)

# Compilation
```sh
meson setup build
meson compile -C build
```
The executable will be located in the build folder.

---

## Project Overview

**Std-Success Quiz App** is a simple desktop quiz application built in C++ with a GTK-based graphical interface. The application is designed to help users select quiz categories, answer questions, search through available questions, track their score, sort results, and calculate total scores.

The project focuses on combining core C++ programming concepts with a usable GUI application. It includes dynamic question loading, score tracking, search functionality, result handling, and recursive score calculation.

## Key Features

| Feature | Description | Status |
| --- | --- | --- |
| Graphical quiz interface | Displays questions, answer options, progress, and score-related information through a GUI. | In progress |
| Question categories menu | Allows users to choose from different quiz categories before starting a test. | Planned |
| Question search | Searches for a given text inside question statements or descriptions and returns matching question indices. | In progress |
| Score tracking | Tracks correct answers while the quiz is being completed. | In progress |
| Total score calculation | Calculates final score totals, including recursive score-processing logic. | Planned |
| Result sorting | Sorts quiz results for easier review and comparison. | Planned |
| Question selection | Supports GUI-based selection and navigation through quiz questions. | In progress |

## Technology Stack

| Area | Technology |
| --- | --- |
| Programming language | C++ |
| GUI framework | GTKMM 4 |
| Build system | Meson |
| Backend build tool | Ninja |
| Main source directory | `src/` |
| Header directory | `include/` |

## Project Structure

| Path | Purpose |
| --- | --- |
| `src/main.cpp` | Application entry point. Creates and runs the GTK application. |
| `src/ui.cpp` | Handles the quiz window, GUI layout, button events, score tracking, and question display. |
| `src/quiz.cpp` | Provides quiz question data and quiz-related helper functions, including question search. |
| `src/utils.cpp` | Contains utility functions used by the application. |
| `include/ui.h` | Declares the GUI window class and UI-related members. |
| `include/quiz.h` | Declares quiz data functions and quiz search functionality. |
| `include/utils.h` | Declares utility functions. |
| `meson.build` | Defines the build configuration and project sources. |

## Functional Requirements

| Requirement | Description |
| --- | --- |
| Category selection | The user should be able to choose a question category from a menu. |
| Question display | The application should display one question and four answer options at a time. |
| Answer handling | The selected answer should be checked against the correct option. |
| Score tracking | The application should count correct answers during the quiz. |
| Question search | Given a text value, the application should search all question statements and return the indices of matching questions. |
| Result sorting | Quiz results should be sortable, for example by score or category. |
| Recursive score calculation | Total scores should be calculated with recursive logic where appropriate. |
| GUI feedback | The interface should show progress and help users follow their current quiz state. |

## Question Search

The project includes a function for searching questions by text. A text value is provided, and the function checks whether that text exists in the statement or description of each question.

| Input | Output |
| --- | --- |
| Quiz ID and search text | A vector containing the indices of matching questions |

Example behavior:

```cpp
std::vector<int> matches = searchQuizQuestions(quizId, "algebra");
```

If questions at indices `0`, `3`, and `5` contain the search text, the function returns:

```cpp
{0, 3, 5}
```

## Score And Results

| Component | Purpose |
| --- | --- |
| Current question index | Tracks the question currently shown to the user. |
| Correct answer count | Stores how many answers were answered correctly. |
| Total question count | Defines when the quiz is complete. |
| Final result | Shows or stores the final score after the quiz ends. |
| Result sorting | Organizes completed quiz results for easier review. |

## Build Instructions

### 1. Configure The Build Directory

```sh
meson setup build
```

### 2. Compile The Project

```sh
meson compile -C build
```

### 3. Run The Application

```sh
./build/quiz
```

## Dependency Notes

| Platform | Notes |
| --- | --- |
| Linux | Install GTKMM 4 development packages using your distribution package manager. Package names are commonly `gtkmm-4.0`, `gtkmm-4.0-dev`, or similar. |
| Windows | Use MSYS2 and install the GTKMM dependencies. The `ldd` command can help identify required DLL files for the executable. |

## Example Development Commands

| Task | Command |
| --- | --- |
| Configure project | `meson setup build` |
| Compile project | `meson compile -C build` |
| Recompile after changes | `meson compile -C build` |
| Run executable | `./build/quiz` |

## Current Development Status

This project is under active development. The current implementation contains the base GUI quiz window, question display logic, answer handling, score tracking, and quiz-related helper functions. Additional features such as full category menus, complete result sorting, persistent question data, and expanded recursive score calculation can be added as the project grows.

## Future Improvements

| Improvement | Benefit |
| --- | --- |
| Add persistent question storage | Makes it possible to load real quiz data from files or another data source. |
| Add category menu screen | Lets users choose the topic before starting a quiz. |
| Improve result view | Gives users a clearer summary after finishing a quiz. |
| Add sorting options | Allows results to be sorted by score, category, or completion order. |
| Add case-insensitive search | Makes question search more flexible. |
| Add tests | Helps verify quiz logic, search behavior, sorting, and score calculation. |
| Improve memory ownership | Makes dynamic text handling safer and easier to maintain. |

## Educational Focus

| Concept | How It Is Used |
| --- | --- |
| Functions | Quiz loading, searching, scoring, and UI update logic are separated into functions. |
| Vectors | Search results and result lists can be stored dynamically. |
| Character arrays | Question text and answer options are handled as C-style strings in the quiz API. |
| Recursion | Used for total score calculation logic. |
| Sorting | Used for organizing quiz results. |
| GUI programming | GTKMM is used to create windows, labels, buttons, and event handlers. |
| Build systems | Meson is used to configure and build the C++ application. |
