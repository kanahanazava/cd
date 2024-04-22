class ThreeAddressCodeGenerator:
    def __init__(self):
        self.quadruples = []
        self.triples = []
        self.indirect_triples = []
        self.temp_count = 0

    def generate_temp(self):
        temp_var = f't{self.temp_count}'
        self.temp_count += 1
        return temp_var

    def generate_code(self, op, arg1, arg2, result):
        self.quadruples.append((op, arg1, arg2, result))
        self.triples.append((op, arg1, arg2))
        self.indirect_triples.append((op, result))

    def generate_expression_code(self, expr):
        if isinstance(expr, tuple):  # Binary operation
            op, left, right = expr
            temp_result = self.generate_temp()
            self.generate_expression_code(left)
            self.generate_expression_code(right)
            self.generate_code(op, left, right, temp_result)
            return temp_result
        else:  # Operand (variable or constant)
            return expr

    def display_code(self):
        print("Quadruples:")
        for quad in self.quadruples:
            print(quad)

        print("\nTriples:")
        for triple in self.triples:
            print(triple)

        print("\nIndirect Triples:")
        for indirect_triple in self.indirect_triples:
            print(indirect_triple)


def main():
    generator = ThreeAddressCodeGenerator()

    # Example expression: a + (b * c)
    expression = ('+', 'a', ('*', 'b', 'c'))

    result = generator.generate_expression_code(expression)

    generator.display_code()


if __name__ == "__main__":
    main()
