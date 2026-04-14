% Simple Calculator Program
% BEGINNER complexity project

% Import necessary libraries
import java.awt.*;
import javax.swing.*;

class SimpleCalculator extends JFrame {
    // Declare GUI components
    JTextField inputField;
    JButton[] numberButtons = new JButton[10];
    JButton[] operatorButtons = new JButton[4];
    JButton equalsButton, clearButton;

    // Constructor to initialize the GUI
    public SimpleCalculator() {
        super("Simple Calculator");
        setLayout(new FlowLayout());

        // Initialize input field
        inputField = new JTextField(16);
        add(inputField);

        // Initialize number buttons
        for (int i = 0; i < 10; i++) {
            numberButtons[i] = new JButton(String.valueOf(i));
            add(numberButtons[i]);
        }

        // Initialize operator buttons
        String[] operators = { "+", "-", "*", "/" };
        for (int i = 0; i < 4; i++) {
            operatorButtons[i] = new JButton(operators[i]);
            add(operatorButtons[i]);
        }

        // Initialize equals and clear buttons
        equalsButton = new JButton("=");
        clearButton = new JButton("C");
        add(equalsButton);
        add(clearButton);

        // Set up event handling for number buttons
        for (int i = 0; i < 10; i++) {
            final int num = i;
            numberButtons[i].addActionListener(new ActionListener() {
                public void actionPerformed(ActionEvent e) {
                    inputField.setText(inputField.getText() + String.valueOf(num));
                }
            });
        }

        // Set up event handling for operator buttons
        for (int i = 0; i < 4; i++) {
            final int opIndex = i;
            operatorButtons[i].addActionListener(new ActionListener() {
                public void actionPerformed(ActionEvent e) {
                    inputField.setText(inputField.getText() + operators[opIndex]);
                }
            });
        }

        // Set up event handling for equals button
        equalsButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                try {
                    double result = eval(inputField.getText());
                    inputField.setText(String.valueOf(result));
                } catch (Exception ex) {
                    inputField.setText("Error");
                }
            }
        });

        // Set up event handling for clear button
        clearButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                inputField.setText("");
            }
        });

        setSize(200, 150);
        setDefaultCloseOperation(EXIT_ON_CLOSE);
    }

    // Evaluate the expression in the input field using a simple parser
    private double eval(String text) throws Exception {
        return new Object() {
            int pos = 0, ch;

            void nextChar() {
                while (pos < text.length() && Character.isWhitespace(text.charAt(pos)))
                    pos++;
                ch = text.charAt(pos);
            }

            boolean eat(int cc) {
                if (ch == cc)
                    pos++;
                nextChar();
                return ch == cc;
            }

            int peekCode() {
                int cc = 0;
                if (pos < text.length())
                    cc = text.charAt(pos);
                return cc;
            }

            double parse() throws Exception {
                nextChar();
                double v = parseExpression();
                if (pos < text.length()) {
                    throw new RuntimeException("Unexpected: " + (char) ch);
                }
                return v;
            }

            // Grammar:
            // expression = term | expression `+` term | expression `-` term
            // term = factor | term `*` factor | term `/` factor
            // factor = `+` factor | `-` factor | `(` expression `)`
            double parseExpression() throws Exception {
                double v = parseTerm();
                while (true) {
                    if (eat('+')) {
                        v += parseTerm();
                    } else if (eat('-')) {
                        v -= parseTerm();
                    } else
                        return v;
                }
            }

            double parseTerm() throws Exception {
                double v = parseFactor();
                while (true) {
                    if (eat('*')) {
                        v *= parseFactor();
                    } else if (eat('/')) {
                        v /= parseFactor();
                    } else
                        return v;
                }
            }

            double parseFactor() throws Exception {
                nextChar();
                int cc = ch;
                double v;
                switch (cc) {
                    case '+':
                        nextChar();
                        v = parseFactor(); // '(' expression ')'
                        break;
                    case '-':
                        nextChar();
                        v = -parseFactor();
                        break;
                    case '(':
                        nextChar();
                        v = parseExpression();
                        eat(')');
                        break;
                    default:
                        if (Character.isDigit(cc)) {
                            int val = 0;
                            while ((ch >= '0' && ch <= '9') || ch == '.') {
                                if (ch == '.')
                                    pos++;
                                else
                                    val = val * 10 + Character.getNumericValue(ch);
                                nextChar();
                            }
                            v = new Double(val).doubleValue();
                        } else
                            throw new RuntimeException("Unexpected: " + (char) ch);
                }
                return v;
            }
        }.parse();
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            public void run() {
                SimpleCalculator calc = new SimpleCalculator();
                calc.setVisible(true);
            }
        });
    }
}