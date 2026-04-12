% Simple Chatbot
% 
% Author: Your Name (or leave this as is)

% Import necessary libraries
import java.io.*;
import java.util.*;

class ChatBot {
    public static void main(String[] args) {
        // Initialize a HashMap to store possible responses based on user input
        HashMap<String, String> responses = new HashMap<>();
        
        // Add responses for simple user queries
        responses.put("hello", "Hello! How can I help you today?");
        responses.put("hi", "Hi there! What's up?");
        responses.put("help", "I'm happy to assist you. What do you need help with?");
        responses.put("exit", "Goodbye!");
        
        // Read user input
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        String userInput;
        
        try {
            while ((userInput = reader.readLine()) != null) {
                // Check for valid responses and provide a corresponding output
                if (responses.containsKey(userInput.toLowerCase())) {
                    System.out.println(responses.get(userInput.toLowerCase()));
                } else {
                    System.out.println("I didn't understand that. Can you please rephrase?");
                }
            }
        } catch (IOException e) {
            System.out.println("Error reading user input: " + e.getMessage());
        }
    }
}