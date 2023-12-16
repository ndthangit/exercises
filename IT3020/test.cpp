#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::string colors[40] = {
        "Red", "Green", "Blue", "Yellow", "Orange", "Purple", "Pink", "Cyan", "Magenta", "Lime",
        "Teal", "Indigo", "Brown", "Gray", "Black", "White", "Silver", "Gold", "Maroon", "Navy",
        "Olive", "Aqua", "Coral", "Plum", "Turquoise", "Slate", "Violet", "Salmon", "Lavender", "Khaki",
        "Ruby", "Emerald", "Sapphire", "Amber", "Topaz", "Jade", "Pearl", "Garnet", "Opal", "Onyx"
    };

    std::ofstream file("colors.dot"); // Create or overwrite the file

    if (file.is_open()) {
        file << "graph colors {\n"; // Start of the DOT script

        for (int i = 0; i < 40; i++) {
            file << "    " << i << " [label=\"" << colors[i] << "\", fillcolor=\"" << colors[i] << "\", style=filled];\n";
        }

        file << "}\n"; // End of the DOT script

        file.close();
        std::cout << "Successfully created the DOT file: colors.dot" << std::endl;
    } else {
        std::cout << "Unable to create the DOT file!" << std::endl;
    }

    return 0;
}
