import requests
from bs4 import BeautifulSoup
from collections import defaultdict

class WebScraper:
    def __init__(self):
        self.sites = {
            "site1": {"url": "https://www.example.com", "tags": ["tag1", "tag2"]},
            "site2": {"url": "https://www.example.net", "tags": ["tag3", "tag4"]}
        }
        self.data = defaultdict(list)

    def scrape(self):
        for site, details in self.sites.items():
            url = details["url"]
            tags = details["tags"]
            response = requests.get(url)
            soup = BeautifulSoup(response.text, 'html.parser')
            for tag in tags:
                elements = soup.find_all(tag)
                for element in elements:
                    text = element.get_text()
                    self.data[site].append(text)

    def analyze(self):
        for site, texts in self.data.items():
            print(f"Site: {site}")
            unique_texts = set(texts)
            print(f"Unique Texts: {len(unique_texts)}")
            common_texts = [text for text in unique_texts if len([t for t in self.data.values() if text in t]) > 1]
            print(f"Common Texts: {common_texts}")

    def run(self):
        self.scrape()
        self.analyze()

if __name__ == '__main__':
    scraper = WebScraper()
    scraper.run()