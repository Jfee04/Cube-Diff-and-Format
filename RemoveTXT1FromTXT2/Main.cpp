#include <iostream>
#include <fstream>
#include <set>
#include <string>

void removeLines(const std::string& file1, const std::string& file2, const std::string& outputFile) {
    std::set<std::string> linesToRemove;
    std::string line;

    // Read lines from the first file and store them in a set
    std::ifstream inputFile1(file1);
    if (!inputFile1) {
        std::cerr << "Error opening file: " << file1 << std::endl;
        return;
    }

    while (std::getline(inputFile1, line)) {
        linesToRemove.insert(line);
    }
    inputFile1.close();

    // Open the second file and create a new output file
    std::ifstream inputFile2(file2);
    std::ofstream output(outputFile);

    if (!inputFile2) {
        std::cerr << "Error opening file: " << file2 << std::endl;
        return;
    }

    // Write lines from the second file to the output file if they are not in the first file
    while (std::getline(inputFile2, line)) {
        if (linesToRemove.find(line) == linesToRemove.end()) {
            output << line << std::endl;
        }
    }

    inputFile2.close();
    output.close();
}


void appendPrefixAndCountLines(const std::string& inputFile, const std::string& outputFile) {
    std::ifstream input(inputFile);
    std::ofstream output(outputFile);
    std::string line;
    int lineCount = 0;

    if (!input) {
        std::cerr << "Error opening file: " << inputFile << std::endl;
        return;
    }

    while (std::getline(input, line)) {
        // Check if the line contains "# mainboard"
        if (line.find("# mainboard") == std::string::npos) {
            output << "1x " << line << std::endl; // Append "1x" to the beginning of each line
            lineCount++; // Increment line count only if the line doesn't contain "# mainboard"
        }
    }

    input.close();
    output.close();

    std::cout << "Total lines processed (excluding '# mainboard'): " << lineCount << std::endl;
}


int main() {
    std::string file1 = "Current10-30-24.txt"; // Replace with your first file
    std::string file2 = "Goal10-30-24.txt"; // Replace with your second file
    std::string outputFile = "output.txt"; // Output file to write the result
    std::string outputFileFormatted = "outputFormatted.txt"; // Output file to store formated output


    removeLines(file1, file2, outputFile);
    std::cout << "Lines from " << file2 << " not in " << file1 << " have been written to " << outputFile << std::endl;

    appendPrefixAndCountLines(outputFile, outputFileFormatted);
    std::cout << "Output formatted" << std::endl;

    return 0;
}
