import requests
from bs4 import BeautifulSoup
import re

def get_page(url):
    """
    Fetches the HTML page content from the given URL.

    Args:
        url (str): The URL to fetch.

    Returns:
        str: The HTML page content.
    """
    try:
        response = requests.get(url)
        response.raise_for_status()  # Raise an exception for bad status codes
        return response.text
    except Exception as e:
        print(f"Error fetching page: {e}")
        return None

def extract_data(html):
    """
    Extracts data from the given HTML content using regular expressions.

    Args:
        html (str): The HTML content to parse.

    Returns:
        list: A list of extracted data.
    """
    try:
        soup = BeautifulSoup(html, 'html.parser')
        pattern = re.compile(r"(\w+)=(\w+)")
        data = []
        for tag in soup.find_all(['h1', 'h2', 'p']):
            matches = pattern.findall(tag.text)
            for match in matches:
                data.append((match[0], match[1]))
        return data
    except Exception as e:
        print(f"Error parsing HTML: {e}")
        return []

def main():
    """
    The entry point of the program.
    """
    url = "https://www.example.com"
    html = get_page(url)
    if html:
        data = extract_data(html)
        for item in data:
            print(f"{item[0]}={item[1]}")

if __name__ == '__main__':
    main()