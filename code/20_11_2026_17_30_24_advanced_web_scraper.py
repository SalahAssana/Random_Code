import requests
from bs4 import BeautifulSoup
from collections import defaultdict
from typing import Dict, List

class WebScraper:
    def __init__(self):
        self.urls = ["https://www.example.com", "https://www.example.net"]
        self.data = defaultdict(dict)

    def fetch_data(self) -> None:
        for url in self.urls:
            response = requests.get(url)
            soup = BeautifulSoup(response.text, 'html.parser')
            for tag in ['h1', 'p']:
                for element in soup.find_all(tag):
                    text = element.get_text()
                    if text not in self.data[url]:
                        self.data[url][tag] = [text]
                    else:
                        self.data[url][tag].append(text)

    def process_data(self) -> Dict[str, List[Dict]]:
        processed_data = {}
        for url, tags in self.data.items():
            processed_data[url] = []
            for tag, texts in tags.items():
                for text in texts:
                    processed_data[url].append({"tag": tag, "text": text})
        return processed_data

    def print_results(self) -> None:
        data = self.process_data()
        for url, results in data.items():
            print(f"Results from {url}:")
            for result in results:
                print(result)

if __name__ == '__main__':
    scraper = WebScraper()
    scraper.fetch_data()
    scraper.print_results()