#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include <unordered_set>
#include <cctype>
using namespace std;

unordered_set<string> keywords = {"int", "char", "return", "using", "namespace", "std", "main"};
unordered_set<char> operators = {'+', '-', '*', '/', '=', '<', '>', '!', '%'};
unordered_set<char> punctuation = {';', ',', '(', ')', '{', '}', '[', ']'};

string removeComments(const string &code) {
    string result = code;
    // Single-line comment regex
    regex singleLineComment("//.*");
    // Multi-line comment regex
    regex multiLineComment("/\\*.*?\\*/");

    // Remove single-line comments
    result = regex_replace(result, singleLineComment, "");
    // Remove multi-line comments
    result = regex_replace(result, multiLineComment, "");
    return result;
}

vector<string> tokenize(const string &code) {
    vector<string> tokens;
    string token;
    for (char c : code) {
        if (isspace(c) || operators.count(c) || punctuation.count(c)) {
            if (!token.empty()) {
                tokens.push_back(token);
                token.clear();
            }
            if (!isspace(c)) {
                tokens.push_back(string(1, c));
            }
        } else {
            token += c;
        }
    }
    if (!token.empty()) {
        tokens.push_back(token);
    }
    return tokens;
}

bool isConstant(const string &token) {
    return regex_match(token, regex("\\d+")) || regex_match(token, regex("'\\w'"));
}

bool isIdentifier(const string &token) {
    return regex_match(token, regex("[a-zA-Z_][a-zA-Z0-9_]*"));
}

void lexicalAnalysis(const string &code) {
    string cleanCode = removeComments(code);
    vector<string> tokens = tokenize(cleanCode);

    vector<string> identifiers;
    vector<string> constants;
    vector<string> keywordsFound;
    vector<string> operatorsFound;
    vector<string> punctuationFound;
    vector<string> lexicalErrors;

    for (const string &token : tokens) {
        if (keywords.count(token)) {
            keywordsFound.push_back(token);
        } else if (operators.count(token[0]) && token.size() == 1) {
            operatorsFound.push_back(token);
        } else if (punctuation.count(token[0]) && token.size() == 1) {
            punctuationFound.push_back(token);
        } else if (isConstant(token)) {
            constants.push_back(token);
        } else if (isIdentifier(token)) {
            identifiers.push_back(token);
        } else {
            lexicalErrors.push_back(token);
        }
    }

    cout << "Keywords: ";
    for (const string &k : keywordsFound) cout << k << " ";
    cout << "\nIdentifiers: ";
    for (const string &id : identifiers) cout << id << " ";
    cout << "\nConstants: ";
    for (const string &c : constants) cout << c << " ";
    cout << "\nOperators: ";
    for (const string &op : operatorsFound) cout << op << " ";
    cout << "\nPunctuation: ";
    for (const string &p : punctuationFound) cout << p << " ";
    cout << "\nLexical Errors: ";
    for (const string &err : lexicalErrors) cout << err << " ";
    cout << endl;
}

int main() {
    string code = R"(
#include<iostream>
using namespace std;

int main(){
    int a = 5;//7H;
    //assign value
    char b='x';
    /* return 
    value*/
    return a+b;
}
)";

    lexicalAnalysis(code);
    return 0;
}
