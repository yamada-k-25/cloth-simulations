#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

vector<unsigned char> split_hex(string& input, char delimiter)
{
    istringstream stream(input);
    string field;
    vector<unsigned char> result;
    while (getline(stream, field, delimiter)) {
        unsigned char field_char = (unsigned char ) atof(field.c_str());
        result.push_back(field_char);
    }
    return result;
}

// int main()
// {
//     ifstream ifs("data.csv");

//     string line;
//     while (getline(ifs, line)) {
        
//         vector<string> strvec = split(line, ',');
        
//         for (int i=0; i<strvec.size();i++){
//             printf("%5d\n", stoi(strvec.at(i)));
//         }
        
//     }
// } 