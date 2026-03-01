% Simple Calculator in MATLAB
%
% Author: Your Name (replace this)
%

% Import necessary libraries
import java.awt.*;
import javax.swing.*;
import java.awt.event.*;

class SimpleCalculator extends JFrame {
    private JTextField inputField;
    private JTextField outputField;

    public SimpleCalculator() {
        super("Simple Calculator");
        setLayout(new FlowLayout());

        // Create the input field
        inputField = new JTextField(20);
        add(inputField);

        // Create the output field
        outputField = new JTextField(20);
        outputField.setEditable(false); % Set to read-only for output
        add(outputField);

        // Add a button panel with calculation buttons
        JPanel buttonPanel = new JPanel();
        addButton(buttonPanel, "7", "numButton");
        addButton(buttonPanel, "8", "numButton");
        addButton(buttonPanel, "9", "numButton");
        addButton(buttonPanel, "4", "numButton");
        addButton(buttonPanel, "5", "numButton");
        addButton(buttonPanel, "6", "numButton");
        addButton(buttonPanel, "1", "numButton");
        addButton(buttonPanel, "2", "numButton");
        addButton(buttonPanel, "3", "numButton");
        addButton(buttonPanel, "0", "numButton");

        // Add the buttons to the main frame
        add(buttonPanel);

        // Add an equals button for calculation
        JButton equalsButton = new JButton("=");
        equalsButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                calculate();
            }
        });
        add(equalsButton);

        setSize(200, 150);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }

    private void addButton(JPanel panel, String text, String actionCommand) {
        JButton button = new JButton(text);
        button.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                inputField.setText(inputField.getText() + text);
            }
        });
        button.setActionCommand(actionCommand);
        panel.add(button);
    }

    private void calculate() {
        try {
            String expression = inputField.getText();
            double result = eval(expression);
            outputField.setText(String.valueOf(result));
        } catch (Exception e) {
            outputField.setText("Error");
        }
    }

    public static double eval(String str) throws Exception {
        return new Object() {
            int pos = -1, ch;

            void nextChar() {
                ch = ++pos < str.length() ? str.charAt(pos) : -1;
            }

            boolean eat(int charToEat) {
                while (ch == ' ') nextChar();
                if (ch == charToEat) {
                    nextChar();
                    return true;
                }
                return false;
            }

            int parse() {
                nextChar();
                int x = parseExpression();
                if (pos < str.length()) throw new RuntimeException("Unexpected: " + (char)ch);
                return x;
            }

            // Grammar:
            // expression = term | expression `+` term | expression `-` term
            // term = factor | term `*` factor | term `/` factor
            // factor = `+` factor | `-` factor | `(` expression `)`
            int parseExpression() {
                int x = parseTerm();
                if (eat('+')) {
                    x += parseTerm();
                } else if (eat('-')) {
                    x -= parseTerm();
                }
                return x;
            }

            int parseTerm() {
                int x = parseFactor();
                if (eat('*')) {
                    x *= parseFactor();
                } else if (eat('/')) {
                    x /= parseFactor();
                }
                return x;
            }

            int parseFactor() {
                if (eat('+')) return parseFactor();
                if (eat('-')) return -parseFactor();
                int x = parsePrimary();
                if (eat(')')) return x;
                while (eat('(')) {
                    x = parseExpression();
                    eat(')');
                }
                return x;
            }

            int parsePrimary() {
                if ((ch >= '0' && ch <= '9') || ch == '.') {
                    return parseNumber();
                } else {
                    nextChar();
                    int x = pos - 1;
                    if (eat('x')) return x;
                    if (eat('X')) return x;
                    throw new RuntimeException("Unexpected: " + (char)ch);
                }
            }

            int parseNumber() {
                while ((ch >= '0' && ch <= '9') || ch == '.') nextChar();
                return Integer.parseInt(new String(new char[++pos]).replace('.', '0'));
            }
        }.parse();
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            public void run() {
                new SimpleCalculator().setVisible(true);
            }
        });
    }