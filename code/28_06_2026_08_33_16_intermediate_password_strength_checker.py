# Password Strength Checker
import re

class PasswordStrengthChecker:
    def __init__(self):
        self.min_length = 8
        self.lowercase_chars = re.compile(r'[a-z]')
        self.uppercase_chars = re.compile(r'[A-Z]')
        self.numbers = re.compile(r'\d')
        self.special_chars = re.compile(r'[^a-zA-Z0-9]')

    def check_password_strength(self, password):
        if len(password) < self.min_length:
            return "Password length is too short. It should be at least {} characters".format(self.min_length)
        
        has_lowercase = bool(self.lowercase_chars.search(password))
        has_uppercase = bool(self.uppercase_chars.search(password))
        has_numbers = bool(self.numbers.search(password))
        has_special_chars = bool(self.special_chars.search(password))

        if not (has_lowercase and has_uppercase and has_numbers and has_special_chars):
            return "Password should have at least one lowercase letter, one uppercase letter, one number, and one special character"
        
        return "Password is strong enough"

    def check_password_strength_main(self):
        password = input("Enter your password: ")
        result = self.check_password_strength(password)
        print(result)

if __name__ == '__main__':
    checker = PasswordStrengthChecker()
    checker.check_password_strength_main()