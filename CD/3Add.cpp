#include <iostream>
#include <sstream>
#include <vector>
#include <tuple>

using namespace std;

class ThreeAddressCodeGenerator {
public:
    vector<tuple<string, string, string, string>> quadruples;
    vector<tuple<string, string, string>> triples;
    vector<tuple<string, string>> indirect_triples;
    int temp_count;

    ThreeAddressCodeGenerator() : temp_count(0) {}

    string generate_temp() {
        return "t" + to_string(temp_count++);
    }

    void generate_code(const string& op, const string& arg1, const string& arg2, const string& result) {
        quadruples.push_back(make_tuple(op, arg1, arg2, result));
        triples.push_back(make_tuple(op, arg1, arg2));
        indirect_triples.push_back(make_tuple(op, result));
    }

    string generate_expression_code(const tuple<string, string, string>& expr) {
        string op = get<0>(expr);
        string left = get<1>(expr);
        string right = get<2>(expr);

        if (op == "+" || op == "-" || op == "*" || op == "/") {
            string temp_result = generate_temp();
            generate_expression_code(make_tuple(left, "", ""));
            generate_expression_code(make_tuple(right, "", ""));
            generate_code(op, left, right, temp_result);
            return temp_result;
        } else {
            // Operand (variable or constant)
            return op;
        }
    }

    void display_code() {
        cout << "Quadruples:\n";
        for (const auto& quad : quadruples) {
            cout << "(" << get<0>(quad) << ", " << get<1>(quad) << ", " << get<2>(quad) << ", " << get<3>(quad) << ")\n";
        }

        cout << "\nTriples:\n";
        for (const auto& triple : triples) {
            cout << "(" << get<0>(triple) << ", " << get<1>(triple) << ", " << get<2>(triple) << ")\n";
        }

        cout << "\nIndirect Triples:\n";
        for (const auto& indirect_triple : indirect_triples) {
            cout << "(" << get<0>(indirect_triple) << ", " << get<1>(indirect_triple) << ")\n";
        }
    }
};

int main() {
    ThreeAddressCodeGenerator generator;

    // Example expression: a + (b * c)
    tuple<string, string, string> expression = make_tuple("+", "a", "*");
    get<2>(expression) = generator.generate_expression_code(make_tuple("b", "*", "c"));

    string result = generator.generate_expression_code(expression);

    generator.display_code();

    return 0;
}
